//>>> added by autochecker: sort.c mnlichte, Lab05, Lab05_submission_2
// Heap size 1024 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "LinkedList.h"


// **** Declare any function prototypes here ***
static int CompareStrings(char *first, char *second);
ListItem *CreateUnsortedList(void); //this function has been written for you
ListItem *SelectionSort(ListItem* list);
ListItem *InsertionSort(ListItem* list);

/* Students should not need to modify main! */
int main(void) {
    BOARD_Init();

    printf("\n\nWelcome to KAJEFFRE's sort.c, compiled on %s %s.\n", __DATE__, __TIME__);

    ListItem* listToSort;
    //    //Do a timing test 
    printf("\nStarting stopwatch for selection sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    SelectionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);


    printf("\nStarting stopwatch for insertion sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    InsertionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);
    while (1);

    return 0;
}
//Helper Function

static int isGreater(ListItem *first, ListItem *second) {
    if (first == NULL || second == NULL) {
        return 0;
    }
    int compare = strcmp(first->data, second->data);
    if (compare > 0) {
        return 1;
    } else {
        return 0;
    }
}

static int CompareStrings(char *first, char *second) {
    int compare = strcmp(first, second);
    if (compare < 0) {
        return -1; // ordered
    } else if (compare > 0) {
        return 1; // swap
    } else {
        return 0;
    }
}

/**
 * SelectionSort() performs a selection sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *SelectionSort(ListItem* list) {
    //YOUR CODE GOES HERE!
    ListItem *head = LinkedListGetFirst(list);

    // head  item
    //  2     0     5     9     8    5 
    int i;
    int size = LinkedListSize(list);
    for (i = 0; i < size - 2; i++, head = head->nextItem) {
        int j;
        ListItem *item = head->nextItem; // i + 1
        for (j = i + 1; j < size - 1; j++, item = item->nextItem) {
            if (CompareStrings(item->data, head->data) == -1) {
                LinkedListSwapData(item, head);
            }

        }
    }
}

/**
 * InsertionSort() performs an insertion sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *InsertionSort(ListItem* list) {
    //YOUR CODE GOES HERE!
    ListItem *tail = LinkedListGetLast(list);
    ListItem *head = LinkedListGetFirst(list);

    // Need a firstsorted(FS), lastunsorted(LU), InsertAfter(IA)
    ListItem *FS = tail;
    ListItem *LU;
    ListItem *IA;

    while (FS != head) {
        tail = LinkedListGetLast(list); //The tail shifts after iterations
        //        if(FS->previousItem == NULL){
        //            int i = 0;
        //            __asm("nop");
        //            break;
        //        }
        LU = FS->previousItem;
        if (CompareStrings(LU->data, FS->data) == -1) {
            FS = LU;
        } else {
            IA = FS;
            while (IA != tail && isGreater(LU, IA->nextItem)) {
                IA = IA->nextItem;
            }
            //remove LU
            char *LU_data = LinkedListRemove(LU);
            //Insert LU item after IA
            LinkedListCreateAfter(IA, LU_data);
            head = LinkedListGetFirst(list);

        }
    }

}
//
//ListItem *InsertionSort(ListItem* list) {
//    //YOUR CODE GOES HERE!
//    int i, j;
//    char *key;
//    char *word;
//
//    ListItem *itemI = list->nextItem;
//    ListItem *itemJ = list;
//
//    int size = LinkedListSize(list);
//    for (i = 1; i < size; itemI = itemI->nextItem, i++) {
//
//        if (itemI == NULL) {
//            break;
//        }
//
//        itemJ = itemI->previousItem; // array[j], j = i - 1
//        key = itemI->data; // key = array[i]
//        word = itemJ->data; // word = array[j]
//        j = i - 1;
//
//        while (j >= 0 && CompareStrings(key, word) == -1) {
//            LinkedListSwapData(itemJ, itemJ->nextItem); // array[j+1] = array[j]
//            itemJ = itemJ->previousItem; // j-- for array[j]
//            //Protect from null pointer error
//            if (itemJ != NULL) {
//                word = itemJ->data;
//            }
//            j--;
//        }
//
//    }
//
//}

/* CreateUnsortedList() uses the functions in the LinkedList library to
 * generate an unsorted list.  
 * 
 * Students should not modify this function!
 * If an error occurs in this function, there is almost certainly 
 * a bug in your implementation of LinkedList.h.
 *   
 * @return A pointer to a ListItem which is the head of a new unsorted list. 
 */
ListItem *CreateUnsortedList(void)
/// <editor-fold defaultstate="collapsed" desc="CreateUnsortedList definition">
{
    char* wordList[] = {"decide", "toothpaste", "lowly", "robin", "reign", "crowd", "pies", "reduce", "tendency", "surround", "finger", "rake", "alleged", "hug", "nest", "punishment", "eggnog", "side", "beef", "exuberant", "sort", "scream", "zip", "hair", "ragged", "damage", "thought", "jump", "frequent", "substance", "head", "step", "faithful", "sidewalk", "pig", "raspy", "juggle", "shut", "maddening", "rock", "telephone", "selective", NULL};
    //  char* wordList[] = {"D", "A", "C", "E", "B", NULL};

    int i = 0;
    ListItem* head = LinkedListNew(wordList[i]);
    ListItem* tail = head;
    for (i = 1; wordList[i] != NULL; i++) {
        tail = LinkedListCreateAfter(tail, wordList[i]);
    }
    return head;
}
// </editor-fold>
