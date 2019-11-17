
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>



//CMPE13 Support Library
#include "BOARD.h"
#include "Leds_Lab06.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// **** Declare any datatypes here ****

enum MOVE_STATE {
    LEFT,
    RIGHT
};

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};


// **** Define global, module-level, or external variables here ****

int TIMER_A_REMAINING = 1;

static uint8_t bitmask;
static struct Timer timerA;

// **** Declare function prototypes ****
void led_bounce(enum MOVE_STATE state);

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
    printf("Welcome to KAJEFFRE's lab6 part2 (bounce_switch).  Compiled on %s %s.\n", __TIME__, __DATE__);
    LEDS_INIT();
    LEDS_SET(0x80); //Start LED off on left side

    enum MOVE_STATE state = RIGHT; //start LED moving right
    timerA.event = FALSE;
    timerA.timeRemaining = TIMER_A_REMAINING;
    bitmask = 0x80; // mask for traveling LED

    while (1) {

        if (bitmask == 0x80) {
            state = RIGHT;
        } else if (bitmask == 0x01) {
            state = LEFT;
        }

        //poll timer events and react if any occur
        if (timerA.event == TRUE) {
            led_bounce(state);
            LEDS_SET(bitmask);
            timerA.event = FALSE;

        }

        uint8_t switchesState = SWITCH_STATES();
        TIMER_A_REMAINING = switchesState + 1; // treats switches like a number



    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

void led_bounce(enum MOVE_STATE state) {
    if (state == RIGHT) {
        bitmask >>= 1;
    } else if (state == LEFT) {
        bitmask <<= 1;
    }
}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;


    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    //Timer Flag
    timerA.timeRemaining--;
    if (timerA.timeRemaining == 0) {
        timerA.event = TRUE;
        timerA.timeRemaining = TIMER_A_REMAINING;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}