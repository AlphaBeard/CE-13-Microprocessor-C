#include "Morse.h"
#include "BinaryTree.h"
#include "Buttons.h"

//State Machine enum and struct
static Node *root;
static Node *currentNode;

typedef enum {
    WAITING_FOR_WORD,
    WAITING_FOR_LETTER,
    WAITING_FOR_PULSE,
    DOT,
    DASH
} States;

typedef struct {
    States state;
} StateMachine;

int MorseInit(void) {
    // '.' : if invalid char, but has chars below it
    // ' ' : if no valid chars below.
    root = TreeCreate(6, ".EISH54V 3UF  . 2ARL     WP  J 1TNDB6 X  KC  Y  MGZ7 Q  O.8 .90");
    if (root == NULL) {
        return STANDARD_ERROR;
    }
    currentNode = root;
    ButtonsInit();
    return SUCCESS;

}

MorseEvent MorseDecode(MorseEvent input_event) {
    MorseEvent morseEvent;
    Node *tmpNode;
    // Process dots or dashes, check if invalid characters
    switch (input_event.type) {
            //process dash
        case MORSE_EVENT_DASH:

            //get right node
            tmpNode = GetRightChild(currentNode);
            if (tmpNode == NULL) {
                //if null child, jump out
                morseEvent.type = MORSE_EVENT_ERROR;
                currentNode = root;
                return morseEvent;
            } else {
                //if not, set to child
                currentNode = tmpNode;
            }


            //if invalid char: send error
            //else: No event flag
            if (currentNode->data == ' ') {
                morseEvent.type = MORSE_EVENT_ERROR;
            } else {
                morseEvent.type = MORSE_EVENT_NONE;
            }

            break;

        case MORSE_EVENT_DOT:
            //get left node
            tmpNode = GetLeftChild(currentNode);
            if (tmpNode == NULL) {
                //if null child, jump out
                morseEvent.type = MORSE_EVENT_ERROR;
                currentNode = root;
                return morseEvent;
            } else {
                currentNode = tmpNode;
            }

            //if invalid char: send error
            //else: No event flag
            if (currentNode->data == ' ') {
                morseEvent.type = MORSE_EVENT_ERROR;
            } else {
                morseEvent.type = MORSE_EVENT_NONE;
            }

            break;

        case MORSE_EVENT_NEW_LETTER:
            //attempt to decode character in current node
            if (currentNode->data == '.') {
                morseEvent.type = MORSE_EVENT_ERROR;
            } else {
                morseEvent.parameter = currentNode->data;
                morseEvent.type = MORSE_EVENT_CHAR_DECODED;
            }
            currentNode = root;
            break;

        default:
            morseEvent.type = MORSE_EVENT_NONE;
            break;
    }
    return morseEvent;
}

MorseEvent MorseCheckEvents(void) {
    static StateMachine SM;

    MorseEvent morse_event;
    morse_event.type = MORSE_EVENT_NONE;

    static uint16_t word_timer;
    static uint16_t letter_timer;
    static uint16_t dash_timer;

    uint8_t WORD_TIMEOUT;
    uint8_t LETTER_TIMEOUT;
    uint8_t DOT_TIMEOUT;

    //    update WORD timer
    if (word_timer != 0) {
        word_timer--;
        WORD_TIMEOUT = FALSE;
    } else {
        WORD_TIMEOUT = TRUE;
    }
    //    update LETTER timer
    if (letter_timer != 0) {
        letter_timer--;
        LETTER_TIMEOUT = FALSE;
    } else {
        LETTER_TIMEOUT = TRUE;
    }
    //    update DASH timer
    if (dash_timer != 0) {
        dash_timer--;
        DOT_TIMEOUT = FALSE;
    } else {
        DOT_TIMEOUT = TRUE;
    }

    //check for button events
    uint8_t buttonEvents = ButtonsCheckEvents();
    uint8_t events = buttonEvents || DOT_TIMEOUT || LETTER_TIMEOUT || WORD_TIMEOUT;
    //if a button event or timeout event was detected:
    if (events) {
        //run morse event checking SM  
        switch (SM.state) {
            case WAITING_FOR_WORD:
                if (buttonEvents == BUTTON_EVENT_4DOWN) {
                    dash_timer = MORSE_DOT_TIMEOUT; //set dash timer
                    SM.state = DOT;
                }
                break;
            case WAITING_FOR_LETTER:
                if (WORD_TIMEOUT == TRUE) {
                    morse_event.type = MORSE_EVENT_NEW_WORD; // generate event
                    SM.state = WAITING_FOR_WORD; // New state
                } else if (buttonEvents == BUTTON_EVENT_4DOWN) {
                    dash_timer = MORSE_DOT_TIMEOUT;
                    SM.state = DOT;
                }
                break;
            case WAITING_FOR_PULSE:
                if (LETTER_TIMEOUT == TRUE) {
                    morse_event.type = MORSE_EVENT_NEW_LETTER; // generate event
                    SM.state = WAITING_FOR_LETTER; // New state
                } else if (buttonEvents == BUTTON_EVENT_4DOWN) {
                    dash_timer = MORSE_DOT_TIMEOUT;
                    SM.state = DOT;
                }
                break;

            case DOT:
                if (buttonEvents == BUTTON_EVENT_4UP) {
                    word_timer = MORSE_WORD_TIMEOUT;
                    letter_timer = MORSE_LETTER_TIMEOUT; // reset timers
                    morse_event.type = MORSE_EVENT_DOT; //generate dot event; 
                    SM.state = WAITING_FOR_PULSE; //switch statse
                } else if (DOT_TIMEOUT == TRUE) {
                    SM.state = DASH;
                }
                break;
            case DASH:
                if (buttonEvents == BUTTON_EVENT_4UP) {
                    word_timer = MORSE_WORD_TIMEOUT;
                    letter_timer = MORSE_LETTER_TIMEOUT; // reset timers
                    morse_event.type = MORSE_EVENT_DASH; //generate dash event; 
                    SM.state = WAITING_FOR_PULSE;
                }
                break;
        }

    }
    return morse_event;

}

