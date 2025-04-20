#ifndef PAGE_H
#define PAGE_H

#include "pico/stdlib.h"

extern char http_response[1024];
void create_http_response(uint8_t direction, uint16_t x, uint16_t y);

#endif
