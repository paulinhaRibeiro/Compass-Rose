#include "page.h"
#include <stdio.h>
#include <string.h>

// Buffer para resposta HTTP
char http_response[1024];

// Função para criar a resposta HTTP
void create_http_response(uint8_t direction, uint16_t x, uint16_t y)
{
    // GERAÇÃO DA PÁGINA HTML DE RESPOSTA
    /*
        Cria uma página HTML da rosa dos ventos baseada nos movimentos do joystick.
        Os botões enviam novos comandos (GET) ao servidor ao serem clicados.
    */
    snprintf(http_response, sizeof(http_response),
             "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
             "<!DOCTYPE html><html><head><meta charset=\"UTF-8\">"
             "<title>Rosa dos Ventos</title><style>"
             "body{font-family:sans-serif;text-align:center;padding:30px;background:#f4f4f4;}"
             ".wind{font-size:28px;margin-top:20px;color:#222;}.pos{font-size:22px;color:#555;}.grid{display:grid;grid-template-columns:repeat(3,1fr);gap:10px;max-width:400px;margin:auto;font-size:20px;}.grid div{padding:10px;}"
             ".ativa{background:#e6b800;font-weight:bold;border-radius:8px;}"
             "</style></head><body><div class=\"grid\">"
             "<div class=\"%s\">No</div><div class=\"%s\">Norte</div><div class=\"%s\">Ne</div>"
             "<div class=\"%s\">Oeste</div><div class=\"%s\">Centro</div><div class=\"%s\">Leste</div>"
             "<div class=\"%s\">So</div><div class=\"%s\">Sul</div><div class=\"%s\">Se</div></div>"
             "<p class=\"pos\">Posição X(%4d) e Y(%4d) do joystick</p>"
             "  <script>"
             "      setTimeout(function(){"
             "          location.reload();"
             "      }, 2000);"
             "  </script>"
             "</body></html>",
             (direction == 6) ? "ativa" : "", // "Noroeste" NO
             (direction == 1) ? "ativa" : "", // "Norte"
             (direction == 5) ? "ativa" : "", // "Nordeste" NE
             (direction == 4) ? "ativa" : "", // "Oeste"
             (direction == 0) ? "ativa" : "", // "Centro"
             (direction == 3) ? "ativa" : "", // "Leste"
             (direction == 8) ? "ativa" : "", // "Sudoeste" SO
             (direction == 2) ? "ativa" : "", // "Sul"
             (direction == 7) ? "ativa" : "", // "Sudeste"  SE
             x,  // Valor de X
             y); // valor de y
}