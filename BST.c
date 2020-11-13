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

// insert a new item into a tree
Tree insertRB(Tree RBtree,int i,bool val){
    if(RBtree==NULL)
	{
        RBtree=newNode(i);
        return RBtree;
	}
	
    else{
    	if(i==data(RBtree)) {
    		return RBtree;	
		}
	}
	 
    if(left(RBtree)!=NULL&&right(RBtree)!=NULL)
	{
//		 //printf("+++++++++++++++++++");
    	if(colour(left(RBtree))==RED&&colour(right(RBtree))==RED){
        	colour(right(RBtree))=BLACK;   //black
			colour(RBtree)=RED;				//red
        	colour(left(RBtree))=BLACK;
        	
		}
	}
	
    if(i<data(RBtree)){
        left(RBtree)=insertRB(left(RBtree),i,false);
        //情况1 
        //printf("-----------start---------------");
        if(RBtree!=NULL&&left(RBtree)!=NULL){
        	if(val&&colour(RBtree)==RED&&colour(left(RBtree))==RED)
			{
			 RBtree=rotateRight(RBtree);
			}
		}
		//情况2 
        if(RBtree!=NULL&&right(RBtree)!=NULL)
		{
        	if(!val && colour(RBtree)==RED&&colour(right(RBtree))==RED) {
        		RBtree=rotateLeft(RBtree);
			}
		}
		//情况3
        if(left(RBtree)!=NULL&&left(left(RBtree))!=NULL)
		{
	        if(colour(left(RBtree))==RED&&colour(left(left(RBtree)))==RED){
	        	//right
	            RBtree=rotateRight(RBtree);
	            colour(RBtree)=BLACK;
	            colour(right(RBtree))=RED;
        	}
		}
        //情况4 

        if(right(RBtree)!=NULL&&right(right(RBtree))!=NULL){
	        if(colour(right(RBtree))==RED && colour(right(right(RBtree)))==RED){
	        	//left
	            RBtree=rotateLeft(RBtree);
	            colour(RBtree)=BLACK;
	            colour(left(RBtree))=RED;
	        }
		}
		//printf("----------end-------");
    }
    //其他 
	else{
        right(RBtree)=insertRB(right(RBtree),i,true);
        if(RBtree!=NULL&&left(RBtree)!=NULL){
        	//printf("--------------------");
        	if(val && colour(RBtree)==RED && colour(left(RBtree))==RED) 
				{
					//right
					RBtree=rotateRight(RBtree);
				}
		}
        if(RBtree!=NULL&&right(RBtree)!=NULL)
		{
        	if(!val&&colour(RBtree)==RED&&colour(right(RBtree))==RED) 
				{
					//left
					RBtree=rotateLeft(RBtree);
				}
		}
				
        if(left(RBtree)!=NULL&&left(left(RBtree))!=NULL){
	    //printf("+++++++++++++++++++");
		    if(colour(left(RBtree))==RED&&colour(left(left(RBtree)))==RED){
	            RBtree=rotateRight(RBtree);
	            colour(RBtree)=BLACK;
	            colour(right(RBtree))=RED;
	        }
		}
		// printf("Not yet implemented.\n");
		//printf("Returning a fixed tree instead:\n");
        if(right(RBtree)!=NULL&&right(right(RBtree))!=NULL){
	        if(colour(right(RBtree))==RED && colour(right(right(RBtree)))==RED){
	            RBtree=rotateLeft(RBtree);
	            colour(RBtree)=BLACK;
	            colour(left(RBtree))=RED;
	        }
		}
    }
    return RBtree;
}


Tree insertRedBlack(Tree tree, int i){
    tree=insertRB(tree, i, false);
    //blcck
	colour(tree)=BLACK;
    return tree;
}

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
