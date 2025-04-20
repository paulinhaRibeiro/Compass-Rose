#include "page.h"
#include <stdio.h>
#include <string.h>

// Buffer para resposta HTTP
char http_response[1024];


// Função para criar a resposta HTTP
void create_http_response(const char *direction, char position[64])
{
    // GERAÇÃO DA PÁGINA HTML DE RESPOSTA
    /*
        Cria uma página HTML com botões para controlar os LEDs e mostra a temperatura atual.
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
             "<p class=\"pos\">%s</p>"
             "  <script>"
             "      setTimeout(function(){"
             "          location.reload();"
             "      }, 3000);"
             "  </script>"
             "</body></html>",
             strcmp(direction, "Noroeste") == 0 ? "ativa" : "",
             strcmp(direction, "Norte") == 0 ? "ativa" : "",
             strcmp(direction, "Nordeste") == 0 ? "ativa" : "",
             strcmp(direction, "Oeste") == 0 ? "ativa" : "",
             strcmp(direction, "Centro") == 0 ? "ativa" : "",
             strcmp(direction, "Leste") == 0 ? "ativa" : "",
             strcmp(direction, "Sudoeste") == 0 ? "ativa" : "",
             strcmp(direction, "Sul") == 0 ? "ativa" : "",
             strcmp(direction, "Sudeste") == 0 ? "ativa" : "",
             position);
}