#include "Field.h"
#include "BOARD.h"
#include <stdio.h>
#include <stdlib.h>
#include "Ascii.h"

#define SIX 6
#define ZERO 0
#define ONE 1
#define TWO 2

static uint8_t DirectionStates = 0;
static GuessData originalHit;
static int direction = 4;

void FieldPrint_UART(Field *own_field, Field * opp_field)
{
    int i;
    int y;
    int q;
    for (i = 0; i < FIELD_ROWS + ONE; i++) {
        if (i == 0) {
            printf(" ");
            for (q = 0; q < FIELD_COLS; q++) {
                printf("--");
            }
            printf("-");
            printf("\t   ");
            for (q = 0; q < FIELD_COLS; q++) {
                printf("--");
            }
            printf("-\n");
        } else {
            printf("[");
            for (y = 0; y < FIELD_COLS; y++) {
                if (own_field->grid[i - ONE][y] == FIELD_SQUARE_EMPTY) {
                    printf(" .");
                } else if ((own_field->grid[i - ONE][y] >= FIELD_SQUARE_SMALL_BOAT)
                        && (own_field->grid[i - ONE][y] <= FIELD_SQUARE_HUGE_BOAT)) {
                    printf(" \x01");
                } else if (own_field->grid[i - ONE][y] == FIELD_SQUARE_HIT) {
                    printf(" X");
                } else if (own_field->grid[i - ONE][y] == FIELD_SQUARE_MISS) {
                    printf(" O");
                }


            }
            printf(" ]\t  [");
            for (y = 0; y < FIELD_COLS; y++) {
                if (opp_field->grid[i - ONE][y] == FIELD_SQUARE_CURSOR) {
                    printf(" *");
                } else if (opp_field->grid[i - ONE][y] == FIELD_SQUARE_HIT) {
                    printf(" X");
                } else if (opp_field->grid[i - ONE][y] == FIELD_SQUARE_EMPTY) {
                    printf("  ");
                } else {
                    printf(" .");
                }
            }
            printf(" ]\n");
        }
    }
}

void FieldInit(Field *own_field, Field * opp_field)
{
    int i;
    int y;
    for (i = ZERO; i < FIELD_ROWS; i++) {
        for (y = ZERO; y < FIELD_COLS; y++) {
            own_field->grid[i][y] = FIELD_SQUARE_EMPTY;
            opp_field->grid[i][y] = FIELD_SQUARE_UNKNOWN;
        }
    }
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col)
{
    if (((row >= FIELD_ROWS) || (row < ZERO)) || ((col < ZERO) || (col >= FIELD_COLS))) {
        return FIELD_SQUARE_INVALID;
    } else {
        return f->grid[row][col];
    }
    return f->grid[row][col];
}

SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p)
{
    if (((row >= FIELD_ROWS) || (row < ZERO)) || ((col < ZERO) || (col >= FIELD_COLS))) {
        return FIELD_SQUARE_INVALID;
    } else {
        SquareStatus statusToReturn = f->grid[row][col];
        f->grid[row][col] = p;
        return statusToReturn;
    }
}

uint8_t FieldAddBoat(Field *f, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type)
{
    if (((row >= FIELD_ROWS) || (row < ZERO)) || ((col < ZERO) || (col >= FIELD_COLS))) {
        return STANDARD_ERROR;
    }
    if (!((f->grid[row][col] == FIELD_SQUARE_EMPTY) || (f->grid[row][col] == FIELD_SQUARE_UNKNOWN))) {
        return STANDARD_ERROR;
    }
    int boatSize;
    int squareType;
    if (boat_type == FIELD_BOAT_TYPE_SMALL) {
        boatSize = FIELD_BOAT_SIZE_SMALL;
        f->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
        squareType = FIELD_SQUARE_SMALL_BOAT;
    } else if (boat_type == FIELD_BOAT_TYPE_MEDIUM) {
        boatSize = FIELD_BOAT_SIZE_MEDIUM;
        f->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
        squareType = FIELD_SQUARE_MEDIUM_BOAT;
    } else if (boat_type == FIELD_BOAT_TYPE_LARGE) {
        boatSize = FIELD_BOAT_SIZE_LARGE;
        f->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
        squareType = FIELD_SQUARE_LARGE_BOAT;
    } else if (boat_type == FIELD_BOAT_TYPE_HUGE) {
        boatSize = FIELD_BOAT_SIZE_HUGE;
        f->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
        squareType = FIELD_SQUARE_HUGE_BOAT;
    }
    if (dir == FIELD_DIR_SOUTH) {
        if ((row + boatSize) >= FIELD_ROWS) {
            return STANDARD_ERROR;
        } else {
            int i;
            for (i = 0; i < boatSize; i++) {
                if (!((f->grid[row + i][col] == FIELD_SQUARE_EMPTY) || (f->grid[row + i][col] == FIELD_SQUARE_UNKNOWN))) {
                    return STANDARD_ERROR;
                }
            }
            for (i = 0; i < boatSize; i++) {
                f->grid[row + i][col] = squareType;
            }
            return SUCCESS;
        }
    } else if (dir == FIELD_DIR_EAST) {
        if ((col + boatSize) >= FIELD_COLS) {
            return STANDARD_ERROR;
        } else {
            int i;
            for (i = 0; i < boatSize; i++) {
                if (!((f->grid[row][col + i] == FIELD_SQUARE_EMPTY) || (f->grid[row][col + i] == FIELD_SQUARE_UNKNOWN))) {
                    return STANDARD_ERROR;
                }
            }
            for (i = 0; i < boatSize; i++) {
                f->grid[row][col + i] = squareType;
            }

            return SUCCESS;
        }
    } else {
        return STANDARD_ERROR;
    }
    return STANDARD_ERROR;
}

