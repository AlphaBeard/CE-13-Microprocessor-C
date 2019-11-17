#include "Leds_Lab06.h"
#include "BOARD.h"

void LEDS_INIT(void)
{
    TRISE = 0x00; // 1111 0110 . 1->input 0->output
    LATE = 0x00; // unit16 : 0000 1001 1 means high and 0 means low
}

void LEDS_SET(char newPattern)
{
    LATE = newPattern;
}

char LEDS_GET(void)
{
    return LATE;
}

