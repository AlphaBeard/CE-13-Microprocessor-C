// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "Oled.h"
#include "Buttons.h"
#include "Adc.h"
#include "Leds_template.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)
#define ADC_WINDOW 4
#define LONG_PRESS 5
// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef enum {
    Time, Temp
} InputSelector;

typedef enum {
    Bake, Broil, Toast
} CookMode;

typedef struct {
    OvenState state;
    uint16_t temp;
    CookMode cook_mode;
    uint16_t btn_press_time;
    uint16_t cook_start_time;
    uint16_t cook_countdown_time;
    InputSelector input_selector;
    //add more members to this struct
} OvenData;

// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****
static uint16_t time;
static uint16_t buttonEvents;
static uint16_t adcEvents;
static uint8_t adcChanged;
static OvenData oven;
static uint8_t tick;
static int countdown_total;

// **** Put any helper functions here ****

uint8_t GetLEDPattern(int percentage)
{
    if (percentage > 87) {
        return 0xFF;
    } else if (percentage > 75) {
        return 0xFE;
    } else if (percentage > 63) {
        return 0xFC;
    } else if (percentage > 50) {
        return 0xF8;
    } else if (percentage > 38) {
        return 0xF0;
    } else if (percentage > 25) {
        return 0xE0;
    } else if (percentage > 13) {
        return 0xC0;
    } else if (percentage > 0) {
        return 0x80;
    } else {
        return 0x00;
    }


}

uint16_t OvenCharGet(void)
{
    if (oven.state == COOKING || oven.state == RESET_PENDING) {
        return 0x0301;
    } else {
        return 0x0402;
    }
}

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData)
{
    OledClear(OLED_COLOR_BLACK);

    //update OLED here
    char str_mode[30];
    char str_time[30];
    char str_temp[30];
    char str_sele[15];
    char oven1[30];
    char oven2[30];
    char oven3[30];
    char oven4[30];

    //quick way to switch oven top and bottom graphic based on cook mode
    char oven_top = OvenCharGet() & 0x00FF;
    char oven_bot = (OvenCharGet() & 0xFF00) >> 8;

    //store oven graphic
    sprintf(oven1, " |%c%c%c%c|", oven_top, oven_top, oven_top, oven_top);
    sprintf(oven2, "\n |    |");
    sprintf(oven3, "\n\n |----|");
    sprintf(oven4, "\n\n\n |%c%c%c%c|", oven_bot, oven_bot, oven_bot, oven_bot);

    //Store oven mode string
    if (ovenData.cook_mode == Bake) {
        sprintf(str_mode, "         Mode: Bake");
    } else if (ovenData.cook_mode == Broil) {
        sprintf(str_mode, "         Mode: Broil");
    } else if (ovenData.cook_mode == Toast) {
        sprintf(str_mode, "         Mode: Toast");
    } else {
        printf("ERROR: Invalid cook mode!\n");
    }

    //store oven time string
    uint16_t min = ((ovenData.cook_countdown_time / 5) + 1) / 60;
    uint16_t sec = ((ovenData.cook_countdown_time / 5) + 1) % 60;
    sprintf(str_time, "\n         Time: %01d:%02d", min, sec);

    //store oven temp string
    sprintf(str_temp, "\n\n         Temp: %i", ovenData.temp);

    if (oven.input_selector == Time) {
        sprintf(str_sele, "\n       >");
    } else if (oven.input_selector == Temp) {
        sprintf(str_sele, "\n\n       >");
    }

    OledDrawString(str_mode);
    OledDrawString(str_time);
    if (oven.cook_mode != Toast) {
        OledDrawString(str_temp);
    }
    OledDrawString(str_sele);
    OledDrawString(oven1);
    OledDrawString(oven2);
    OledDrawString(oven3);
    OledDrawString(oven4);

    OledUpdate();
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void)
{
    //write your SM logic here.
    switch (oven.state) {
    case SETUP:
        //Adc changed event 

        if (adcChanged) {

            if (oven.input_selector == Time) {
                oven.cook_countdown_time = (adcEvents >> 2)*5;
            } else if (oven.input_selector == Temp) {
                oven.temp = 300 + (adcEvents >> 2);
            }
            updateOvenOLED(oven);
            oven.state = SETUP;
        }
        //adcChanged is pretty volatile, if this becomes if else, its hard to call this code section
        if (buttonEvents & BUTTON_EVENT_3DOWN) {
            //go to selector_change state
            oven.cook_start_time = time;
            oven.state = SELECTOR_CHANGE_PENDING;
        } else if (buttonEvents & BUTTON_EVENT_4DOWN) {
            //go to cooking and grab countdown time
            countdown_total = oven.cook_countdown_time;
            oven.state = COOKING;
        }
        break;
    case SELECTOR_CHANGE_PENDING:
        if (buttonEvents & BUTTON_EVENT_3UP) {
            uint16_t elapsed_time = time - oven.cook_start_time;
            if (elapsed_time <= LONG_PRESS) {
                oven.input_selector = Time; // When switching modes go back to time selection
                oven.cook_mode = (oven.cook_mode + 1) % 3; // rotate through cook modes
                //set temp to 500 if boil
                if (oven.cook_mode == Broil) {
                    oven.temp = 500;
                }
                oven.state = SETUP;
                updateOvenOLED(oven);
            } else {
                if (oven.cook_mode == Bake) {
                    oven.input_selector = (oven.input_selector + 1) % 2;
                }
                oven.state = SETUP;
                updateOvenOLED(oven);
            }
        }
        break;
    case COOKING:
        //from setup, button 4 down comes here, start counting down
        if (buttonEvents & BUTTON_EVENT_4DOWN) {
            //go to reset_pend state for possible reset
            oven.state = RESET_PENDING;
            oven.cook_start_time = time;
        }

        if (tick) {
            oven.cook_countdown_time -= 1;
            int time_percent = (oven.cook_countdown_time * 100) / countdown_total;
            if (oven.cook_countdown_time > 0) {

                //update LED
                LEDS_SET(GetLEDPattern(time_percent));
                //update OLED
                updateOvenOLED(oven);
            } else {
                //reset settings
                LEDS_SET(GetLEDPattern(time_percent));
                oven.cook_countdown_time = (adcEvents >> 2)*5;
                oven.state = SETUP;

                //update OLED
                updateOvenOLED(oven);
                //ADD OLED FLASHING HERE
            }
        }
        break;

    case RESET_PENDING:
        if (buttonEvents & BUTTON_EVENT_4UP) {
            //if button released fast, just go back to cooking
            oven.state = COOKING;
        } else if (tick) {
            int elapsed_time = time - oven.cook_start_time;
            if (elapsed_time >= LONG_PRESS) {
                //end cooking
                oven.state = SETUP;
                //reset settings
                oven.cook_countdown_time = (adcEvents >> 2)*5;
                oven.input_selector = Time;
                LEDS_SET(0x00);
                //update oled
                updateOvenOLED(oven);
            } else {

                if (tick) {
                    oven.cook_countdown_time -= 1;
                }
                int time_percent = (oven.cook_countdown_time * 100) / countdown_total;
                //update LED
                LEDS_SET(GetLEDPattern(time_percent));
                //update OLED
                updateOvenOLED(oven);
            }
        }

        break;
    default:
        printf("ERROR: INVALID STATE");
        break;
    }

}

