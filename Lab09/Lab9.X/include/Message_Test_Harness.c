#include "Message.h"
#include <stdint.h>
#include <stdio.h>
#include "BOARD.h"

//MODULE LEVEL VARIABLES
static char payload[15] = "";
static char checksum_string[3] = "";
static BB_Event battle_boat_event;
static int error;

//HELPER FUNCTIONS
void Decode_Result(void);
void Decode_Event(char *string);
void Decode_Event_by_char(void);

int main(void)
{
    BOARD_Init();

    //TEST HARNESS MESSAGE.c
    printf("\nWELCOME TO KAJEFFRE's LAB 9 Message.c TEST HARNESS:\n");

    //GIVE MESSAGE EVENTS WITH ENCODE
    char message[50];
    Message test_message;
    int length;

    //TSET MESSAGE ENCODE
    //    test_message.type = MESSAGE_RES;
    //    test_message.param0 = 1;
    //    test_message.param1 = 0;
    //    test_message.param2 = 1;
    //    length = Message_Encode(message, test_message);
    //
    //    Decode_Event(message);

    while (TRUE) {
        //MANUALLY GIVE COMMANDS
        char str[50];
        char nextLine;
        printf("PLEASE ENTER A BB MESSAGE: ");
        //        fgets(str, 50, stdin);
        //        scanf("%c", &nextLine);

        /*  MESSAGES TO TEST WITH 
         *    //$CHA,43182*5A
         *    //$ACC,57203*5E
         *    //$REV,12345*5C
         *    //$SHO,4,8*58
         *    //$RES,4,8,1*55
         *****BAD MESSAGES BELOW***
         *    //$RES,4,8,1*50
         *    //$RES,4,8,1*ZB
         */

        battle_boat_event.type = BB_EVENT_NO_EVENT;
        // DECODE BY FULL LINE INPUTS
        //        Decode_Event(str);

        //DECODE CHAR BY CHAR INPUT
        Decode_Event_by_char();

    }
}

void Decode_Event_by_char(void)
{
    char str;
    char nextLine;

    while (battle_boat_event.type == BB_EVENT_NO_EVENT) {
        str = getchar();
        error = Message_Decode(str, &battle_boat_event);
        printf("\nBB EVENT: %d,\n", battle_boat_event.type);
    }
    scanf("%c", &nextLine); //absorb nextline

    Decode_Result();

}

void Decode_Event(char *string)
{
    int i = 0;
    while (battle_boat_event.type == BB_EVENT_NO_EVENT && i < 50) {
        error = Message_Decode(string[i], &battle_boat_event);
        i++;
    }
    Decode_Result();

}

void Decode_Result(void)
{
    if (battle_boat_event.type == BB_EVENT_CHA_RECEIVED) {
        printf("    EVENT TYPE: CHALLENGE, PARAMETERS: %d \n\n", battle_boat_event.param0);
    } else if (battle_boat_event.type == BB_EVENT_ACC_RECEIVED) {
        printf("    EVENT TYPE: ACCEPTED, PARAMETERS: %d \n\n", battle_boat_event.param0);
    } else if (battle_boat_event.type == BB_EVENT_REV_RECEIVED) {
        printf("    EVENT TYPE: REV, PARAMETERS: %d \n\n", battle_boat_event.param0);
    } else if (battle_boat_event.type == BB_EVENT_SHO_RECEIVED) {
        printf("    EVENT TYPE: SHOT, PARAMETERS: %d, %d \n\n", battle_boat_event.param0, battle_boat_event.param1);
    } else if (battle_boat_event.type == BB_EVENT_RES_RECEIVED) {
        printf("    EVENT TYPE: RESULT, PARAMETERS: %d, %d, %d \n\n", battle_boat_event.param0, battle_boat_event.param1, battle_boat_event.param2);
    } else {
        if (battle_boat_event.param0 == BB_ERROR_BAD_CHECKSUM) {
            printf("    BAD CHECKSUM\n\n");
        } else if (battle_boat_event.param0 == BB_ERROR_CHECKSUM_LEN_EXCEEDED) {
            printf("    CHECKSUM TOO LONG\n\n");
        } else if (battle_boat_event.param0 == BB_ERROR_CHECKSUM_LEN_INSUFFICIENT) {
            printf("    CHECKSUM TOO SHORT\n\n");
        } else if (battle_boat_event.param0 == BB_ERROR_INVALID_MESSAGE_TYPE) {
            printf("    INVALID MESSAGE TYPE\n\n");
        } else if (battle_boat_event.param0 == BB_ERROR_PAYLOAD_LEN_EXCEEDED) {
            printf("    PAYLOAD TOO LONG\n\n");
        }
    }
}
