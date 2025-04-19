#ifndef PAGE_H
#define PAGE_H

#include "pico/stdlib.h"

extern char http_response[1024];
void create_http_response(const char *direction, char position[64]);

#endif
