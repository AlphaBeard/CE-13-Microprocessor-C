#include "BinaryTree.h"
#include "BOARD.h"
#include "stdio.h"
/**
 * @file
 *
 * This file implements an API for creating and printing a binary tree built of Nodes. Each node can
 * store a single character. There are no function for manipulating the tree as it is assumed that
 * the tree will be traversed and manipulated depending on the data contained within and no generic
 * solution would work.
 * 
 * @note This libraries relies on malloc() being available and usage, therefore a heap must be set.
 *
 * Example usage for creating a tree:
 * char treeData[7] = "abdecfg";        //< This is not a string! It's missing ending '\0'>
 * Node *root = TreeCreate(3, treeData);
 */

/**
 * A node in the binary tree. This is the only element used for representing the tree and there is no
 * object used to represent the tree as a whole. It has a left child, right child, and single char.
 * If either leftChild or rightChild are NULL, it implies that that child doesn't exist. Note that
 * this structure has no way to refer to the parent, therefore it's impossible to traverse up the
 * tree without having first traversed down it.
 */

#define LEVEL_SPACES 4

/**
 * This function creates a binary tree of a given size given a serialized array of data. All nodes
 * are allocated on the heap via `malloc()` and store the input data in their data member. Note that
 * this parameter is serialized in a top-down, left-to-right order. This means it follows the
 * left-hand-side of the tree to the bottom and then backs it's way back up.
 *
 * So for a tree like:
 *           A
 *        B     C
 *      D   E F   G
 * The data variable is ordered as [A B D E C F G].
 * 
 * This function uses recursion for generating the tree in this top-down, left-right order. This
 * tree, and therefore the input data set, is assumed to be full and balanced. Therefore, creating
 * a tree with n levels will have 2^n - 1 nodes.  If the `data` input is not this size, then this 
 * function's behavior is undefined. 
 *
 * If allocating memory fails during TreeCreate() then it will return NULL. Additionally, if the
 * creation of either of the subtrees fails within TreeCreate(), it should return NULL. This means
 * that if TreeCreate() returns a non-NULL value, that means that a perfect tree has been created,
 * so all nodes that should exist have been successfully malloc()'d onto the heap.
 *
 * This function does NOT completely clean up after itself if malloc() fails at any point. So, 
 * a malloc() failure in TreeCreate() is likely to leave memory in the heap unaccessible.
 *
 * @param level How many vertical levels the tree will have.
 * @param data A serialized array of the character data that will be stored in all nodes. This array
 *              should be of length `2^level - 1`.
// * @return A pointer to the root node of the created tree, or NULL if malloc fails for any node.
// */
Node *TreeCreate(int level, const char *data)
{
    if (level == 0) {
        return NULL;
    } else {
        //allocate current node
        Node *node = malloc(sizeof (Node));
        if (node == 0) {
            return NULL;
        }
        //current node data = first character of data string
        node->data = data[0];
        //Right child = TreeCreate(right child dataString, level-1)
        int right_child = (2 << (level - 2));
        node->rightChild = TreeCreate(level - 1, &data[right_child]);
        //Left child = TreeCreate(left child dataString, level-1)
        node->leftChild = TreeCreate(level - 1, &data[1]);
        //Return pointer to current node
        return node;
    }
}

///**
// * This function returns the left child of the node passed into the function. The function should return
// * NULL if the node passed in has no left child. You will also need to be careful not to dereference the
// * NULL pointer if called with an empty node.
// *
// * @param root Pointer to root node
// * @return The pointer to the left child of the node, NULL if there is no child.
// */

Node *GetLeftChild(Node *root)
{
    if (root->leftChild == NULL) {
        return NULL;
    } else {
        return root->leftChild;
    }
}

///**
// * This function returns the right child of the node passed into the function. The function should return
// * NULL if the node passed in has no right child. You will also need to be careful not to dereference the
// * NULL pointer if called with an empty node.
// *
// * @param root Pointer to root node
// * @return The pointer to the right child of the node, NULL if there is no child.
// */

Node *GetRightChild(Node *root)
{
    if (root->rightChild == NULL) {
        return NULL;
    } else {
        return root->rightChild;
    }
}

void printSpaces(int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf(" ");
    }
}

void TreePrint(Node *node, int space)
{
    if (node == NULL) {
        return;
    } else {
        space++;
        TreePrint(node->rightChild, space);
        printf("\n");
        printSpaces(space * LEVEL_SPACES);
        printf("%c", node->data);
        TreePrint(node->leftChild, space);
        return;
    }
}
