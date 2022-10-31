#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suffix_tree.h"

//Defining a type of struct for the nodes of the Suffix Tree
typedef struct suffixnode{
    //index for leafs identification
    int index;
    //start of the suffix label on node
    int start;
    //end of the suffix label on node
    int *end;
    //father node of the actual node, if father == NULL then the node is the root
    struct suffixnode *father;
    //child node of the actual node, if children == NULL then the node is a leaf
    //REMINDER: wich internal node will have at least 2 children nodes
    struct suffixnode *children;
    //link thats connect the internal nodes of the suffix tree to other internal nodes and the root
    struct suffixnode *link;
}node;

//node functions
int index(node *n);
int start(node *n);
int *end(int i);
node *father(node *n);
node *children(node *n);
node *link(node *n);
//function to create a new node
node *createnode(node *n, int start, int *end, int index);

int isRoot();

node *existingedge(node *n, int actualposition);

void construtingtree(node *root, int start, int end);

int main(int argc, char*argv[]){
    char *string;
    char *comparedstring;
    return 0;
}

node *createnode(node *n, int start, int *end, int index){
    node *n = malloc(sizeof(node));
    n->start = start;
    n->end = end;
    n->father = n->children = n->link = NULL;
}

void construtingtree(node *root, int start, int end){
    node *actualnode;
    int activelength;
    int remaningnodes;
}