#include "Player.h"


// //Module Level Variables
static uint8_t inventory_items[INVENTORY_SIZE];
static uint8_t num_of_items = 0;

//Helper Functions
int InventoryFull(int index);


int AddToInventory(uint8_t item)
{
    int i; // Move Index to empty space
    for (i = 0; i < INVENTORY_SIZE; i++)
    {
        if (inventory_items[i] == 0)
        {
            break;
        }
    }

    if (InventoryFull(i))
    {
        return STANDARD_ERROR;
    }

    inventory_items[i] = item;
    num_of_items++;
    return SUCCESS;
}

int FindInInventory(uint8_t item)
{
    int i;
    for (i = 0; i < INVENTORY_SIZE; i++)
    {
        if (inventory_items[i] == item)
        {
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}

int InventoryFull(int index)
{
    int inventory_max_index = INVENTORY_SIZE - 1;
    //If something at last index, inventory must be full
    if (index == inventory_max_index && inventory_items[inventory_max_index] != 0)
    {
        return TRUE;
    }
    return FALSE;
}