SquareStatus FieldRegisterEnemyAttack(Field *f, GuessData *gData)
{
    int previousSquareStatus = f->grid[gData->row][gData->col];
    if (((gData->row >= FIELD_ROWS) || (gData->row < ZERO)) || ((gData->col < ZERO) || (gData->col >= FIELD_COLS))) {
        gData->result == RESULT_MISS;
        return FIELD_SQUARE_INVALID;
    }
    if (f->grid[gData->row][gData->col] == FIELD_SQUARE_SMALL_BOAT) {
        f->smallBoatLives--;
        if (f->smallBoatLives == ZERO) {
            gData->result = RESULT_SMALL_BOAT_SUNK;
        } else {
            gData->result = RESULT_HIT;
        }
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
    } else if (f->grid[gData->row][gData->col] == FIELD_SQUARE_MEDIUM_BOAT) {
        f->mediumBoatLives--;
        if (f->mediumBoatLives == ZERO) {
            gData->result = RESULT_MEDIUM_BOAT_SUNK;
        } else {
            gData->result = RESULT_HIT;
        }
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
    } else if (f->grid[gData->row][gData->col] == FIELD_SQUARE_LARGE_BOAT) {
        f->largeBoatLives--;
        if (f->largeBoatLives == ZERO) {
            gData->result = RESULT_LARGE_BOAT_SUNK;
        } else {
            gData->result = RESULT_HIT;
        }
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
    } else if (f->grid[gData->row][gData->col] == FIELD_SQUARE_HUGE_BOAT) {
        f->hugeBoatLives--;
        if (f->hugeBoatLives == ZERO) {
            gData->result = RESULT_HUGE_BOAT_SUNK;
        } else {
            gData->result = RESULT_HIT;
        }
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
    } else {
        f->grid[gData->row][gData->col] = FIELD_SQUARE_MISS;
        gData->result = RESULT_MISS;
    }
    return previousSquareStatus;
}

SquareStatus FieldUpdateKnowledge(Field *f, const GuessData * gData)
{
    int previousSquareStatus = f->grid[gData->row][gData->col];
    if (gData->result == RESULT_SMALL_BOAT_SUNK) {
        f->smallBoatLives = ZERO;
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
    } else if (gData->result == RESULT_MEDIUM_BOAT_SUNK) {
        f->mediumBoatLives = ZERO;
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
    } else if (gData->result == RESULT_LARGE_BOAT_SUNK) {
        f->largeBoatLives = ZERO;
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
    } else if (gData->result == RESULT_HUGE_BOAT_SUNK) {
        f->hugeBoatLives = ZERO;
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
    } else if (gData->result == RESULT_HIT) {
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
    } else {
        f->grid[gData->row][gData->col] = FIELD_SQUARE_EMPTY;
    }
    return previousSquareStatus;
}

uint8_t FieldGetBoatStates(const Field * f)
{
    uint8_t boatStates = ZERO;
    if (f->smallBoatLives > ZERO) {
        boatStates |= FIELD_BOAT_STATUS_SMALL;
    }
    if (f->mediumBoatLives > ZERO) {
        boatStates |= FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->largeBoatLives > ZERO) {
        boatStates |= FIELD_BOAT_STATUS_LARGE;
    }
    if (f->hugeBoatLives > ZERO) {
        boatStates |= FIELD_BOAT_STATUS_HUGE;
    }
    return boatStates;
}

uint8_t FieldAIPlaceAllBoats(Field * f)
{
    int boatAddSuccessful;
    int boatType = FIELD_BOAT_TYPE_SMALL;
    while (boatType <= FIELD_BOAT_TYPE_HUGE) {
        int row = rand() % FIELD_ROWS;
        int col = rand() % FIELD_COLS;
        int dir = rand() % 2;
        boatAddSuccessful = FieldAddBoat(f, row, col, dir, boatType);
        if (boatAddSuccessful == SUCCESS) boatType++;
    }
    return SUCCESS;

}

