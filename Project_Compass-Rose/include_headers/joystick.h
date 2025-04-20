#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "pico/stdlib.h"

void joystick_init(void);
uint16_t joystick_read_x(void);
uint16_t joystick_read_y(void);
uint8_t get_direction(uint16_t x, uint16_t y);

#endif
