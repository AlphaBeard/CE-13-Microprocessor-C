#include "BOARD.h"
#include "Agent.h"
#include "Field.h"
#include "Negotiation.h"
#include <stdio.h>
#include <stdlib.h>

//MODULE LEVEL VARIABLES
static BB_Event battleboatEvent;

int main(void)
{
    //Initialize
    int test_flag;
    int total_success;
    int number_of_tests = 0;
    BOARD_Init();
    AgentInit();
    AgentState state = AgentGetState();
    Message message_to_send;
    printf("WELCOME TO KAJEFFRE'S Agent.c TEST HARNESS:\n");

    /*
        BB_EVENT_NO_EVENT, //0
        BB_EVENT_START_BUTTON, //1
        BB_EVENT_RESET_BUTTON, //2
        BB_EVENT_CHA_RECEIVED, //3
        BB_EVENT_ACC_RECEIVED, //4
        BB_EVENT_REV_RECEIVED, //5
        BB_EVENT_SHO_RECEIVED, //6
        BB_EVENT_RES_RECEIVED, //7
        BB_EVENT_MESSAGE_SENT, //8
        BB_EVENT_ERROR, //9

        //the following events are only used for human agents:
        BB_EVENT_SOUTH_BUTTON, //10
        BB_EVENT_EAST_BUTTON, //11
     */

    /******************Test START AGENT states***************************/
    total_success = 0;
    //    printf("Testing Starting as Challenge Agent: \n");
    //
    //    number_of_tests++;
    //    battleboatEvent.type = BB_EVENT_START_BUTTON;
    //    Message message_to_send = AgentRun(battleboatEvent);
    //    (message_to_send.type == MESSAGE_CHA) ? (total_success++) : (test_flag = 1);
    //
    //    //Give Challenge Accepted
    //    number_of_tests++;
    //
    //    int B = rand();
    //    battleboatEvent.type = BB_EVENT_ACC_RECEIVED;
    //    battleboatEvent.param0 = B;
    //    message_to_send = AgentRun(battleboatEvent);
    //    (message_to_send.type == MESSAGE_REV) ? (total_success++) : (test_flag = 2);
    //
    //
    //    //GOES TO DEFENDING STATE IN THIS INSTANCE OF DEBUG
    //    //Give Challenge Accepted
    //    number_of_tests++;
    //
    //    int row_rand = rand() % FIELD_ROWS;
    //    int col_rand = rand() % FIELD_COLS;
    //    battleboatEvent.type = BB_EVENT_SHO_RECEIVED;
    //    battleboatEvent.param0 = row_rand;
    //    battleboatEvent.param1 = col_rand;
    //    message_to_send = AgentRun(battleboatEvent);
    //    (message_to_send.type == MESSAGE_RES) ? (total_success++) : (test_flag = 3);
    //    printf("SHOT RECIEVED FIELD: \n");
    //    print_field();
    //
    //
    //    //Give Message Sent Event
    //    number_of_tests++;
    //    battleboatEvent.type = BB_EVENT_MESSAGE_SENT;
    //    message_to_send = AgentRun(battleboatEvent);
    //    (message_to_send.type == MESSAGE_SHO) ? (total_success++) : (test_flag = 4);
    //
    //
    //    //Give Message Sent Event
    //    number_of_tests++;
    //    battleboatEvent.type = BB_EVENT_RES_RECEIVED;
    //    battleboatEvent.param0 = message_to_send.param0;
    //    battleboatEvent.param1 = message_to_send.param1;
    //    battleboatEvent.param2 = RESULT_HIT;
    //    message_to_send = AgentRun(battleboatEvent);
    //    state = AgentGetState();
    //    printf("SHOT SENT FIELD: \n");
    //    print_field();
    //    (state == AGENT_STATE_DEFENDING) ? (total_success++) : (test_flag = 5);

    /***********************************************************************/

    //Reset
    ResetGame();

    /******************Test Response AGENT states***************************/
    printf("Testing Starting as Receiving Agent: \n");

    //Receive Challenge
    number_of_tests++;
    NegotiationData A = rand();
    NegotiationData hash_A = NegotiationHash(A);
    battleboatEvent.type = BB_EVENT_CHA_RECEIVED;
    battleboatEvent.param0 = hash_A;
    message_to_send = AgentRun(battleboatEvent);
    state = AgentGetState();
    (message_to_send.type == MESSAGE_ACC && state == AGENT_STATE_ACCEPTING) ? (total_success++) : (test_flag = 1);


    //Receive Reveal
    number_of_tests++;
    battleboatEvent.type = BB_EVENT_REV_RECEIVED;
    battleboatEvent.param0 = A; //noncheating
    //    battleboatEvent.param0 = 420; // cheating
    message_to_send = AgentRun(battleboatEvent);
    state = AgentGetState();
    (state == AGENT_STATE_DEFENDING || state == AGENT_STATE_ATTACKING) ? (total_success++) : (test_flag = 2);
    //    (state == AGENT_STATE_END_SCREEN) ? (total_success++) : (test_flag = 2); //cheating

    //On tails go to attacking, on heads go to defending

    /***********************************************************************/

 

    printf("\tTests passed: %d/%d\n", total_success, number_of_tests);
    if (total_success != number_of_tests) printf("\tError on test %d\n", test_flag);

    while (1);
}

