#include "MatrixMath.h"

// FP_DELTA for equals tolerance

#define ROW 3
#define COL 3
#define TRUE 1
#define FALSE 0

int MatrixEquals(float mat1[3][3], float mat2[3][3])
{



    int i;
    for (i = 0; i < ROW; i++) {
        int j;
        for (j = 0; j < COL; j++) {
            if (abs(mat1[i][j] - mat2[i][j]) > FP_DELTA) return FALSE; // Jump out of program if not equal  

        }
    }
    return TRUE;
}

void MatrixPrint(float mat[3][3])
{
    int i;

    printf(" ______________________________________\n");
    for (i = 0; i < ROW; i++) {
        int j;
        for (j = 0; j < COL; j++) {
            printf("| % 9.4f  ", mat[i][j]);
        }
        printf("|\n");
        printf(" --------------------------------------\n");
    }

}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int i;
    for (i = 0; i < ROW; i++) {
        int j;
        for (j = 0; j < COL; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }

    }
}

//helper function for matrixmultiply

static float VectorDotProduct(float mat1[3], float mat2[3]) // multiplys vectors of length 3
{
    int i;
    float result = 0;
    for (i = 0; i < ROW; i++) {
        result += mat1[i] * mat2[i];
    }
    return result;
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int i;
    float mat2vector[3];
    for (i = 0; i < ROW; i++) {
        int j;
        for (j = 0; j < COL; j++) {
            int l;
            for (l = 0; l < ROW; l++) // Copy the COLumn i want into a new vector to pass to dotprdct
            {
                mat2vector[l] = mat2[l][j];
            }
            //The first matrix here doesn't need to be copied because of ROW major order, the dot
            //product function will grab the next three elements in the array passed to it
            result[i][j] = VectorDotProduct(&mat1[i][0], mat2vector);

        }

    }
}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    int i;
    for (i = 0; i < ROW; i++) {
        int j;
        for (j = 0; j < COL; j++) {
            result[i][j] = mat[i][j] + x;
        }

    }
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    int i;
    for (i = 0; i < ROW; i++) {
        int j;
        for (j = 0; j < COL; j++) {
            result[i][j] = mat[i][j] * x;
        }

    }
}
// sum of diagonal indexes

float MatrixTrace(float mat[3][3])
{
    int i;
    int j;
    float result = 0;
    for (i = 0, j = 0; i < ROW; i++, j++) {
        result += mat[i][j];
    }
    return result;
}

void MatrixTranspose(float mat[3][3], float result[3][3])
{
    int i;
    for (i = 0; i < ROW; i++) {
        int j;
        for (j = 0; j < COL; j++) {
            result[j][i] = mat[i][j];
        }

    }
}

// k and l correspond to ROW and COLumn iterating through the 3x3 matrix, s and f are the ROW
// and COLumn of the 2 by 2 matrix. The function only wants to increase the f and s values
// when actually assigning one of the 3 by 3 values to an index in the result

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    int k;
    int s = 0, f = 0;
    for (k = 0; k < ROW; k++) {
        if (k == i) continue;
        f = 0;
        int l;
        for (l = 0; l < COL; l++) {
            if (l == j) continue;
            result[s][f] = mat[k][l];
            f++;
        }
        s++;
    }
}

//Helper function

static float TwoByDet(float mat[2][2])
{
    float answer = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    return answer;
}

float MatrixDeterminant(float mat[3][3])
{
    float result = 0;
    float submat[2][2];
    int i;
    for (i = 0; i < ROW; i++) {
        MatrixSubmatrix(0, i, mat, submat);
        if (i == 1) {
            result -= mat[0][i] * TwoByDet(submat);
            continue;
        }

        result += mat[0][i] * TwoByDet(submat);
    }
    return result;

}

void MatrixInverse(float mat[3][3], float result[3][3])
{
    int i;
    float subMat[2][2];
    float cofactorMat[3][3];
    float cofactorMatTranspose[3][3];

    //get cofactor matrix
    for (i = 0; i < ROW; i++) {
        int j;
        for (j = 0; j < COL; j++) {
            MatrixSubmatrix(i, j, mat, subMat);
            //if is even
            if ((i + j) % 2 == 0) {

                cofactorMat[i][j] = TwoByDet(subMat);
                continue;
            }
            cofactorMat[i][j] = TwoByDet(subMat);
            if (cofactorMat[i][j] == 0) continue;
            cofactorMat[i][j] *= -1;

        }
    }

    MatrixTranspose(cofactorMat, cofactorMatTranspose); // get transpose of cofactor matrix
    float det = 1 / MatrixDeterminant(mat); // multiply by 1/det(mat))
    MatrixScalarMultiply(det, cofactorMatTranspose, result);
}