// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "rpn.h"

int main()
{
    BOARD_Init();
    int error;

    printf("\n###### Beginning Kajeffre's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
//    
    char test0[] = " ";
    double result0;
//    double expected0 = 2;
//    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
//    error = RPN_Evaluate(test0, &result0);
//    if (error) {
//        printf("   Failed, RPN_Evaluate produced an error\n");
//    } else if (result0 != expected0) {
//        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
//    } else {
//        printf("   Success!\n");
//    }
//
    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "123456\b\b\b\b\b\b\b\b\b\b\b\b\b12";
    // 12345656
    int length = ProcessBackspaces(test_pb1);
    printf("result    : %s, of length: %i\n", test_pb1, length);
    printf("should be : 1234\n");

    
//    error = RPN_Evaluate(test0, &result0);
//    printf("\nresult: %f\n\tError if non zero: %i", result0, error);
//    
    while (1);
}