int main()
{
    BOARD_Init();
    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to KAJEFFRE's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    OledInit();
    ButtonsInit();
    AdcInit();
    LEDS_INIT();

    oven.cook_countdown_time = 60;
    oven.cook_mode = Bake;
    oven.state = SETUP;
    oven.temp = 350;
    oven.input_selector = Time; //TEMPORARY

    updateOvenOLED(oven);

    while (1) {
        //        if (sec_tick0) {
        //            if (oven.state == SETUP) {
        //                printf("SETUP STATE\n");
        //            } else if (oven.state == SELECTOR_CHANGE_PENDING) {
        //                printf("SELECTOR_CHANGE_PENDING STATE\n");
        //            } else if (oven.state == COOKING) {
        //                printf("COOKING STATE\n");
        //            } else if (oven.state == RESET_PENDING) {
        //                printf("RESET_PENDING STATE\n");
        //            }
        //            sec_tick0 = FALSE;
        //        }
        // check for events
        uint8_t events = adcChanged || buttonEvents || tick;
        if (events) {
            // on event, run runOvenSM()
            runOvenSM();
            // clear event flags
            buttonEvents = BUTTON_EVENT_NONE;
            adcChanged = FALSE;
            tick = FALSE;
        }

    }
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    // program clock, counts 5 times a second
    time++;
    tick = TRUE;

    //add event-checking code here
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //add event-checking code here
    buttonEvents = ButtonsCheckEvents();
    adcChanged = AdcChanged();
    // Buffer the adc to only change for shifts greater than 4 in value
    uint16_t adc_tmp = AdcRead();
    if (abs(adcEvents - adc_tmp) > ADC_WINDOW) {
        adcEvents = adc_tmp;
    }
}