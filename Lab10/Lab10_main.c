// **** Include libraries here ****
// Standard libraries
#include <math.h>
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "UNIXBOARD.h"

// User libraries
#include "Game.h"
#include "Player.h"
// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****
static const char *red = "\e[1;31m";
static const char *grn = "\e[1;32m";
static const char *end = "\e[0m";

// **** Declare any function prototypes here ****

int main() {
    char input;
    char desc[GAME_MAX_ROOM_DESC_LENGTH];
    char title[GAME_MAX_ROOM_TITLE_LENGTH];
    uint8_t exits;
    /******************************** Your custom code goes below here ********************************/
    // AddToInventory(0x3);
    GameInit();
    while (input != 'q') {
        GameGetCurrentRoomDescription(desc);
        GameGetCurrentRoomTitle(title);
        printf("\n\n\n%sTitle:%s %s\n%sDescription: %s%s\nExits: ", grn, end, title, red, end, desc);
        exits = GameGetCurrentRoomExits();
        if ((exits & GAME_ROOM_EXIT_NORTH_EXISTS) != 0) {
            printf("\tn");
        }
        if ((exits & GAME_ROOM_EXIT_EAST_EXISTS) != 0) {
            printf("\te");
        }
        if ((exits & GAME_ROOM_EXIT_SOUTH_EXISTS) != 0) {
            printf("\ts");
        }
        if ((exits & GAME_ROOM_EXIT_WEST_EXISTS) != 0) {
            printf("\tw");
        }
        printf("\n");
        printf("Enter direction to travel (n, e, s, w) or q to quit followed by enter: ");
        input = getchar();
        char throwawy = getchar();

        if (input == 'n') {
            int error = GameGoNorth();
            if (error == STANDARD_ERROR) {
                continue;
            }
        } else if (input == 'e') {
            int error = GameGoEast();
            if (error == STANDARD_ERROR) {
                continue;
            }
        } else if (input == 's') {
            int error = GameGoSouth();
            if (error == STANDARD_ERROR) {
                continue;
            }
        } else if (input == 'w') {
            int error = GameGoWest();
            if (error == STANDARD_ERROR) {
                continue;
            }
        }
    }
    // return 0;
    /**************************************************************************************************/
}
