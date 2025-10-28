#ifndef BUTTON_h
#define BUTTON_h
#include <stdio.h>
#include <stdint.h>
#include <pico/stdlib.h>
#include "hardware/gpio.h"
#include "tusb.h"
#define PIN_GROUP_START 8
#define PIN_GROUP_END 15
#define ButCount 7
#define ButDebounce 3
#define timeAllowed 6
typedef struct {
    char id;
    uint8_t pin;
    uint64_t press_timestamp;
    uint64_t press_timestampprev;
    bool isPressed;

}Button;
extern Button buttons[ButCount];
int setup();
void resetButton();

#endif