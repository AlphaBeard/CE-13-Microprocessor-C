// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Buttons.h"
#include "ButtonsTest.h"
#include "Leds_Lab06.h"
// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

enum buttonStyle {
    press_on_up,
    press_on_down
};

// **** Define global, module-level, or external variables here ****
int time_out;
static uint8_t buttonsEvent;
// **** Declare function prototypes ****

int main(void) {
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to KAJEFFRE's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);
    LEDS_INIT();
    BOARD_Init();
    time_out = BUTTONS_DEBOUNCE_PERIOD;
    enum buttonStyle button_style;
    while (1) {
        //if switch 1 is flipped changed button style
        if (SW1) {
            button_style = press_on_up;
        } else {
            button_style = press_on_down;
        }

        //LED's ON FROM BUTTON DOWN EVENT
        if (button_style == press_on_down) {

            if (buttonsEvent == BUTTON_EVENT_1DOWN) {
                LEDS_SET(LEDS_GET() ^ 0x03); //invert output 1st and 2nd LED
            } else if (buttonsEvent == BUTTON_EVENT_2DOWN) {
                LEDS_SET(LEDS_GET() ^ 0x0C); //invert output 3rd and 4th
            } else if (buttonsEvent == BUTTON_EVENT_3DOWN) {
                LEDS_SET(LEDS_GET() ^ 0x30); //invert output 1st and 2nd LED
            } else if (buttonsEvent == BUTTON_EVENT_4DOWN) {
                LEDS_SET(LEDS_GET() ^ 0xC0); //invert output 3rd and 4th
            }

            //LED's ON FROM BUTTON UP EVENT
        } else if (button_style == press_on_up) {
            if (buttonsEvent == BUTTON_EVENT_1UP) {
                LEDS_SET(LEDS_GET() ^ 0x03); //invert output 1st and 2nd LED
            } else if (buttonsEvent == BUTTON_EVENT_2UP) {
                LEDS_SET(LEDS_GET() ^ 0x0C); //invert output 3rd and 4th
            } else if (buttonsEvent == BUTTON_EVENT_3UP) {
                LEDS_SET(LEDS_GET() ^ 0x30); //invert output 1st and 2nd LED
            } else if (buttonsEvent == BUTTON_EVENT_4UP) {
                LEDS_SET(LEDS_GET() ^ 0xC0); //invert output 3rd and 4th
            }

        } else {
            printf("ERROR: YOU SHOULDN'T BE HERE");
        }
        buttonsEvent = BUTTON_EVENT_NONE; // reset buttons flag 
    }
}

/***************************************************************************************************
 * Your code goes in between this comment and the preceding one with asterisks
 **************************************************************************************************/

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    buttonsEvent = ButtonsCheckEvents();

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}