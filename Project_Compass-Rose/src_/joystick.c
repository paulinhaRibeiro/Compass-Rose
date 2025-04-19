#include "joystick.h"
#include "hardware/adc.h"
#include <stdlib.h>

const int joystick_VRX_PIN = 26; // Define o pino GP26 para o eixo X (Horz) do joystick (Canal ADC0).
const int joystick_VRY_PIN = 27; // Define o pino GP27 para o eixo Y (Vert) do joystick (Canal ADC1).

// _____________ Calibração do centro real do joystick
// A posição central real do joystick
const uint16_t CENTER_X = 1800;
const uint16_t CENTER_Y = 2100;
const uint16_t DEADZONE = 250; // Margem de tolerância

void joystick_init(void)
{
    adc_init();
    /*
        Eixo X -> GPIO26 - ADC0
        Eixo Y -> GPIO27 - ADC1
    */
    adc_gpio_init(joystick_VRX_PIN);
    adc_gpio_init(joystick_VRY_PIN);
}

uint16_t joystick_read_x(void)
{
    adc_select_input(0); // ADC0 = GPIO26
    return adc_read();
}

uint16_t joystick_read_y(void)
{
    adc_select_input(1); // ADC1 = GPIO27
    return adc_read();
}

/*
    Função que determina a direção do joystick com base nas coordenadas lidas
*/
const char *get_direction(uint16_t x, uint16_t y)
{
    // Calcula a distância entre a leitura atual e o centro calibrado.
    int16_t dx = x - CENTER_X;
    int16_t dy = y - CENTER_Y;

    if (abs(dx) < DEADZONE && abs(dy) < DEADZONE)
        return "Centro"; // Se os dois eixos estão dentro da zona morta --> joystick está parado

    /* Verifica se o desvio em X é maior que o desvio em Y
            - movimento é mais horizontal do que vertical
            - Se for verdadeiro:
                O movimento é horizontal (Leste ou Oeste) ou diagonal (SE/NE/SO/NO)*/
    if (abs(dx) > abs(dy))
    {
        // o joystick está indo para Leste (direita) - Se dy estiver na zona morta -> somente "Leste"
        /*
            Se dy > 0 -> movimento diagonal para baixo - "Sudeste"
            Se dy < 0 -> diagonal para cima - "Nordeste"
        */
        return (dx > 0) ? (abs(dy) < DEADZONE ? "Leste" : (dy > 0 ? "Sudeste" : "Nordeste"))
                        : (abs(dy) < DEADZONE ? "Oeste" : (dy > 0 ? "Sudoeste" : "Noroeste")); /// indica movimento para Oeste
    }
    else
    { // Caso contrário - o movimento é mais vertical que horizontal
        /*
            Se dy > 0, o movimento é para baixo - Sul
            Se dy < 0, é para cima - Norte
        */
        return (dy > 0) ? (abs(dx) < DEADZONE ? "Sul" : (dx > 0 ? "Sudeste" : "Sudoeste"))
                        : (abs(dx) < DEADZONE ? "Norte" : (dx > 0 ? "Nordeste" : "Noroeste"));
    }
}
