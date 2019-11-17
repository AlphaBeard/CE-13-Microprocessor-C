/*
 * File:   Part0.c
 * Author: theaw
 *
 * Created on April 4, 2019, 4:21 PM
 */


#include "xc.h"
#include "BOARD.h"
int main(void)
{
    BOARD_Init();
    printf("HELLO World!!\n");
    while(32);
    return 0;
}
