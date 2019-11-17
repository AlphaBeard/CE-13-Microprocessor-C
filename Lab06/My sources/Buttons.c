#include "Buttons.h"
#include <stdio.h>
#include "ButtonsTest.h"

/**
 * This function initializes the proper pins such that the buttons 1-4 may be used by modifying
 * the necessary bits in TRISD/TRISF. Only the bits necessary to enable the 1-4 buttons are
 * modified, so that this library does not interfere with other libraries.
 */

void ButtonsInit(void) {
    TRISFbits.TRISF1 = 1;
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;

}

/**
 * ButtonsCheckEvents function checks the current button states and returns
 *  any events that have occured since its last
 * call.  This function should be called repeatedly in a Timer ISR, though it can
 * be called in main() during testing.
 *
 * In normal use, this function should only be used after ButtonsInit().
 * 
 * This function should assume that the buttons start in an off state with 
 * value 0. Therefore if no buttons are
 * pressed when ButtonsCheckEvents() is first called, 
 * BUTTONS_EVENT_NONE should be returned. 
 * 
 * @return  Each bit of the return value corresponds to one ButtonEvent flag,
 *          as described in Buttons.h.  If no events are detected, BUTTONS_EVENT_NONE is returned.
 * 
 * Note that more than one event can occur simultaneously, though this situation is rare.
 * To handle this, the output should be a bitwise OR of all applicable event flags. 
 * For example, if button 1 was released at the same time that button 2 was pressed,
 * this function should return (BUTTON_EVENT_1UP | BUTTON_EVENT_2DOWN) 
 * 
 */
uint8_t ButtonsCheckEvents(void) {
    // set all events to none
    uint8_t events = BUTTON_EVENT_NONE;

    static uint8_t buttonsState;
    uint8_t tmp_btn_state = BUTTON_STATES();

    time_out--;


    //if button4 is pressed
    uint8_t tmp1 = tmp_btn_state & BUTTON_STATE_4; //current state
    uint8_t tmp2 = buttonsState & BUTTON_STATE_4;  //previous state
    if (time_out <= 0) {
        if (tmp1 != tmp2) {
            if (tmp1) { //If button 4 pressed
                events |= BUTTON_EVENT_4DOWN; // generate button_down event
                time_out = BUTTONS_DEBOUNCE_PERIOD; // reset timer
            } else {
                events |= BUTTON_EVENT_4UP; // generate button_down event
                time_out = BUTTONS_DEBOUNCE_PERIOD;
            }
        }

        //if button3 is pressed
        tmp1 = tmp_btn_state & BUTTON_STATE_3;
        tmp2 = buttonsState & BUTTON_STATE_3;

        if (tmp1 != tmp2) {
            if (tmp1) {
                events |= BUTTON_EVENT_3DOWN;
                time_out = BUTTONS_DEBOUNCE_PERIOD;

            } else {
                events |= BUTTON_EVENT_3UP;
                time_out = BUTTONS_DEBOUNCE_PERIOD;

            }
        }


        //if button2 is pressed
        tmp1 = tmp_btn_state & BUTTON_STATE_2;
        tmp2 = buttonsState & BUTTON_STATE_2;

        if (tmp1 != tmp2) {
            if (tmp1) {
                events |= BUTTON_EVENT_2DOWN;
                time_out = BUTTONS_DEBOUNCE_PERIOD;

            } else {
                events |= BUTTON_EVENT_2UP;
                time_out = BUTTONS_DEBOUNCE_PERIOD;

            }
        }
        //if button1 is pressed
        tmp1 = tmp_btn_state & BUTTON_STATE_1;
        tmp2 = buttonsState & BUTTON_STATE_1;

        if (tmp1 != tmp2) {
            if (tmp1) {
                events |= BUTTON_EVENT_1DOWN;
                time_out = BUTTONS_DEBOUNCE_PERIOD;

            } else {
                events |= BUTTON_EVENT_1UP;
                time_out = BUTTONS_DEBOUNCE_PERIOD;

            }
        }

    }
    buttonsState = tmp_btn_state;
    return events;



}

