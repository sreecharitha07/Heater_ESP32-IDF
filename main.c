#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_random.h"

// GPIOs
#define HEATER_PIN GPIO_NUM_2  // Heater + indicator LED on GPIO 2
#define LED_IDLE GPIO_NUM_14
#define LED_HEATING GPIO_NUM_27
#define LED_STABILIZING GPIO_NUM_26
#define LED_TARGET GPIO_NUM_25
#define LED_OVERHEAT GPIO_NUM_33
#define BUZZER_PIN GPIO_NUM_32 //buzzer

// Heater state enum
typedef enum {
    Idle,
    Heating,
    Stabilizing,
    TargetReached,
    Overheat
} State;

State currentState = Idle;

void reset_leds() {
    gpio_set_level(LED_IDLE, 0);
    gpio_set_level(LED_HEATING, 0);
    gpio_set_level(LED_STABILIZING, 0);
    gpio_set_level(LED_TARGET, 0);
    gpio_set_level(LED_OVERHEAT, 0);
}

void update_leds(State state) {
    reset_leds();
    switch (state) {
        case Idle: gpio_set_level(LED_IDLE, 1); break;
        case Heating: gpio_set_level(LED_HEATING, 1); break;
        case Stabilizing: gpio_set_level(LED_STABILIZING, 1); break;
        case TargetReached: gpio_set_level(LED_TARGET, 1); break;
        case Overheat: gpio_set_level(LED_OVERHEAT, 1); break;
    }
}

void print_state(State state) {
    switch (state) {
        case Idle: printf("Idle"); break;
        case Heating: printf("Heating"); break;
        case Stabilizing: printf("Stabilizing"); break;
        case TargetReached: printf("Target Reached"); break;
        case Overheat: printf("Overheat"); break;
    }
}

void app_main() {
    // Init GPIOs
    //heater
    gpio_set_direction(HEATER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(HEATER_PIN, 0);

    //buzzer
    gpio_set_direction(BUZZER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(BUZZER_PIN, 0);  // Start off

    //leds
    gpio_set_direction(LED_IDLE, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_HEATING, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_STABILIZING, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_TARGET, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_OVERHEAT, GPIO_MODE_OUTPUT);

    while (1) {
        float tempC = 25 + (esp_random() % 2000) / 100.0f; // Simulated 25°C–45°C
        // State logic
        if (tempC < 0.1f) {
              currentState = Idle;
          } else if (tempC >= 0.1f && tempC < 30.0f) {
              currentState = Heating;
          } else if (tempC >= 30.0f && tempC < 35.0f) {
              currentState = Stabilizing;
          } else if (tempC >= 35.0f && tempC < 40.0f) {
              currentState = TargetReached;
          } else {
              currentState = Overheat;
          }

        // Buzzer control for Overheat
        if (currentState == Overheat) {
            gpio_set_level(BUZZER_PIN, 1);  // Turn on buzzer
        } else {
            gpio_set_level(BUZZER_PIN, 0);  // Turn off buzzer
        }
        //for heater
        int heater_on = 0;
        // Heater control (also lights LED on GPIO 2)
        if (currentState == Heating || currentState == Stabilizing || currentState == TargetReached) {
        heater_on = 1;
        }
        gpio_set_level(HEATER_PIN, heater_on);
        //update buzzer in seril monitor
        if (currentState == Overheat) {
            gpio_set_level(BUZZER_PIN, 1);
            printf("BUZZER ON (Overheat!)\n");
        }
        // Update LEDs and serial monitor
        update_leds(currentState);
        printf("Temperature: %.2f°C | State: ", tempC);
        print_state(currentState);
        printf(" | Heater: %s\n", heater_on ? "ON" : "OFF");

        vTaskDelay(pdMS_TO_TICKS(1000)); //rtos periodic operations is used here
    }
}
