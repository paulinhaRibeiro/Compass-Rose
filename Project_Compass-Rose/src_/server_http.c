#include "server_http.h"
#include "page.h"
#include "joystick.h"

#include <stdio.h>
#include <string.h>
// lwip/*: bibliotecas para rede TCP/IP usando o stack LWIP (servidor web)
#include "lwip/pbuf.h"
#include "lwip/tcp.h"

volatile uint16_t x = 0;
volatile uint16_t y = 0;
volatile uint8_t direction = 0;


/* ___________________________________________
        Tabela de valores correspondentes 
          a posição da rosa dos ventos.
   -------------------------------------------
     Centro   -> corresponde ao número -> "0"
     Norte    -> corresponde ao número -> "1"
     Sul      -> corresponde ao número -> "2"
     Leste    -> corresponde ao número -> "3"
     Oeste    -> corresponde ao número -> "4"
     Nordeste -> corresponde ao número -> "5"
     Noroeste -> corresponde ao número -> "6"
     Sudeste  -> corresponde ao número -> "7"
     Sudoeste -> corresponde ao número -> "8"
   ___________________________________________
*/
// Função de callback para processar RESPOSTA A REQUISIÇÕES HTTP
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{ // Função chamada sempre que uma requisição HTTP chegar ao servidor.
    if (!p)
    { // Se não há dados (p == NULL), fecha a conexão TCP.
        tcp_close(tpcb);
        tcp_recv(tpcb, NULL);
        return ERR_OK;
    }

    x = joystick_read_x();
    y = joystick_read_y();
    
    // captura o numero correspondente a direção
    direction = get_direction(x, y);

    // Atualiza o conteúdo da página com base na posção do joystick
    create_http_response(direction, x, y);

    // ENVIO DA RESPOSTA AO CLIENTE
    // Envia a página HTML de volta ao navegador.
    tcp_write(tpcb, http_response, strlen(http_response), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);
    // Libera memória
    pbuf_free(p);
    return ERR_OK;
}

// Função de callback ao aceitar conexões TCP
// Toda vez que alguém se conecta ao servidor, define tcp_server_recv como função para lidar com a requisição.
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    tcp_recv(newpcb, tcp_server_recv);
    return ERR_OK;
}

// Função de setup do servidor TCP
void server_http_init(void)
{
    struct tcp_pcb *pcb = tcp_new();
    if (!pcb || tcp_bind(pcb, IP_ADDR_ANY, 80) != ERR_OK)
    {
        printf("Erro ao iniciar servidor HTTP\n");
        return;
    }
    pcb = tcp_listen(pcb);              // Coloca o PCB em modo de escuta
    tcp_accept(pcb, tcp_server_accept); // Associa o callback de conexão
    printf("Servidor HTTP escutando na porta 80\n");
}
