#include "LinkedList.h"
#include <stdio.h>

int main(void) {


    int error = 0;
    int passed = 0;
    int total_passed = 0;
    ListItem *head1;
    ListItem *head;
    ListItem *tail;


///////////////////////////////////////////////////////////////////////    
    //LinkedListNew(); Test
    head1 = LinkedListNew("test 1");
    tail = head1;

    //test 1
    if(strcmp(tail->data,"test 1" ) == 0){
        passed++;
    }

    head = LinkedListNew("test 2");
    tail = head;
    //test 2
    if(strcmp(tail->data, "test 2") == 0){
        passed++;
        
    }
    total_passed += passed;
    printf("Testing LinkedListNew(): passed(%i/2)\n", passed);
    passed = 0;
    

    
    
/////////////////////////////////////////////////////////////////////////////    
    
    //LinkedListCreateAfter(); Test
    tail = LinkedListCreateAfter(head, "added after test 2");

    //test 1
    if(strcmp(head->nextItem->data,"added after test 2" ) == 0){
        passed++;
    }

    ListItem *inbetween;
    inbetween = LinkedListCreateAfter(head, "put in between");
    tail = inbetween->nextItem;
    //test 2
    if(head->nextItem == inbetween){
        passed++;
        
    }
    total_passed += passed;
    printf("Testing LinkedListCreateAfter(): passed(%i/2)\n", passed);
    passed = 0;

/////////////////////////////////////////////////////////////////////////    

    
    //LinkedListRemvoe(); Test

    LinkedListRemove(inbetween);
    //test 1
    if(head->nextItem == tail){
        passed++;
    }

    LinkedListRemove(tail);
    
    //test 2
    if(head->nextItem == NULL){
        passed++;
        
    }
    total_passed += passed;
    printf("Testing LinkedListRemove(): passed(%i/2)\n", passed);
    passed = 0;

/////////////////////////////////////////////////////////////////////////    

    //LinkedListGetSize(); Test
    int size = 1;
    //test 1
    if(LinkedListSize(head) == size){
        passed++;
    }
    
    tail = LinkedListCreateAfter(head, "testee test");
    size = 2;
    
    //test 2
    if(LinkedListSize(head) == size){
        passed++;
        
    }
    total_passed += passed;
    printf("Testing LinkedListGetSize(): passed(%i/2)\n", passed);
    passed = 0;

/////////////////////////////////////////////////////////////////////////    

    //LinkedListGetFirst(); Test
    ListItem *test;
    test = LinkedListGetFirst(tail);
    //test 1
    if(test == head){
        passed++;
    }
    ListItem *test2;
    test2 = LinkedListGetFirst(test2);
    //test 2
    if(test2 == NULL){
        passed++;
        
    }
    total_passed += passed;
    printf("Testing LinkedListGetFirst(): passed(%i/2)\n", passed);
    passed = 0;

/////////////////////////////////////////////////////////////////////////    
  

    //LinkedListSwap(); Test
    error = LinkedListSwapData(head, tail);
    //test 1
    if(error == 1){
        passed++;
    }
    
    
    //test 2
    if(!strcmp(head->data,"testee test")){
        passed++;
        
    }
    total_passed += passed;
    printf("Testing LinkedListSwapData(): passed(%i/2)\n", passed);
    passed = 0;

/////////////////////////////////////////////////////////////////////////    


    //LinkedListPrint(); Test

    printf("Testing LinkedListPrint()\nExpected: \nitem 0: testee test\n"
            "item 1: test2\nOutput: \n");
    LinkedListPrint(head);

/////////////////////////////////////////////////////////////////////////    


//    LinkedListPrint(list_tail); 
    while (1);
}
