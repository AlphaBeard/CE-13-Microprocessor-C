#include "Field.h"
#include "BOARD.h"
#include <stdio.h>

int main(void)
{

    //INITIALIZE
    BOARD_Init();
    Field test_field;
    Field test_field_opp;
    int success;
    int total_success = 0;
    int test_flag;
    //TEST Field.c HERE
    printf("\nWELCOME TO KAJEFFRE's TEST HARNESS FOR Field.c: \n");


    //TEST FieldInit()
    printf("Testing FieldInit():\n");
    FieldInit(&test_field, &test_field_opp);

    //NO KNOWN BUGS

    //TEST FieldAIPlaceAllBoats())
    printf("Testing FieldAIPlaceAllBoats: \n");
    FieldAIPlaceAllBoats(&test_field);
    FieldPrint_UART(&test_field, &test_field_opp);

    
    //TEST FieldAddBoat()
    //    printf("Testing FieldAddBoat():\n");
    //    success = FieldAddBoat(&test_field, 0, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL);
    //    (success == SUCCESS) ? (total_success++) : (test_flag = 1);
    //    success = FieldAddBoat(&test_field, 1, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_MEDIUM);
    //    (success == SUCCESS) ? (total_success++) : (test_flag = 2);
    //    success = FieldAddBoat(&test_field, 1, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE);
    //    (success == STANDARD_ERROR) ? (total_success++) : (test_flag = 3);
    //    success = FieldAddBoat(&test_field, 0, 6, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);
    //    (success == SUCCESS) ? (total_success++) : (test_flag = 4);
    //
    //    printf("\tTests passed: %d/4\n", total_success);
    //    if (total_success != 4) printf("\tError on test %d\n", test_flag);
    //NO KNOWN BUGS


    //TEST FieldGetSquareStatus()
    printf("Testing FieldGetSquareStatus()\n");
    SquareStatus status;
    total_success = 0;
    test_flag = 0;
    /*      0 1 2 3 4 5 6 7 8 9
     *     ---------------------
     *  0 [ 3 3 3 . . . 3 . . . ]
     *  1 [ 4 4 4 4 . . 3 . . . ]
     *  2 [ . . . . . . 3 . . . ]
     *  3 [ . . . . . . . . . . ]
     *  4 [ . . . . . . . . . . ]
     *  5 [ . . . . . . . . . . ]
     */
    status = FieldGetSquareStatus(&test_field, 0, 0);
    (status == FIELD_SQUARE_SMALL_BOAT) ? (total_success++) : (test_flag = 1);
    status = FieldGetSquareStatus(&test_field, 8, 0);
    (status == FIELD_SQUARE_INVALID) ? (total_success++) : (test_flag = 2);
    status = FieldGetSquareStatus(&test_field, 0, 6);
    (status == FIELD_SQUARE_SMALL_BOAT) ? (total_success++) : (test_flag = 3);
    status = FieldGetSquareStatus(&test_field, 1, 6);
    (status == FIELD_SQUARE_SMALL_BOAT) ? (total_success++) : (test_flag = 4);

    printf("\tTests passed: %d/4\n", total_success);
    if (total_success != 4) printf("\tError on test %d\n", test_flag);
    //NO KNOWN BUGS


    //TEST FieldRegisterEnemyAttack()
    printf("Testing FieldRegisterEnemyAttack()\n");
    total_success = 0;
    test_flag = 0;
    GuessData opponent_guess;

    opponent_guess.col = 0;
    opponent_guess.row = 0;
    status = FieldRegisterEnemyAttack(&test_field, &opponent_guess);
    (status == FIELD_SQUARE_SMALL_BOAT && opponent_guess.result == RESULT_HIT) ? (total_success++) : (test_flag = 1);
    opponent_guess.col = 1;
    opponent_guess.row = 0;
    status = FieldRegisterEnemyAttack(&test_field, &opponent_guess);
    (status == FIELD_SQUARE_SMALL_BOAT && opponent_guess.result == RESULT_HIT) ? (total_success++) : (test_flag = 2);
    opponent_guess.col = 2;
    opponent_guess.row = 0;
    status = FieldRegisterEnemyAttack(&test_field, &opponent_guess);
    (status == FIELD_SQUARE_SMALL_BOAT && opponent_guess.result == RESULT_SMALL_BOAT_SUNK) ? (total_success++) : (test_flag = 3);
    opponent_guess.col = 10;
    opponent_guess.row = 0;
    status = FieldRegisterEnemyAttack(&test_field, &opponent_guess);
    (status == FIELD_SQUARE_INVALID) ? (total_success++) : (test_flag = 4);

    printf("\tTests passed: %d/4\n", total_success);
    if (total_success != 4) printf("\tError on test %d\n", test_flag);
    //NO KNOWN BUGS


    //TEST FieldAIPlaceAllBoats()
    printf("Testing FieldAIPlaceAllBoats()\n");
    total_success = 0;
    test_flag = 0;

    success = FieldAIPlaceAllBoats(&test_field_opp);
    (success == SUCCESS) ? (total_success++) : (test_flag = 1);

    printf("\tTests passed: %d/1\n", total_success);
    if (total_success != 1) printf("\tError on test %d\n", test_flag);
    printf("\tCHECK OPPONENT FIELD FOR BEHAVIOR:\n");
    FieldPrint_UART(&test_field, &test_field_opp);
    //BUG: The entire field gets filled with Large Boats



    //TEST FieldUpdateKnowledge()
    //    printf("Testing FieldUpdateKnowledge()\n");
    //    total_success = 0;
    //    test_flag = 0;
    //    GuessData opp_guess;
    //    
    //    status = FieldUpdateKnowledge(&test_field, &opp_guess);


    //TEST FieldGetBoatStates()
    printf("Testing FieldGetBoatStates()\n");
    total_success = 0;
    test_flag = 0;
    uint8_t boat_states;

    boat_states = FieldGetBoatStates(&test_field);
    (boat_states == 0b00000011) ? (total_success++) : (test_flag = 1);
    printf("\tTests passed: %d/1\n", total_success);
    if (total_success != 1) printf("\tError on test %d\n", test_flag);
    //BUG: Add boats not adding lives to field


    //TEST FieldAIDecideGuess()
    printf("Testing FieldAIDecideGuess()\n");
    total_success = 0;
    test_flag = 0;


    printf("\tTests passed: %d/1\n", total_success);
    if (total_success != 1) printf("\tError on test %d\n", test_flag);


    //TEST FieldSetSquareStatus()
    printf("Testing FieldGetSquareStatus()\n");
    total_success = 0;
    test_flag = 0;

    status = FieldSetSquareStatus(&test_field_opp, 0, 0, FIELD_SQUARE_CURSOR);
    (status == FIELD_SQUARE_UNKNOWN) ? (total_success++) : (test_flag = 1);
    printf("CURSOR FUNCTIONALITY CHECK\n");
    FieldPrint_UART(&test_field, &test_field_opp);

    FieldSetSquareStatus(&test_field_opp, 0, 0, status);
    status = FieldSetSquareStatus(&test_field_opp, 1, 0, FIELD_SQUARE_CURSOR);
    (status == FIELD_SQUARE_UNKNOWN) ? (total_success++) : (test_flag = 2);
    FieldPrint_UART(&test_field, &test_field_opp);

    FieldSetSquareStatus(&test_field_opp, 1, 0, status);
    status = FieldSetSquareStatus(&test_field_opp, 2, 0, FIELD_SQUARE_CURSOR);
    (status == FIELD_SQUARE_UNKNOWN) ? (total_success++) : (test_flag = 3);
    FieldPrint_UART(&test_field, &test_field_opp);

    status = FieldSetSquareStatus(&test_field_opp, 9, 0, FIELD_SQUARE_CURSOR);
    (status == FIELD_SQUARE_UNKNOWN) ? (total_success++) : (test_flag = 4);
    FieldPrint_UART(&test_field, &test_field_opp);

    printf("\tTests passed: %d/4\n", total_success);
    if (total_success != 4) printf("\tError on test %d\n", test_flag);
    //NO KNOWN BUGS

    while (1);
}
