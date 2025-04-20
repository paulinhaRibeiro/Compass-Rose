#ifndef THINGSPEAK_H
#define THINGSPEAK_H

#include "lwip/tcp.h"
#include "settings.h"

err_t http_request_callback(void *arg, struct tcp_pcb *tpcb, err_t err);
void send_data_to_thingspeak(uint16_t value_field1, uint16_t value_field2, uint8_t direction);


#endif