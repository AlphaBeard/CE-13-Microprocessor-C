#include "Negotiation.h"
#include "BOARD.h"

//Helper Function
int GetParity(NegotiationData n)
{
    int parity = 0;
    while (n != 0) {
        //flip parity each time
        if (n & 1 == 1) {
            parity = !parity;
        }
        n = n >> 1;
    }
    return parity;
}

NegotiationData NegotiationHash(NegotiationData secret)
{
    NegotiationData hash = (secret * secret) % PUBLIC_KEY;
    return hash;
}

int NegotiationVerify(NegotiationData secret, NegotiationData commitment)
{
    NegotiationData commitment_check = NegotiationHash(secret);
    if (commitment_check == commitment) {
        return TRUE;
    } else {
        return FALSE;
    }
}


NegotiationOutcome NegotiateCoinFlip(NegotiationData A, NegotiationData B)
{
    NegotiationData coin_flip = A ^ B;

    int parity = GetParity(coin_flip);
    if (parity == 1) {
        return HEADS;
    } else {
        return TAILS;
    }
}
