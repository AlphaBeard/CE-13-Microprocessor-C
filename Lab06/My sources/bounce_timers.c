// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
#define TIMER1_PERIOD ((float) 0.026214)
#define TIMER_A_REMAINING (int) (2 / TIMER1_PERIOD)
#define TIMER_B_REMAINING (int) (3 / TIMER1_PERIOD)
#define TIMER_C_REMAINING (int) (5 / TIMER1_PERIOD)

static struct Timer timerA;
static struct Timer timerB;
static struct Timer timerC;

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
    printf("Welcome to KAJEFFRE's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);
    LEDS_INIT();
    timerA.timeRemaining = TIMER_A_REMAINING;
    timerA.event = FALSE;
    timerB.timeRemaining = TIMER_B_REMAINING;
    timerB.event = FALSE;
    timerC.timeRemaining = TIMER_C_REMAINING;
    timerC.event = FALSE;


    while (1) {
        //poll timer A
        if (timerA.event == TRUE) {
            printf("A ");
            LEDS_SET(LEDS_GET() ^ 0x04);
            timerA.event = FALSE;
        }
        if (timerB.event == TRUE) {
            printf("B ");
            LEDS_SET(LEDS_GET() ^ 0x02);
            timerB.event = FALSE;
        }
        if (timerC.event == TRUE) {
            printf("C ");
            LEDS_SET(LEDS_GET() ^ 0x01);
            timerC.event = FALSE;
        }

        //react to timer A events
        //clear timer A event flag
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

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

    //update timerA
    timerA.timeRemaining--;
    timerB.timeRemaining--;
    timerC.timeRemaining--;
    //if timerA has counted down,
    if (timerA.timeRemaining == 0) {
        timerA.event = TRUE;
        timerA.timeRemaining = TIMER_A_REMAINING;
    }
    if (timerB.timeRemaining == 0) {
        timerB.event = TRUE;
        timerB.timeRemaining = TIMER_B_REMAINING;
    }
    if (timerC.timeRemaining == 0) {
        timerC.event = TRUE;
        timerC.timeRemaining = TIMER_C_REMAINING;
    }
    //generate timerA event
    //reset timerA


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}