#include "wifi.h"
#include <stdio.h>
#include "settings.h" // SSID e senha

// controla o chip Wi-Fi embutido da Pico W
#include "pico/cyw43_arch.h"
#include "lwip/netif.h" // Para acessar netif_default e IP

bool connect_to_wifi(void)
{
    // Inicializa o Wi-Fi
    if (cyw43_arch_init())
    {
        printf("Erro ao inicializar o Wi-Fi\n");
        return false;
    }

    // ativa o modo cliente Wi-Fi.
    cyw43_arch_enable_sta_mode();
    printf("Conectando ao Wi-Fi...\n");

    // Tenta conectar à rede Wi-Fi usando o SSID e senha definidos.
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS,
                                           CYW43_AUTH_WPA2_AES_PSK, 10000))
    {
        printf("Falha ao conectar ao Wi-Fi\n");
        return false;
    }

    printf("Conectado.\n");
    if (netif_default)
    {
        printf("IP do dispositivo: %s\n", ipaddr_ntoa(&netif_default->ip_addr));
    }
    return true;
}