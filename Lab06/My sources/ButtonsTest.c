// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Buttons.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "ButtonsTest.h"
// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****

static uint8_t buttonEvents;
int time_out;


// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 2; // 1:64 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the time_outr on

    // Set up the time_outr interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to KAJEFFRE's lab6 part4 (ButtonsTest).  Compiled on %s %s.\n", __TIME__, __DATE__);
    printf("Please press some buttons!\n");
    time_out = BUTTONS_DEBOUNCE_PERIOD;

    while (1) {

        // IF buttonEvents has any value a.k.a any event, print...
        if (buttonEvents) {
            printf("EVENTS: ");
            printf(" 4:");
            //tmp is masked button 4 events, same for subsequent tmp variables
            uint8_t tmp = buttonEvents & 0xC0;
            if (tmp == BUTTON_EVENT_4DOWN) {
                printf("DOWN");
            } else if (tmp == BUTTON_EVENT_4UP) {
                printf("  UP");
            } else {
                printf("----");
            }

            printf(" 3:");
            tmp = buttonEvents & 0x30;
            if (tmp == BUTTON_EVENT_3DOWN) {
                printf("DOWN");
            } else if (tmp == BUTTON_EVENT_3UP) {
                printf("  UP");
            } else {
                printf("----");
            }

            printf(" 2:");
            tmp = buttonEvents & 0x0C;
            if (tmp == BUTTON_EVENT_2DOWN) {
                printf("DOWN");
            } else if (tmp == BUTTON_EVENT_2UP) {
                printf("  UP");
            } else {
                printf("----");
            }

            printf(" 1:");
            tmp = buttonEvents & 0x03;
            if (tmp == BUTTON_EVENT_1DOWN) {
                printf("DOWN");
            } else if (tmp == BUTTON_EVENT_1UP) {
                printf("  UP");
            } else {
                printf("----");
            }

            printf("\n");
            //reset events flag after use
            buttonEvents = BUTTON_EVENT_NONE;

        }
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    buttonEvents = ButtonsCheckEvents();


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}