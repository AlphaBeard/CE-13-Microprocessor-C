#include "rpn.h"
#include "BOARD.h"
#include "stack.h"
#include <string.h>
#include <stdio.h>

int RPN_Evaluate(char * rpn_string, double * result)
{

    //initialize stack
    struct Stack stack;
    StackInit(&stack);

    //Declare result
    double tmp_result = 0;
    char *ptr;
    ptr = strtok(rpn_string, " "); // point to first address

    //ERROR if only one value entered
    if (ptr[1] == '\n') {
        return RPN_ERROR_STACK_UNDERFLOW;
    }
    
    while (ptr != NULL) {

        //If number or negative number
        if (isdigit(*ptr) | (*ptr == '-' && isdigit(ptr[1]))) {

            //Too many numbers trying to be put on stack
            if (StackIsFull(&stack)) {

                return RPN_ERROR_STACK_OVERFLOW;
            }

            double value = atof(ptr);
            StackPush(&stack, value); //Push number on stack 

        } else if (*ptr == '+') {
            //ERROR if not enough operands before operator
            if (StackGetSize(&stack) < 2) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            double operand1;
            double operand2;
            StackPop(&stack, &operand1);
            StackPop(&stack, &operand2);
            tmp_result = operand1 + operand2; // Add numbers and push back
            StackPush(&stack, tmp_result);

        } else if (*ptr == '-') {
            if (StackGetSize(&stack) < 2) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            double operand1;
            double operand2;
            StackPop(&stack, &operand1);
            StackPop(&stack, &operand2);
            tmp_result = operand2 - operand1; // subtract numbers and push back
            StackPush(&stack, tmp_result);

        } else if (*ptr == '*') {
            if (StackGetSize(&stack) < 2) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            double operand1;
            double operand2;
            StackPop(&stack, &operand1);
            StackPop(&stack, &operand2);
            tmp_result = operand1 * operand2; // multiply numbers and push back
            StackPush(&stack, tmp_result);

        } else if (*ptr == '/') {
            if (StackGetSize(&stack) < 2) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            double operand1;
            double operand2;
            //ERROR if divide by zero
            if (operand1 == 0) {
                return RPN_ERROR_DIVIDE_BY_ZERO;
            }
            StackPop(&stack, &operand1);
            StackPop(&stack, &operand2);
            tmp_result = operand2 / operand1; // divide numbers and push back
            StackPush(&stack, tmp_result);

            //ERROR if input is not a digit or operand or the last entry is a space
        } else if (!(isdigit(*ptr) || *ptr == '/' || *ptr == '*' || *ptr == '+'
                || *ptr == '-' || *ptr == '\n')) {
            return RPN_ERROR_INVALID_TOKEN;
        }

        ptr = strtok(NULL, " ");
        *result = tmp_result;


    }

    //ERROR if stack is empty at end of parse
    if (StackIsEmpty(&stack)) {
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    } else // ERROR if stack has more than just one result at end of parse
        if (StackGetSize(&stack) > 1) {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }


    return RPN_NO_ERROR;
}

int ProcessBackspaces(char *rpn_sentence)
{

    //iterate through whole string
    int i;
    for (i = 0; rpn_sentence[i] != NULL; i++) {

        if (rpn_sentence[i] == '\b') {

            //Account for having backspace and no other characters
            if (rpn_sentence[i - 1] == NULL) {
                int l;
                for (l = i; rpn_sentence[l] != NULL; l++) {

                    //If theres no char left of backspace, shift all characters left
                    rpn_sentence[l] = rpn_sentence[l + 1];

                }
                //set last point to zero
                rpn_sentence[l] = NULL;
                continue;

            }

            // Account for consecutive backspaces
            int is_next_backspace = 0;
            if (rpn_sentence[i + 1] == '\b') {
                is_next_backspace = 1;

            }

            int k;
            for (k = i; rpn_sentence[k] != NULL; k++) {

                rpn_sentence[k - 1] = rpn_sentence[k + 1];

            }

            rpn_sentence[k - 2] = NULL;
            rpn_sentence[k - 1] = NULL;

            //If there is another backspace behind the current one, reset the pointer back one
            if (is_next_backspace) {
                i -= 2;
            }
        }
    }

    return strlen(rpn_sentence);

}