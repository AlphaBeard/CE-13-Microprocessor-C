// **** Include libraries here ****
// Standard C libraries


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
//------don't include BinaryTree.h or Morse.h!-----
#include "Morse.h"
#include "Oled.h"

//Helper functions:
void OledAddToTopLine(MorseEvent event);
void OledClearTopLine(MorseEvent event);
void OledAddToBottomLine(MorseEvent event);

//Module Level Variables
static MorseEvent morseEvent;
static int morseSpaces;
static int charSpaces;
static char morseChars[10];
static char decodedMorseChars[50];

int main()
{
    BOARD_Init();

    // <editor-fold defaultstate="collapsed" desc="Configure Timer">


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

    // </editor-fold>

    printf("\nWelcome to CRUZID's Lab8 Morse decoder!  Compiled on %s %s\n", __DATE__, __TIME__);

    //initialization code
    MorseInit();
    OledInit();
    OledDrawString("Welcome To Morse!");
    OledUpdate();
    MorseEvent decodeEvent;
    morseSpaces = 0; //for spacing out the prints
    charSpaces = 1;

    while (1) {
        //poll for morse events:
        if (morseEvent.type != MORSE_EVENT_NONE) {
            OledClear(OLED_COLOR_BLACK);
            //decode morseEvent
            decodeEvent = MorseDecode(morseEvent);
            //update OLED, if appropriate
            uint8_t topLineEvent = morseEvent.type == MORSE_EVENT_DASH || morseEvent.type == MORSE_EVENT_DOT || morseEvent.type == MORSE_EVENT_NEW_LETTER || decodeEvent.type == MORSE_EVENT_ERROR;
            if (topLineEvent) {
                OledAddToTopLine(decodeEvent);
            }
            //update OLED, if appropriate
            uint8_t bottomLineEvent = decodeEvent.type == MORSE_EVENT_CHAR_DECODED || morseEvent.type == MORSE_EVENT_NEW_WORD || decodeEvent.type == MORSE_EVENT_ERROR;
            if (bottomLineEvent) {
                OledAddToBottomLine(decodeEvent);

            }
            OledDrawString(morseChars);
            OledDrawString(decodedMorseChars);
            OledUpdate();

            //consume morseEvent

            morseEvent.type = MORSE_EVENT_NONE;
        }
    }
}

/* Timer2 is used to check for Morse events.
 * 
 * You shouldn't need to modify this ISR!
 */
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.

    IFS0CLR = 1 << 8;

    morseEvent = MorseCheckEvents();
}

void OledAddToTopLine(MorseEvent event)
{
    if (morseEvent.type == MORSE_EVENT_NEW_LETTER || event.type == MORSE_EVENT_ERROR) {
        int i;
        for (i = 0; i < 10; i++) {
            morseChars[i] = NULL;
        }
        morseSpaces = 0;
    } else if (morseEvent.type == MORSE_EVENT_DASH) {
        morseChars[morseSpaces] = '-';
        morseSpaces++;
    } else if (morseEvent.type == MORSE_EVENT_DOT) {
        morseChars[morseSpaces] = '.';
        morseSpaces++;
    }

}

void OledAddToBottomLine(MorseEvent event)
{
    decodedMorseChars[0] = '\n';
    if (event.type == MORSE_EVENT_ERROR) {
        decodedMorseChars[charSpaces] = '#';
        charSpaces++;
    } else if (event.type == MORSE_EVENT_CHAR_DECODED) {
        decodedMorseChars[charSpaces] = event.parameter;
        charSpaces++;
    } else if (morseEvent.type == MORSE_EVENT_NEW_WORD) {
        decodedMorseChars[charSpaces] = ' ';
        charSpaces++;
    }

}
