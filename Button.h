#ifndef BUTTON_h
#define BUTTON_h
#include <stdio.h>
#include <stdint.h>
#include <pico/stdlib.h>
#include "hardware/gpio.h"
#define PIN_GROUP_START 8
#define PIN_GROUP_END 15
#define ButCount 7
#define ButDebounce 10
#define timeAllowed 30
typedef enum {
    BTN_UP,
    BTN_DOWN,
    BTN_LEFT,
    BTN_RIGHT,
    BTN_A,
    BTN_B,
    BTN_START,
    BTN_SELECT,

} ButtonID;
typedef struct {
    char id;
    uint8_t pin;
    uint64_t press_timestamp;
    uint64_t press_timestampprev;
    bool isPressed;
}Button;
extern Button buttons[ButCount];
int setup();
void resetButton(ButtonID button);

#endif