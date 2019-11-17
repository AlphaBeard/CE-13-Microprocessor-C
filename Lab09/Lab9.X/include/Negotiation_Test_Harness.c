#include "Negotiation.h"
#include <stdio.h>
#include "Message.h"
#include <stdlib.h>
#include "BOARD.h"

// MODULE LEVEL STRUCTS AND ENUMS

typedef struct {
    NegotiationData a;
    NegotiationData b;
    NegotiationData hash_a;
} Agent;

//HELPER FUNCTIONS
int NegotiationExchange(Agent *agentA, Agent *agentB);
void CheckResult(Agent *agentA, Agent *agentB, int success);

int main(void)
{
    //TEST HARNESS Negotiation.c
    printf("TEST HARNESS Negotiation.c:\n");
    Agent agentA;
    Agent agentB;
    int i;
    for (i = 0; i < 50; i++) {
        int success = NegotiationExchange(&agentA, &agentB);
        CheckResult(&agentA, &agentB, success);
    }
    while (1);
}

int NegotiationExchange(Agent *agentA, Agent *agentB)
{
    agentA->a = rand();
    agentA->hash_a = NegotiationHash(agentA->a);

    agentB->hash_a = agentA->hash_a;
    agentB->b = rand();

    agentA->b = agentB->b;

    agentB->a = agentA->a;

    int success = NegotiationVerify(agentB->a, agentB->hash_a);
    return success;
}

void CheckResult(Agent *agentA, Agent *agentB, int success)
{
    if (success == TRUE) {
        NegotiationOutcome outcome = NegotiateCoinFlip(agentB->a, agentB->b);
        switch (outcome) {
        case HEADS:
            printf("HEADS\n");
            break;
        case TAILS:
            printf("TAILS\n");
            break;
        default:
            printf("ERROR STATE\n");
            break;
        }
    } else if (success == FALSE) {
        printf("PLAYER A CHEATED\n");
    }
}