GuessData FieldAISmartDecideGuess(const Field * f, GuessData *PrevHit)
{
    GuessData SmartGuess;
    //    static int dir;
    //    if (DirectionStates != 0) {
    //        // North 0
    //        // East 1
    //        // South 2
    //        // West 3
    //        do {
    //            if (dir == 0) {
    //                SmartGuess.row = PrevHit->row - ONE;
    //                SmartGuess.col = PrevHit->col;
    //                DirectionStates &= 0b00001110;
    //            } else if (dir == 1) {
    //                SmartGuess.row = PrevHit->row;
    //                SmartGuess.col = PrevHit->col + ONE;
    //                DirectionStates &= 0b00001101;
    //            } else if (dir == 2) {
    //                SmartGuess.row = PrevHit->row + ONE;
    //                SmartGuess.col = PrevHit->col;
    //                DirectionStates &= 0b00001011;
    //            } else if (dir == 3) {
    //                SmartGuess.row = PrevHit->row;
    //                SmartGuess.col = PrevHit->col - ONE;
    //                DirectionStates &= 0b00000111;
    //            }
    //        } while (f->grid[SmartGuess.row][SmartGuess.col] != FIELD_SQUARE_UNKNOWN);
    //
    //
    //    } else {
    //        dir = rand() % 4;
    //        if (PrevHit->result != RESULT_MISS) {
    //            DirectionStates &= 0x0F;
    //            return;
    //        }
    //        SmartGuess = FieldAIDecideGuess(f);
    //    }
    //    return SmartGuess;
    if (PrevHit->result == RESULT_MISS) {
        if (direction != 4) {
            PrevHit->col = originalHit.col;
            PrevHit->row = originalHit.row;
            PrevHit->result = originalHit.result;
            do {
                direction = rand() % 4;
                if (direction == 0) {
                    SmartGuess.row = PrevHit->row - ONE;
                    SmartGuess.col = PrevHit->col;
                } else if (direction == 1) {
                    SmartGuess.row = PrevHit->row;
                    SmartGuess.col = PrevHit->col + ONE;
                } else if (direction == 2) {
                    SmartGuess.row = PrevHit->row + ONE;
                    SmartGuess.col = PrevHit->col;
                } else if (direction == 3) {
                    SmartGuess.row = PrevHit->row;
                    SmartGuess.col = PrevHit->col - ONE;
                }
            } while (f->grid[SmartGuess.row][SmartGuess.col] != FIELD_SQUARE_UNKNOWN);
        } else {
            SmartGuess = FieldAIDecideGuess(f);
            direction = 4;
        }
    } else if (PrevHit->result > RESULT_HIT) {
        SmartGuess = FieldAIDecideGuess(f);
        direction = 4;
    } else {
        if (direction == 4) {
            originalHit.col = PrevHit->col;
            originalHit.row = PrevHit->row;
            originalHit.result = PrevHit->result;
            do {
                direction = rand() % 4;
                if (direction == 0) {
                    SmartGuess.row = PrevHit->row - ONE;
                    SmartGuess.col = PrevHit->col;
                } else if (direction == 1) {
                    SmartGuess.row = PrevHit->row;
                    SmartGuess.col = PrevHit->col + ONE;
                } else if (direction == 2) {
                    SmartGuess.row = PrevHit->row + ONE;
                    SmartGuess.col = PrevHit->col;
                } else if (direction == 3) {
                    SmartGuess.row = PrevHit->row;
                    SmartGuess.col = PrevHit->col - ONE;
                }
            } while (f->grid[SmartGuess.row][SmartGuess.col] != FIELD_SQUARE_UNKNOWN);
        } else {
            if (direction == 0) {
                SmartGuess.row = PrevHit->row - ONE;
                SmartGuess.col = PrevHit->col;
            } else if (direction == 1) {
                SmartGuess.row = PrevHit->row;
                SmartGuess.col = PrevHit->col + ONE;
            } else if (direction == 2) {
                SmartGuess.row = PrevHit->row + ONE;
                SmartGuess.col = PrevHit->col;
            } else if (direction == 3) {
                SmartGuess.row = PrevHit->row;
                SmartGuess.col = PrevHit->col - ONE;
            }
            if (f->grid[SmartGuess.row][SmartGuess.col] != FIELD_SQUARE_UNKNOWN) {
                PrevHit->col = originalHit.col;
                PrevHit->row = originalHit.row;
                PrevHit->result = originalHit.result;
                do {
                    direction = rand() % 4;
                    if (direction == 0) {
                        SmartGuess.row = PrevHit->row - ONE;
                        SmartGuess.col = PrevHit->col;
                    } else if (direction == 1) {
                        SmartGuess.row = PrevHit->row;
                        SmartGuess.col = PrevHit->col + ONE;
                    } else if (direction == 2) {
                        SmartGuess.row = PrevHit->row + ONE;
                        SmartGuess.col = PrevHit->col;
                    } else if (direction == 3) {
                        SmartGuess.row = PrevHit->row;
                        SmartGuess.col = PrevHit->col - ONE;
                    }
                } while (f->grid[SmartGuess.row][SmartGuess.col] != FIELD_SQUARE_UNKNOWN);
            }
        }
    }
    return SmartGuess;
}

GuessData FieldAIDecideGuess(const Field * f)
{
    GuessData gData;
    int row;
    int col;
    do {
        row = rand() % FIELD_ROWS;
        col = rand() % FIELD_COLS;
    } while (f->grid[row][col] != FIELD_SQUARE_UNKNOWN);

    gData.col = col;
    gData.row = row;
    return gData;
}
