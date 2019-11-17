// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//CMPE13 Support Library
#include "BOARD.h"


// Microchip libraries
#include <xc.h>

// User libraries:
#include "MatrixMath.h"

// Module-level variables:
float one_matrix[3][3] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
};
float one_submatrix[2][2] = {
    {1, 1},
    {1, 1}
};
float identity_matrix[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};
float two_matrix[3][3] = {
    {2, 2, 2},
    {2, 2, 2},
    {2, 2, 2}
};
float six_matrix[3][3] = {
    {6, 6, 6},
    {6, 6, 6},
    {6, 6, 6}
};
float rnd_matrix[3][3] = {
    {5, 2, 3},
    {9, 1, 1},
    {7, 1, 1}
};
float zero_matrix[3][3] = {
    {},
    {},
    {}
};
float result_matrix[3][3];
float result1_matrix[3][3];
float result_submatrix[2][2];
float zero_submatrix[2][2] = {
    {},
    {}
};

// Helper functions

int SubmatrixEquals(float mat1[2][2], float mat2[2][2])
{
    int i;
    for (i = 0; i < 2; i++) {
        int j;
        for (j = 0; j < 2; j++) {
            if (abs(mat1[i][j] - mat2[i][j]) > FP_DELTA) return FALSE;
        }
    }
    return TRUE;

}

int main()
{
    BOARD_Init();

    printf("Beginning Kajeffre's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    int passed = 0;
    int score = 0;
   
    //Matrix equals test
    if (MatrixEquals(one_matrix, one_matrix)) passed++; //one_matrix = one_matrix
    if (!MatrixEquals(one_matrix, zero_matrix)) passed++; // one_matrix != zero_matrix

    printf("PASSED(%i/2): MatrixEquals()\n", passed);
    
    if(passed == 2)score++;

    // Add more tests here!


    // Matrix add test
    passed = 0;
    MatrixAdd(one_matrix, two_matrix, result_matrix); // A + B = B + A
    MatrixAdd(two_matrix, one_matrix, result1_matrix);
    if (MatrixEquals(result_matrix, result1_matrix)) passed++;

    MatrixAdd(two_matrix, zero_matrix, result_matrix); //A + 0 = A
    if (MatrixEquals(result_matrix, two_matrix)) passed++;

    printf("PASSED(%i/2): MatrixAdd()\n", passed);
    if(passed == 2)score++;



    // Matrix multiply
    passed = 0;
    MatrixMultiply(one_matrix, two_matrix, result_matrix); // A * B = 6 matrix

    if (MatrixEquals(result_matrix, six_matrix)) passed++;

    MatrixMultiply(two_matrix, rnd_matrix, result_matrix); //B * A != A * B
    MatrixMultiply(rnd_matrix, two_matrix, result1_matrix); //B * A != A * B

    if (!MatrixEquals(result_matrix, result1_matrix)) passed++;

    printf("PASSED(%i/2): MatrixMultiply() \n", passed);
    if(passed == 2)score++;


    // Matrix scalar add
    passed = 0;
    MatrixScalarAdd((float) 5, one_matrix, result_matrix); // A + 5 = 6 matrix

    if (MatrixEquals(result_matrix, six_matrix)) passed++;

    MatrixScalarAdd((float) 0, one_matrix, result_matrix); // A + 0 = A matrix

    if (MatrixEquals(one_matrix, result_matrix)) passed++;

    printf("PASSED(%i/2): MatrixScalarAdd() \n", passed);
    if(passed == 2)score++;



    // Matrix trace
    passed = 0;
    if ((float) 3 == MatrixTrace(one_matrix)) passed++; // Trace(one_mat) = 3
    if ((float) 0 == MatrixTrace(zero_matrix)) passed++; // Trace(zero_mat) = 0

    printf("PASSED(%i/2): MatrixTrace() \n", passed);
    if(passed == 2)score++;





    // Matrix Transpose
    passed = 0;
    MatrixTranspose(one_matrix, result_matrix); // Transpose(one_mat) = one_mat

    if (MatrixEquals(result_matrix, one_matrix)) passed++;

    MatrixTranspose(rnd_matrix, result_matrix); // Transpose(rnd_mat) != rnd_mat

    if (!MatrixEquals(rnd_matrix, result_matrix)) passed++;

    printf("PASSED(%i/2): MatrixTranspose() \n", passed);
    if(passed == 2)score++;





    //Matrix submatrix
    passed = 0;
    MatrixSubmatrix(0, 0, zero_matrix, result_submatrix); // SubMat( 0, 0, zero_mat) = zero_submat

    if (SubmatrixEquals(result_submatrix, zero_submatrix)) passed++;

    MatrixSubmatrix(0, 0, rnd_matrix, result_submatrix); // SubMat( 0, 0, rnd_mat) != zero_submat

    if (!SubmatrixEquals(zero_submatrix, result_submatrix)) passed++;

    printf("PASSED(%i/2): MatrixSubMatrix() \n", passed);
    if(passed == 2)score++;



    //Matrix determinant
    passed = 0;
    float det = MatrixDeterminant(rnd_matrix);
    if ((float) 2 - FP_DELTA <= det && det <= (float) 2 + FP_DELTA) passed++; // det(rnd_mat) = 2

    det = MatrixDeterminant(one_matrix);
    if ((float) 0 - FP_DELTA <= det && det <= (float) 0 + FP_DELTA) passed++; // det(one_mat) = 0

    printf("PASSED(%i/2): MatrixDeterminant() \n", passed);
    if(passed == 2)score++;




    //Matrix Inverse
    float rnd_inv_mat[3][3] = {
        {0, .5, -.5},
        {-1, -8, 11},
        {1, 4.5, -6.5}
    };
    passed = 0;

    MatrixInverse(rnd_matrix, result_matrix);

    if (MatrixEquals(result_matrix, rnd_inv_mat)) passed++;

    MatrixMultiply(rnd_matrix, rnd_inv_mat, result_matrix); // rnd * rnd^-1 = identity mat

    if (MatrixEquals(result_matrix, identity_matrix)) passed++;
    printf("PASSED(%i/2): MatrixInverse() \n", passed);
    if(passed == 2)score++;

    
    
    //Test Harness Report
    float percent = (float) score / 9 * 100;
    printf("---------------------------\n"
            "%i out of 9 functions passed (%%%.1f)\n\n", score, percent);
            
    //Matrix Print
    float max_matrix[3][3] = {
        {999, 999, 999},
        {9, 0, 0},
        {-999, 0, 1}
    };
    printf("OUTPUT OF PRINTF\n");
    MatrixPrint(max_matrix);
    printf("EXPECTED OUTPUT OF PRINTF \n"
            " ______________________________________\n"
            "|  999.0000  |  999.0000  |  999.0000  |\n"
            " --------------------------------------\n"
            "|    9.0000  |    0.0000  |    0.0000  |\n"
            " --------------------------------------\n"
            "| -999.0000  |    0.0000  |    1.0000  |\n"
            " --------------------------------------\n");
    while (1);
}

