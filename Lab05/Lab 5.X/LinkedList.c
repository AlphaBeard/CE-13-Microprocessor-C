#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>


ListItem *LinkedListNew(char *data) {
    ListItem *new = (ListItem*) malloc(sizeof (ListItem));
    if (new == NULL) {
        return new;
    }
    new->data = data;
    new->nextItem = NULL;
    new->previousItem = NULL;
    return new;
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data) {
    ListItem *itemA = item;
    ListItem *itemC = itemA->nextItem; // The item next in the list

    //new item
    ListItem *itemB = (ListItem*) malloc(sizeof (ListItem));

    if (itemB == NULL) {
        return itemB;
    }

    //Happens whether or not there is another item in the list
    itemA->nextItem = itemB;
    itemB->previousItem = itemA;
    itemB->data = data;

    //If there is a next item in the list
    if (itemC != NULL) {
        itemC->previousItem = itemB;
        itemB->nextItem = itemC;
    } else {
        itemB->nextItem = NULL;
    }

    return itemB;

}

char *LinkedListRemove(ListItem *item) {
    //send back if null pointer
    if (item == NULL) {
        return (char*) NULL;
    }
    //Rearrange next and previous pointers
    ListItem *A = item->previousItem;
    ListItem *C = item->nextItem;

    if (A != NULL) {
        A->nextItem = C;
    }

    if (C != NULL) {
        C->previousItem = A;
    }

    //return data pointer
    char *word = item->data;
    free(item);
    return word;
}

int LinkedListSize(ListItem *list) {
    int n = 0;

    if (list == NULL) {
        return 0;
    }
    //Get to front of list
    for (; list->previousItem != NULL; list = list->previousItem);

    //Count how many entries
    for (; list != NULL; list = list->nextItem) {
        n++;
    }

    return n;
}

ListItem *LinkedListGetFirst(ListItem *list) {
    if (list == NULL) {
        return list;
    }
    //get to front of list
    for (; list->previousItem != NULL; list = list->previousItem);

    return list;
}

ListItem *LinkedListGetLast(ListItem *list) {
    if (list == NULL) {
        return list;
    }
    //Get to back of list
    for (; list->nextItem != NULL; list = list->nextItem);
    
    return list;

}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem) {
    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR;
    }
    char *tmp;
    tmp = firstItem->data;
    firstItem->data = secondItem->data;
    secondItem->data = tmp;
    return SUCCESS;

}

int LinkedListPrint(ListItem *list) {
    if (list == NULL) {
        return STANDARD_ERROR;
    }
    int i = 0;

    //Get to front of list
    for (; list->previousItem != NULL; list = list->previousItem);

    for (; list != NULL; list = list->nextItem, i++) {
        printf("Item %i: %s\n", i, list->data);
    }
    return SUCCESS;
}