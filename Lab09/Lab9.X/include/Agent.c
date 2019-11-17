#include "Agent.h"
#include "Field.h"
#include "FieldOled.h"
#include "Negotiation.h"
#include "Message.h"
#include "BOARD.h"

//DEFINES
#define ZERO 0
//#define SMART_AI_MODE
//MODULE LEVEL VARIABLES
static AgentState currentState;
static int turnCounter;
static Field myField;
static Field oppField;
static FieldOledTurn turn = FIELD_OLED_TURN_NONE;
static GuessData PrevHit;

typedef struct {
    NegotiationData a;
    NegotiationData b;
    NegotiationData hash_a;
} Agent;
static Agent agent;

//HELPER FUNCTIONS
void DecodeError(BB_Event event);
void ResetGame(void);

void AgentInit(void)
{
    FieldInit(&myField, &oppField);
    currentState = AGENT_STATE_START;
    turnCounter = ZERO;
    FieldAIPlaceAllBoats(&myField);
    PrevHit.result = RESULT_MISS;
}

Message AgentRun(BB_Event event)
{ //Give message none type by default
    Message messageToSend;
    messageToSend.type = MESSAGE_NONE;

    switch (currentState) {
    case AGENT_STATE_START:
        if (event.type == BB_EVENT_ERROR) {
            DecodeError(event);
        } else if (event.type == BB_EVENT_START_BUTTON) {
            //Possible initialize fields here
            FieldOledDrawScreen(&myField, &oppField, turn, turnCounter);
            int A;
            A = rand();
            agent.a = A;
            NegotiationData hashToSend = NegotiationHash(A);
            agent.hash_a = hashToSend;
            messageToSend.param0 = hashToSend;
            messageToSend.type = MESSAGE_CHA;
            currentState = AGENT_STATE_CHALLENGING;
        } else if (event.type == BB_EVENT_CHA_RECEIVED) {
            int B;
            B = rand();
            agent.hash_a = event.param0;
            agent.b = B;
            messageToSend.type = MESSAGE_ACC;
            messageToSend.param0 = B;
            currentState = AGENT_STATE_ACCEPTING;
        }
        break;
    case AGENT_STATE_CHALLENGING:
        if (event.type == BB_EVENT_ERROR) {
            DecodeError(event);
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            currentState = AGENT_STATE_START;
            ResetGame();
            break;
        }
        if (event.type == BB_EVENT_ACC_RECEIVED) {
            agent.b = event.param0;
            messageToSend.type = MESSAGE_REV;
            messageToSend.param0 = agent.a;
            NegotiationOutcome outcome = NegotiateCoinFlip(agent.a, agent.b);
            if (outcome == HEADS) {
                currentState = AGENT_STATE_WAITING_TO_SEND;
            } else {
                currentState = AGENT_STATE_DEFENDING;
            }
        }
        break;
    case AGENT_STATE_ACCEPTING:
        if (event.type == BB_EVENT_ERROR) {
            DecodeError(event);
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            currentState = AGENT_STATE_START;
            ResetGame();
            break;
        }
        if (event.type == BB_EVENT_REV_RECEIVED) {
            agent.a = event.param0;
            int verified = NegotiationVerify(agent.a, agent.hash_a);
            if (verified == FALSE) {
                //                messageToSend.type = MESSAGE_ERROR;
                OledClear(OLED_COLOR_BLACK);
                OledDrawString("\n    CHEATING\n    DETECTED");
                OledUpdate();
                currentState = AGENT_STATE_END_SCREEN;
            } else if (NegotiateCoinFlip(agent.a, agent.b) == HEADS) {
                currentState = AGENT_STATE_DEFENDING;
            } else {
#ifdef SMART_AI_MODE
                GuessData firstShot = FieldAISmartDecideGuess(&oppField, &PrevHit);
#else
                GuessData firstShot = FieldAIDecideGuess(&oppField);
#endif
                messageToSend.type = MESSAGE_SHO;
                messageToSend.param0 = firstShot.row;
                messageToSend.param1 = firstShot.col;
                currentState = AGENT_STATE_ATTACKING;
            }
        }
        break;
    case AGENT_STATE_ATTACKING:
        turn = FIELD_OLED_TURN_MINE;
        FieldOledDrawScreen(&myField, &oppField, turn, turnCounter);
        if (event.type == BB_EVENT_ERROR) {
            DecodeError(event);
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            currentState = AGENT_STATE_START;
            ResetGame();
            break;
        }
        if (event.type == BB_EVENT_RES_RECEIVED) {
            //debug stuff
            //            uint8_t boat_states = FieldGetBoatStates(&myField);
            //            uint8_t enemy_boat_states = FieldGetBoatStates(&oppField);
            //            printf("\nBoatStates: %x\nEnemyBoatStates: %x\nEnemySmallBoatLives: %d\n"
            //                    "EnemyMedBoatLives: %d\n"
            //                    "EnemyLargeBoatLives: %d\n"
            //                    "EnemyHugeBoatLives: %d\n", boat_states, enemy_boat_states, myField.smallBoatLives,
            //                    myField.mediumBoatLives,
            //                    myField.largeBoatLives,
            //                    myField.hugeBoatLives);

            if (!FieldGetBoatStates(&myField)) {
                OledClear(OLED_COLOR_BLACK);
                OledDrawString("\n    DEFEAT");
                OledUpdate();
                currentState = AGENT_STATE_END_SCREEN;
            } else {
                GuessData guessResult;
                guessResult.row = event.param0;
                guessResult.col = event.param1;
                guessResult.result = event.param2;
                PrevHit.row = event.param0;
                PrevHit.col = event.param1;
                PrevHit.result = event.param2;

                FieldUpdateKnowledge(&oppField, &guessResult);
                if (!FieldGetBoatStates(&oppField)) {
                    OledClear(OLED_COLOR_BLACK);
                    OledDrawString("\n    Victory");
                    OledUpdate();
                    currentState = AGENT_STATE_END_SCREEN;
                }
                FieldOledDrawScreen(&myField, &oppField, turn, turnCounter);
                currentState = AGENT_STATE_DEFENDING;
            }
        }
        break;
    case AGENT_STATE_DEFENDING:
        turn = FIELD_OLED_TURN_THEIRS;
        if (!FieldGetBoatStates(&oppField)) {
            OledClear(OLED_COLOR_BLACK);
            OledDrawString("\n    VICTORY");
            OledUpdate();
            currentState = AGENT_STATE_END_SCREEN;
        }
        FieldOledDrawScreen(&myField, &oppField, turn, turnCounter);
        if (event.type == BB_EVENT_ERROR) {
            DecodeError(event);
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            currentState = AGENT_STATE_START;
            ResetGame();
            break;
        }
        if (event.type == BB_EVENT_SHO_RECEIVED) {
            GuessData guessResult;
            guessResult.row = event.param0;
            guessResult.col = event.param1;
            guessResult.result = event.param2;
            FieldRegisterEnemyAttack(&myField, &guessResult);
            FieldOledDrawScreen(&myField, &oppField, turn, turnCounter);
            messageToSend.type = MESSAGE_RES;
            messageToSend.param0 = guessResult.row;
            messageToSend.param1 = guessResult.col;
            messageToSend.param2 = guessResult.result;
            if (!FieldGetBoatStates(&myField)) {
                OledClear(OLED_COLOR_BLACK);
                OledDrawString("\n    DEFEAT");
                OledUpdate();
                currentState = AGENT_STATE_END_SCREEN;
            }
            currentState = AGENT_STATE_WAITING_TO_SEND;
            turnCounter++;
        }
        break;
    case AGENT_STATE_WAITING_TO_SEND:
        if (event.type == BB_EVENT_ERROR) {
            DecodeError(event);
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            currentState = AGENT_STATE_START;
            ResetGame();
            break;
        }
        if (event.type == BB_EVENT_MESSAGE_SENT) {
            turnCounter++;
            GuessData guessShot;
#ifdef SMART_AI_MODE
            guessShot = FieldAISmartDecideGuess(&oppField, &PrevHit);
#else
            guessShot = FieldAIDecideGuess(&oppField);
#endif
            messageToSend.type = MESSAGE_SHO;
            messageToSend.param0 = guessShot.row;
            messageToSend.param1 = guessShot.col;
            currentState = AGENT_STATE_ATTACKING;
        }
        break;
    case AGENT_STATE_END_SCREEN:
        if (event.type == BB_EVENT_ERROR) {
            DecodeError(event);
        }
        if (event.type == BB_EVENT_RESET_BUTTON) {
            currentState = AGENT_STATE_START;
            ResetGame();
            break;
        }
        break;
    }

    //Send Message
    return messageToSend;
}

