// Heap size 2048 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "BinaryTree.h"

// **** Set any macros or preprocessor directives here ****


// **** Define any module-level, global, or external variables here ****


// **** Declare any function prototypes here ****


int main()
{
    BOARD_Init();

	printf("\nWelcome to KAJEFFRE's Binary Tree test harness, compiled on %s %s\n",__DATE__,__TIME__);

	//this is a simple test binary tree, included so you can write the relatively simple TreePrint() before implementing CreateTree().  In general, you should NOT create your binary trees this way.
	//level 1 (leaf) nodes
//	Node nodeD = {NULL, NULL, 'C'};
//	Node nodeE = {NULL, NULL, 'E'};
//	Node nodeF = {NULL, NULL, 'F'};
//	Node nodeG = {NULL, NULL, 'G'};
//	//level 2 nodes:
//	Node nodeB = {&nodeD, &nodeE, 'B'};
//	Node nodeC = {&nodeF, &nodeG, 'C'};
//	//level 3 node:
//	Node nodeA = {&nodeB, &nodeC, 'A'};
//	Node * root = &nodeA;
	
	//now, you can call TreePrint():
//	TreePrint(root, 0);
	
	//Now write TreeCreate() and try it again!
        char *TreeData = "abdecfg";
	Node *root = TreeCreate(3,TreeData);
        TreePrint(root, 0);
	
    while (1);
}

