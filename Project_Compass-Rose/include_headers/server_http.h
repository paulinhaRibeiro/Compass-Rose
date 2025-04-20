#ifndef SERVER_HTTP_H
#define SERVER_HTTP_H

#include "pico/stdlib.h"

extern volatile uint16_t x;
extern volatile uint16_t y;
extern volatile uint8_t directionValueThingspeak;

void server_http_init(void);

#endif
