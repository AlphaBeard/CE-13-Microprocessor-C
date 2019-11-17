// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning Kajeffre's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!

    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
        StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }

    //test StackInit:   



    // test StackIsFull() 
    printf("Does StackIsFull() return False if not full and vice versa?\n");
    stack.currentItemIndex = 19;

    if (StackIsFull(&stack) == TRUE) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }

    
    
    
    // test StackPush() 
    printf("Does StackPush return a success?\n");
    stack.currentItemIndex = -1;

    double testpushvalue = 7.0;

    if (StackPush(&stack, testpushvalue) == SUCCESS) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }

    stack.initialized = FALSE;
    
    // test StackSize() 
    printf("Does StackGetSize() return size of 1 or a Size Error?\n");
    int size = StackGetSize(&stack);
    printf("Stack Size: %i ", size);
    if (size == 1) {
        printf("\npassed\n");
    } else if(size == SIZE_ERROR){
        printf("\npassed\n");
    }else{
        printf("failed\n");
    }
    
    
    
    // test StackPop() 
    printf("Does StackPop() return a success?\n");
    double testpopvalue;
    int pass = StackPop(&stack, &testpopvalue);

    if (testpopvalue == testpushvalue) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    
    
    
    // test StackIsEmpty() 
    printf("Does StackIsEmpty() return a success?\n");
    if (StackIsEmpty(&stack) == TRUE) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }


    while (1);
    return 0;
}


