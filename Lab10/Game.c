#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Player.h"
//Defines
// #define DEBUG_MODE //Uncomment for debug mode
#define RPG_LENGTH 3
#define length_LENGTH 1
#define EXITS 4
#define MAX_ITEMS 4
//Custom Variable Types
typedef struct
{
    char room_title[GAME_MAX_ROOM_TITLE_LENGTH];
    int title_length;
    int desc_length;
    char room_description[GAME_MAX_ROOM_DESC_LENGTH];
    uint8_t items_required;
    uint8_t item_requirements[INVENTORY_SIZE];
    uint8_t num_of_items_contained;
    uint8_t items_contained[INVENTORY_SIZE];
    uint8_t exits[EXITS];
    //  0 1 2 3
    // (n e s w)
} Room;

//Module Level Variables
static Room CurrentRoom;
static FILE *file_path;

//Helper Functions
void NextRoomVersion(int version);
void SkipSection(void);
int ItemRequirementMet(void);
void OpenRoomFile(const char *file);
void RoomGetTitle(void);
void RoomGetDescription(void);
void RoomGetItemContents(void);
void ClearRoomItemRequirements(void);
void RoomGetExits(void);
void RoomGetItems(void);


int GameGoNorth(void) {
    //Check if valid direction
    if (CurrentRoom.exits[0] == 0) {
        return STANDARD_ERROR;
    }
    //OPEN FILE
    char file_name[35];
    sprintf(file_name, "RoomFiles/room%d.txt", CurrentRoom.exits[0]);
    OpenRoomFile(file_name);

    //GET TITLE
    RoomGetTitle();

    //GET DESCRIPTION
    RoomGetDescription();

    //GET ITEMS CONTENTS
    RoomGetItemContents();
    RoomGetItems();

    //GET EXITS
    RoomGetExits();

    fclose(file_path);
    return SUCCESS;
}

int GameGoSouth(void) {
    //Check if valid direction
    if (CurrentRoom.exits[2] == 0) {
        return STANDARD_ERROR;
    }
    //OPEN FILE
    char file_name[35];
    sprintf(file_name, "RoomFiles/room%d.txt", CurrentRoom.exits[2]);
    OpenRoomFile(file_name);

    //GET TITLE
    RoomGetTitle();

    //GET DESCRIPTION
    RoomGetDescription();

    //GET ITEMS CONTENTS
    RoomGetItemContents();
    RoomGetItems();

    //GET EXITS
    RoomGetExits();

    fclose(file_path);
    return SUCCESS;
}

int GameGoEast(void) {
    //Check if valid direction
    if (CurrentRoom.exits[1] == 0) {
        return STANDARD_ERROR;
    }
    //OPEN FILE
    char file_name[35];
    sprintf(file_name, "RoomFiles/room%d.txt", CurrentRoom.exits[1]);
    OpenRoomFile(file_name);

    //GET TITLE
    RoomGetTitle();

    //GET DESCRIPTION
    RoomGetDescription();

    //GET ITEMS CONTENTS
    RoomGetItemContents();
    RoomGetItems();

    //GET EXITS
    RoomGetExits();

    fclose(file_path);
    return SUCCESS;
}

int GameGoWest(void) {
    //Check if valid direction
    if (CurrentRoom.exits[3] == 0) {
        return STANDARD_ERROR;
    }
    //OPEN FILE
    char file_name[35];
    sprintf(file_name, "RoomFiles/room%d.txt", CurrentRoom.exits[3]);
    OpenRoomFile(file_name);

    //GET TITLE
    RoomGetTitle();

    //GET DESCRIPTION
    RoomGetDescription();

    //GET ITEMS CONTENTS
    RoomGetItemContents();
    RoomGetItems();

    //GET EXITS
    RoomGetExits();

    fclose(file_path);
    return SUCCESS;
}
/**
 * This function sets up anything that needs to happen at the start of the game. This is just
 * setting the current room to STARTING_ROOM and loading it. It should return SUCCESS if it succeeds
 * and STANDARD_ERROR if it doesn't.
 * @return SUCCESS or STANDARD_ERROR
 */
int GameInit(void) {
    //OPEN FILE
    char file_name[35];
    sprintf(file_name, "RoomFiles/room%d.txt", STARTING_ROOM);
    OpenRoomFile(file_name);

    //GET TITLE
    RoomGetTitle();

    //GET DESCRIPTION
    RoomGetDescription();

    //GET ITEMS CONTENTS
    RoomGetItemContents();
    RoomGetItems();

    //GET EXITS
    RoomGetExits();

    fclose(file_path);
    return SUCCESS;
}

int GameGetCurrentRoomTitle(char *title) {
    strcpy(title, CurrentRoom.room_title);
    return CurrentRoom.title_length;
}

