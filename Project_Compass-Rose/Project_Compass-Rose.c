#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "joystick.h"
#include "server_http.h"
#include "wifi.h"


int main()
{
    // Inicializa a comunicação padrão
    stdio_init_all();
    joystick_init();
    

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

        sleep_ms(100);
    }

    // ENCERRAMENTO (caso saísse do loop)
    // Desliga o Wi-Fi ao finalizar o programa (embora nunca chegue aqui com while (true)).
    cyw43_arch_deinit();
    return 0;
}
