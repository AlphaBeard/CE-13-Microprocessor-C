//Kyle, Jeffrey  Kajeffre

// Standard libraries
#include <stdio.h>
#include <math.h>
//#include <xc.h>

//User libraries:
//#include "BOARD.h"


// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);
//add more prototypes here
int validInput(char c);
double Subtract(double operand1, double operand2);
double Divide(double operand1, double operand2);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);
double Round(double operand);




void CalculatorRun(void)
{
    printf("\n\nWelcome to KYLE's calculator program! Compiled at %s %s\n\n", __DATE__, __TIME__);


    // Your code here
    int run = 1;

    while (run) {

        int secondOperand = 1;

        int inputCheckLoop = 1;
        double answer = 0;

        char op;
        char enterChar;


        //Checks for invalid inputs
        while (inputCheckLoop) {
            printf("Enter a mathematical operation to perform (*,/,+,-,v,a,c,f,t,r): ");

            scanf("%c%c", &op, &enterChar);

            if (validInput(op) == 0) {
                printf("\n   Invalid Input\n");

            } else {
                inputCheckLoop = 0;
            }


        }
        // flag if the operation uses one operand
        if (op == 'a' || op == 'f' || op == 'c' || op == 't' || op == 'r') secondOperand = 0;


        //get operand 1
        double operand1;

        printf("\n    Please enter operand 1: ");
        scanf("%lf%c", &operand1, &enterChar);



        //get operand 2 if second operand used and error handle a divide by zero
        double operand2;

        if (secondOperand) {
            printf("\n    Please enter operand 2: ");
            scanf("%lf%c", &operand2, &enterChar);
            if (op == '/' && operand2 == 0) {
                printf("\n    Divide by zero error!\n \n");
                continue;
            };
        }


        //do op
        if (op == '+') answer = Add(operand1, operand2);
        if (op == '-') answer = Subtract(operand1, operand2);
        if (op == '/') answer = Divide(operand1, operand2);
        if (op == '*') answer = Multiply(operand1, operand2);
        if (op == 'a') answer = AbsoluteValue(operand1);
        if (op == 'f') answer = CelsiusToFahrenheit(operand1);
        if (op == 'm') answer = Average(operand1, operand2);
        if (op == 'c') answer = FahrenheitToCelsius(operand1);
        if (op == 't') answer = Tangent(operand1);
        if (op == 'r') answer = Round(operand1);

        //Different print styles based on operation    
        if (secondOperand) {
            printf("\n    Result of (%f %c %f): %f \n\n", operand1, op, operand2, answer);

        } else {
            if (op == 'a') printf("\n    Result of |%f| : %f \n\n", operand1, answer);
            if (op == 'f') printf("\n    Result of (%f deg ->F) : %f \n\n", operand1, answer);
            if (op == 'c') printf("\n    Result of (%f deg ->C) : %f \n\n", operand1, answer);
            if (op == 't') printf("\n    Result of tan(%f) : %f \n\n", operand1, answer);
            if (op == 'r') printf("\n    Result of %f rounded: %f \n\n", operand1, answer);

        }

    }
}

int validInput(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '*' || c == 'm' || c == 'a' || 
        c == 'c' || c == 'f' || c == 't' || c == 'r') {
        return 1;
    } else {
        return 0;
    }
}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{
    return operand1 + operand2;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
    //  Your code here
    return operand1 - operand2;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2)
{
    //  Your code here
    return operand1 * operand2;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
    //  Your code here
    return operand1 / operand2;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand1)
{
    //  Your code here

    if (operand1 < 0) {
        operand1 *= -1;
    }
    return operand1;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    //  Your code here
    return (operand * (double) 9 / 5) + 32;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand)
{
    //  Your code here
    return (operand - 32) * (double) 5 / 9;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
    //  Your code here
    return (operand1 + operand2) / 2;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
//USE M_PI FOR PI

double Tangent(double operand)
{
    //  Your code here
    return tan((operand / 180) * 3.14159);
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{
    //  Your code here
    int answer;
    //   4.5 -> 5
    //  -4.5 -> -5
    if (operand >= 0) {
        answer = (operand + .5);
    } else {
        answer = (operand - .5);
    }
    return answer;
}