int GameGetCurrentRoomDescription(char *desc) {
    strcpy(desc, CurrentRoom.room_description);
    return CurrentRoom.desc_length;
}
uint8_t GameGetCurrentRoomExits(void) {
    uint8_t Exits = 0;
    int i;
    for (i = 0; i < EXITS; i++) {
        Exits = Exits << 1;
        if (CurrentRoom.exits[i] != 0) {
            Exits |= 1;
        }
    }
    return Exits;
}
void RoomGetItems(void) {
    int i;
    if (CurrentRoom.num_of_items_contained == 0) {
        return;
    }
    for (i = 0; CurrentRoom.items_contained[i] != 0; i++) {
        int in_inventory = FindInInventory(CurrentRoom.items_contained[i]);
        if (in_inventory == STANDARD_ERROR) {
            AddToInventory(CurrentRoom.items_contained[i]);
        }
    }
}

void OpenRoomFile(const char *file) {
    file_path = fopen(file, "rb");
    if (file_path == NULL) {
        printf("ERROR OPENING FILE\n");
        FATAL_ERROR();
    }
}
void RoomGetTitle(void) {
    fseek(file_path, 3, SEEK_SET);            //Move past RPG
    int title_length = fgetc(file_path) + 1;  //grab title length
    char *ptr = fgets(CurrentRoom.room_title, title_length, file_path);
    CurrentRoom.room_title[title_length] = 0;  //add null char
    if (ptr == NULL) {
        printf("ERROR READING TITLE\n");
        FATAL_ERROR();
    }
    CurrentRoom.title_length = title_length;
}
void ClearRoomItemRequirements(void) {
    int i;
    for (i = 0; i < 4; i++) {
        CurrentRoom.item_requirements[i] = 0;
    }
}
void RoomFillItemRequirements() {
    int i;
    CurrentRoom.items_required = fgetc(file_path);
    ClearRoomItemRequirements();
    for (i = 0; i < CurrentRoom.items_required; i++) {
        CurrentRoom.item_requirements[i] = fgetc(file_path);  //store item in byte
    }
}
void RoomGetItemContents(void) {
    unsigned char length = fgetc(file_path);
    CurrentRoom.num_of_items_contained = length;
    int i;
    for (i = 0; i < MAX_ITEMS; i++) {  //Clear items contained
        CurrentRoom.items_contained[i] = 0;
    }
    for (i = 0; i < length; i++) {  //Get all items contained
        CurrentRoom.items_contained[i] = fgetc(file_path);
    }
}
void RoomGetDescription(void) {
    int i = 0;
    do {
        NextRoomVersion(i);
        RoomFillItemRequirements();
        i++;
    } while (ItemRequirementMet() == FALSE);
    CurrentRoom.desc_length = fgetc(file_path) + 1;  //grab title length
    char *ptr = fgets(CurrentRoom.room_description, CurrentRoom.desc_length, file_path);
    CurrentRoom.room_description[CurrentRoom.desc_length] = 0;
    if (ptr == NULL) {
        printf("ERROR FILLING ROOM DESCRIPTION\n");
        FATAL_ERROR();
    }
}
void RoomGetExits(void) {
    int i;
    for (i = 0; i < EXITS; i++) {
        CurrentRoom.exits[i] = fgetc(file_path);
    }
}
int ItemRequirementMet(void) {
    int i;
    if (CurrentRoom.items_required == 0) {
        return TRUE;
    }
    for (i = 0; CurrentRoom.item_requirements[i] != 0; i++) {
        int success = FindInInventory(CurrentRoom.item_requirements[i]);
        if (success == STANDARD_ERROR) {
            return FALSE;
        }
    }
    return TRUE;
}

void SkipSection(void) {
    unsigned char length;
    length = fgetc(file_path);
    fseek(file_path, length, SEEK_CUR);
}
void NextRoomVersion(int offset) {
    fseek(file_path, RPG_LENGTH, SEEK_SET);
    SkipSection();  // Skip title
    int i;
    for (i = 0; i < offset; i++) {
        SkipSection();                  // Skip items
        SkipSection();                  // Skip Description
        SkipSection();                  //Skip items Contained
        fseek(file_path, 4, SEEK_CUR);  //Skip Exits
    }
}
void PrintRoom(void) {
    printf("Title: %s    Title Length: %d\nDescription: %s     Desc. Length: %d\n", CurrentRoom.room_title, CurrentRoom.title_length, CurrentRoom.room_description, CurrentRoom.desc_length);
}
void PrintContents(void) {
    printf("ItemRequirements: %i (", CurrentRoom.items_required);
    int i;
    for (i = 0; i < CurrentRoom.items_required; i++) {
        printf("%x ", CurrentRoom.item_requirements[i]);
    }
    printf(")\n");
    printf("Items Contained: ");
    for (i = 0; i < CurrentRoom.num_of_items_contained; i++) {
        printf("0x%x ", CurrentRoom.items_contained[i]);
    }
    printf("\n");
}