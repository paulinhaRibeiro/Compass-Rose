#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "joystick.h"
#include "server_http.h"
#include "wifi.h"
#include "thingspeak.h"


int main()
{
    // Inicializa a comunicação padrão
    stdio_init_all();
    joystick_init();

    absolute_time_t last_Thingspeak_update = get_absolute_time();

    sleep_ms(10000);

    // tenta conectar aoa wifi
    if (!connect_to_wifi())
        return 1;

    // Inicia o servidor HTTP
    server_http_init();

    while (true)
    {
        // Mantém o sistema em funcionamento, escutando conexões.
        //    É obrigatório para o Wi-Fi funcionar corretamente na Pico W.
        cyw43_arch_poll();
        // Envia os dados do botão e da temperatura ao Thingspeak a cada 20seg
        if (absolute_time_diff_us(last_Thingspeak_update, get_absolute_time()) >= 20000000)
        {
            send_data_to_thingspeak(x, y, directionValueThingspeak);
            last_Thingspeak_update = get_absolute_time();
        }

        sleep_ms(200);
    }

    // ENCERRAMENTO (caso saísse do loop)
    // Desliga o Wi-Fi ao finalizar o programa (embora nunca chegue aqui com while (true)).
    cyw43_arch_deinit();
    return 0;
}