void DecodeError(BB_Event event)
{
    /*
    BB_SUCCESS = 0, //0
    BB_ERROR_BAD_CHECKSUM, //1
    BB_ERROR_PAYLOAD_LEN_EXCEEDED, //2
    BB_ERROR_CHECKSUM_LEN_EXCEEDED, //3
    BB_ERROR_CHECKSUM_LEN_INSUFFICIENT, //4
    BB_ERROR_INVALID_MESSAGE_TYPE, //5
    BB_ERROR_MESSAGE_PARSE_FAILURE,
     */
    OledClear(OLED_COLOR_BLACK);
    if (event.param0 == BB_ERROR_BAD_CHECKSUM) {
        OledDrawString("\nBAD CHECKSUM");
    } else if (event.param0 == BB_ERROR_CHECKSUM_LEN_EXCEEDED) {
        OledDrawString("\nCHECKSUM TOO LONG");
    } else if (event.param0 == BB_ERROR_CHECKSUM_LEN_INSUFFICIENT) {
        OledDrawString("\nCHECKSUM TOO SHORT");
    } else if (event.param0 == BB_ERROR_INVALID_MESSAGE_TYPE) {
        OledDrawString("\nINVALID MESSAGE TYPE");
    } else if (event.param0 == BB_ERROR_PAYLOAD_LEN_EXCEEDED) {
        OledDrawString("\nPAYLOAD TOO LONG");
    }
    OledUpdate();

}

AgentState AgentGetState(void)
{
    return currentState;
}

void AgentSetState(AgentState newState)
{
    currentState = newState;
}

void ResetGame(void)
{
    AgentInit();
}

void print_field(void)
{
    FieldPrint_UART(&myField, &oppField);
}