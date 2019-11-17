#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Message.h"
#include "BOARD.h"

//DEBUG DEFINE
//#define CHECKSUM_ALWAYS_VALID

// Module Level Variable typedefs

typedef enum {
    WAIT_FOR_DELIMITER,
    RECORDING_PAYLOAD,
    RECORDING_CHECKSUM
} MessageDecodeStates;

//Module Level Variables
static MessageDecodeStates state = WAIT_FOR_DELIMITER;
static int payload_index = 0;
static int checksum_index = 0;

//Helper Functions

uint8_t ToHex(const char *checksum_string)
{
    uint8_t checksum = 0;
    if (checksum_string[0] >= 'A' && checksum_string[0] <= 'Z') {
        checksum += (checksum_string[0] - 55) * 16;
    } else {
        checksum += (checksum_string[0] - 48) * 16;
    }
    //    checksum += 1;

    if (checksum_string[1] >= 'A' && checksum_string[1] <= 'Z') {
        checksum += (checksum_string[1] - 55);
    } else {
        checksum += checksum_string[1] - 48;
    }

    return checksum;
}

int Reset(int type)
{
    payload_index = 0;
    checksum_index = 0;
    state = WAIT_FOR_DELIMITER;
    if (type == SUCCESS) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

uint8_t Message_CalculateChecksum(const char* payload)
{
    uint8_t checksum = 0;
    int i;
    int pay_len = strlen(payload);
    for (i = 0; i < pay_len; i++) {
        checksum ^= payload[i];
    }
    return checksum;
}

int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event)
{
    char tmp_payload[MESSAGE_MAX_PAYLOAD_LEN];
    strcpy(tmp_payload, payload);
    char *payload_type = strtok(tmp_payload, ",");

    //check the payload for BB_event type and fill message_event
    if (!strcmp(payload_type, "CHA")) {
        char *char_param0 = strtok(NULL, "\0");
        int param0 = atoi(char_param0);
        message_event->param0 = param0;
        message_event->type = BB_EVENT_CHA_RECEIVED;
    } else if (!strcmp(payload_type, "ACC")) {
        char *char_param0 = strtok(NULL, "\0");
        int param0 = atoi(char_param0);
        message_event->param0 = param0;
        message_event->type = BB_EVENT_ACC_RECEIVED;
    } else if (!strcmp(payload_type, "REV")) {
        char *char_param0 = strtok(NULL, "\0");
        int param0 = atoi(char_param0);
        message_event->param0 = param0;
        message_event->type = BB_EVENT_REV_RECEIVED;
    } else if (!strcmp(payload_type, "SHO")) {
        char *char_param0 = strtok(NULL, ",");
        char *char_param1 = strtok(NULL, "\0");
        int param0 = atoi(char_param0);
        int param1 = atoi(char_param1);
        message_event->param0 = param0;
        message_event->param1 = param1;
        message_event->type = BB_EVENT_SHO_RECEIVED;
    } else if (!strcmp(payload_type, "RES")) {
        char *char_param0 = strtok(NULL, ",");
        char *char_param1 = strtok(NULL, ",");
        char *char_param2 = strtok(NULL, "\0");
        int param0 = atoi(char_param0);
        int param1 = atoi(char_param1);
        int param2 = atoi(char_param2);
        message_event->param0 = param0;
        message_event->param1 = param1;
        message_event->param2 = param2;
        message_event->type = BB_EVENT_RES_RECEIVED;
    } else {
        //No corresponding message template
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = BB_ERROR_INVALID_MESSAGE_TYPE;
        return STANDARD_ERROR;
    }

    //Make sure checksum is correct
    uint8_t checksum = Message_CalculateChecksum(payload);
    uint8_t input_checksum = ToHex(checksum_string);

    //Check for bad checksum
#ifndef CHECKSUM_ALWAYS_VALID
    if (checksum != input_checksum) {
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = BB_ERROR_BAD_CHECKSUM;
        return STANDARD_ERROR;
    }
#endif
    return SUCCESS;
}

int Message_Encode(char *message_string, Message message_to_encode)
{
    char payload_holder[15];
    uint8_t checksum;
    switch (message_to_encode.type) {
    case MESSAGE_NONE:
        return 0;
        break;
    case MESSAGE_CHA:
        sprintf(payload_holder, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0);
        break;
    case MESSAGE_ACC:
        sprintf(payload_holder, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);
        break;
    case MESSAGE_REV:
        sprintf(payload_holder, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);
        break;
    case MESSAGE_SHO:
        sprintf(payload_holder, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0, message_to_encode.param1);
        break;
    case MESSAGE_RES:
        sprintf(payload_holder, PAYLOAD_TEMPLATE_RES, message_to_encode.param0, message_to_encode.param1, message_to_encode.param2);
        break;
    }

    checksum = Message_CalculateChecksum(payload_holder);
    sprintf(message_string, MESSAGE_TEMPLATE, payload_holder, checksum);

    //MESSAGE LENGTH INCLUDE \n
    return strlen(message_string);


}

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event)
{
    static char payload[MESSAGE_MAX_PAYLOAD_LEN];
    static char checksum[MESSAGE_CHECKSUM_LEN];

    switch (state) {
    case WAIT_FOR_DELIMITER:
        if (char_in == '$') {
            state = RECORDING_PAYLOAD;
        }
        break;

    case RECORDING_PAYLOAD:
        if (payload_index > MESSAGE_MAX_PAYLOAD_LEN) {
            decoded_message_event->type = BB_EVENT_ERROR;
            decoded_message_event->param0 = BB_ERROR_PAYLOAD_LEN_EXCEEDED;
            return Reset(STANDARD_ERROR);
        } else if (char_in == '$' || char_in == '\n') {
            decoded_message_event->type = BB_EVENT_ERROR;
            decoded_message_event->param0 = BB_ERROR_INVALID_MESSAGE_TYPE;
            return Reset(STANDARD_ERROR);
        } else if (char_in == '*') {
            payload[payload_index] = '\0';
            state = RECORDING_CHECKSUM;
        } else {
            payload[payload_index] = char_in;
            payload_index++;
        }
        break;
    case RECORDING_CHECKSUM:
        if (checksum_index > MESSAGE_CHECKSUM_LEN) {
            decoded_message_event->type = BB_EVENT_ERROR;
            decoded_message_event->param0 = BB_ERROR_CHECKSUM_LEN_EXCEEDED;
            return Reset(STANDARD_ERROR);
            //            } else if (checksum_index != HEX characters) {
            //                decoded_message_event->param0 = BB_ERROR_BAD_CHECKSUM;
            //                return Error_Reset();
        } else if (char_in == '\n') {
            if (checksum_index < 2) {
                decoded_message_event->type = BB_EVENT_ERROR;
                decoded_message_event->param0 = BB_ERROR_CHECKSUM_LEN_INSUFFICIENT;
                return Reset(STANDARD_ERROR);
            }
            checksum[checksum_index] = '\0';
            //parse payload
            //parse checksum
            int error = Message_ParseMessage(payload, checksum, decoded_message_event);
            if (error == SUCCESS) {

                return Reset(SUCCESS);
            } else {
                return Reset(STANDARD_ERROR);
            }
        } else {
            checksum[checksum_index] = char_in;
            checksum_index++;
        }

        break;

    }
}