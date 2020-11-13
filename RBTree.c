// Red-Black Tree ADT implementation ... COMP9024 20T3

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "RBTree.h"

#define PRINT_COLOUR_RED   "\x1B[31m"
#define PRINT_COLOUR_RESET "\x1B[0m"

#define data(tree)   ((tree)->data)
#define left(tree)   ((tree)->left)
#define right(tree)  ((tree)->right)
#define colour(tree) ((tree)->colour)
#define isRed(tree)  ((tree) != NULL && (tree)->colour == RED)

typedef enum {RED,BLACK} Colr;

typedef struct Node {
   int  data;
   Colr colour;
   Tree left, right;
} Node;

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// make a new node containing data
Tree newNode(Item it) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   data(new) = it;
   colour(new) = RED;
   left(new) = right(new) = NULL;
   return new;
}


Tree rotateRight(Tree);
Tree rotateLeft(Tree);
Tree insertRB(Tree t,int item,bool inRight);
Tree insertRedBlack(Tree t, int item);

// insert a new item into a tree
Tree TreeInsert(Tree t, Item it) {

//   printf("Not yet implemented.\n");
//   printf("Returning a fixed tree instead:\n");
//
//   Tree testTree = newNode(2);
//   colour(testTree) = BLACK;
//   left(testTree) = newNode(1);
//   right(testTree) = newNode(3);

//   return testTree;
	t=insertRedBlack(t, it);
    return t;

}
Tree insertRB(Tree t,int item,bool inRight){
    if(t==NULL){
        t=newNode(item);
        return t;}
    else if(item == data(t)) return t;
    if(left(t)!=NULL && right(t)!=NULL){
    if(colour(left(t))==RED && colour(right(t))==RED){
        colour(t)=RED;
        colour(left(t))=BLACK;
        colour(right(t))=BLACK;}}
    if(item <data(t)){
        left(t)=insertRB(left(t), item, false);
        if(t!=NULL && left(t)!=NULL){
        if(inRight && colour(t)==RED && colour(left(t))==RED) t=rotateRight(t);}
        if(t!=NULL && right(t)!=NULL){
        if(!inRight && colour(t)==RED && colour(right(t))==RED) t=rotateLeft(t);}
        if(left(t)!=NULL && left(left(t))!=NULL){
        if(colour(left(t))==RED && colour(left(left(t)))==RED){
            t=rotateRight(t);
            colour(t)=BLACK;
            colour(right(t))=RED;
        }}
        if(right(t)!=NULL && right(right(t))!=NULL){
        if(colour(right(t))==RED && colour(right(right(t)))==RED){
            t=rotateLeft(t);
            colour(t)=BLACK;
            colour(left(t))=RED;
        }}
    }else{
        right(t)=insertRB(right(t), item, true);
        if(t!=NULL && left(t)!=NULL){
        if(inRight && colour(t)==RED && colour(left(t))==RED) t=rotateRight(t);}
        if(t!=NULL && right(t)!=NULL){
        if(!inRight && colour(t)==RED &&colour( right(t))==RED) t=rotateLeft(t);}
        if(left(t)!=NULL && left(left(t))!=NULL){
        if(colour(left(t))==RED && colour(left(left(t)))==RED){
            t=rotateRight(t);
            colour(t)=BLACK;
            colour(right(t))=RED;
        }}
        if(right(t)!=NULL && right(right(t))!=NULL){
        if(colour(right(t))==RED && colour(right(right(t)))==RED){
            t=rotateLeft(t);
            colour(t)=BLACK;
            colour(left(t))=RED;
        }}
    }
    return t;
}

Tree insertRedBlack(Tree t, int item){
    t=insertRB(t, item, false);
    colour(t)=BLACK;
    return t;
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;
   else if (it < data(t))
      return TreeSearch(left(t), it);
   else if (it > data(t))
      return TreeSearch(right(t), it);
   else                                 // it == data(t)
      return true;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      if (isRed(t))
	 printf("%s%d%s\n", PRINT_COLOUR_RED, data(t), PRINT_COLOUR_RESET);
       else
	 printf("%d\n", data(t));
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}
