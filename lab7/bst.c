#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

/*
typedef struct {
  char* cnet;
  char* email;
  char* fname;
  char* lname;
  char* tel;
} vcard;

typedef struct bst bst;
struct bst {
  vcard* vc;
  bst* lsub;
  bst* rsub;
};

*/

const char *_bst_todo_format = "TODO [bst]: %s\nhalting\n";

/* Create a bst consisting of one leaf node. */
/* Do not copy the vcard, just point to it. */
/* (This is a shallow-copy constructor.) */
bst* bst_singleton(vcard* vc)
{
    bst* bst_single=malloc(sizeof (bst));
    bst_single->vc=vc;
    bst_single->lsub=NULL;
    bst_single->rsub=NULL;
    return bst_single;
}


/* Insert a vcard into a non-empty BST. */
/* Raise an error if given an empty BST. */
/* Use cnet alphabetical order (per strcmp). */
/* If the cnet is already present in the tree, insert nothing. */
/* Do not copy the vcard (this is shallow-copy insert). */
/* Return the number of vcards inserted (either 1 or 0). */

int bst_insert(bst* t, vcard* vc)
{
    char* cnet_toadd = vc->cnet;
    char* cnet_inBST = t->vc->cnet;

    //if tree empty, exit and return error
    if (t==NULL){
        fprintf(stderr,_bst_todo_format,"bst_insert - EMPTY TREE");
        exit(1);
    }

    //if vcard to add is LESS-->go into left branch
    if (strcmp (cnet_toadd,cnet_inBST) < 0){
        if (t->lsub == NULL){
            t->lsub=bst_singleton(vc);
            return 1;
        }
        return bst_insert(t->lsub, vc);
    }
    //if vcard to add is GREATER-->go to right branch
    if (strcmp(cnet_toadd,cnet_inBST) > 0){
        if (t->rsub == NULL){
            t->rsub=bst_singleton(vc);
            return 1;
        }
        return bst_insert(t->rsub, vc);
    }
    //if vcard is equal, do nothing because already added
    else{
        return 0;
    }
}


/* Compute the total number of vcards in the tree. */
unsigned int bst_num_entries(bst* t)
{
    //if empty tree
    if (t==NULL){
        return 0;
    }
    //if leaf node, add 1
    if (t->lsub == NULL && t->rsub == NULL){
        return 1;
    }
    //if only lsub empty, keep going down rsub
    if (t->lsub == NULL){
        return 1+bst_num_entries(t->rsub);
    }
    //if only rsub empty, keep going down lsub
    if (t->rsub == NULL){
        return 1+bst_num_entries(t->lsub);
    }
    //else (both lsub and rsub have elements) go down both subtrees
    return 1+bst_num_entries(t->lsub)+bst_num_entries(t->rsub);
}

/* The empty bst has height 0. */
/* A singleton tree has height 1, etc. */
unsigned int bst_height(bst* t)
{
    //if empty tree
    if (t==NULL){
        return 0;
    }
    //if leaf node
    if (t->lsub == NULL && t->rsub == NULL){
            return 1;
    }
    //if only left node empty, go down right
    if (t->lsub == NULL){
        return 1+bst_height(t->rsub);
    }
    //if only right node empty, go down left
    if (t->rsub == NULL){
        return 1+bst_height(t->lsub);
    }
    //if both subtrees present:
    //if left branch longer, go down left branch
    if ((bst_height(t->lsub)) > (bst_height(t->rsub))){
        return 1+bst_height(t->lsub);
    }
    //if right branch longer or equal, go down right
    else {
        return 1+bst_height(t->rsub);
    }
}

/* Return NULL is nothing is found. */
/* n_comparisons is an out parameter to count the number of */
/* comparisons made during the search. */
/* The program must not assume that *n_comparisons is 0. */
vcard* bst_search(bst* t, const char* cnet, int* n_comparisons)
{
    return bst_search_HELP(t,cnet,n_comparisons,0);
}

vcard* bst_search_HELP(bst* t, const char* cnet, int* n_comparisons, int counter)
{
    if (t==NULL){
        return NULL;
    }
    char* bst_cnet=t->vc->cnet;
    //if cnet is less than bst's --> LSUB
    if (strcmp (cnet,bst_cnet) < 0){
        counter++;
        *n_comparisons=counter;
        return bst_search_HELP(t->lsub,cnet,n_comparisons,counter);
    }
    //if cnet is greater than bst's --> RSUB
    if (strcmp(cnet,bst_cnet) > 0){
        counter++;
        *n_comparisons=counter;
        return bst_search_HELP(t->rsub, cnet,n_comparisons,counter);
    }
    //if equal
    else{
        counter++;
        *n_comparisons=counter;
        return t->vc;
    }
}

//helper function for bst_prefix_show - stores length of prefix & # of prefixes printed
unsigned int bst_prefix_helper(FILE* f, bst* t, const char * prefix,
                                int len, unsigned int num_prefixes)
{
    //empty tree
    if (t==NULL){
        return num_prefixes;
    }
    char* bst_cnet=t->vc->cnet;
    int x = strncmp(prefix,bst_cnet,len);
    //if it has the prefix, print and continue down both trees
    if (x == 0){
        fprintf(f,"%s\n",bst_cnet);
        num_prefixes++;
        if (t->lsub==NULL && t->rsub == NULL){
                return num_prefixes;
        }
        return bst_prefix_helper(f,t->lsub,prefix,len,num_prefixes);
        return bst_prefix_helper(f,t->rsub,prefix,len,num_prefixes);
    }
    //if prefix is smaller than cnet, check t->lsub
    if (x < 0){
        if (t->lsub == NULL){
            return num_prefixes;
        }
        return bst_prefix_helper(f,t->lsub,prefix,len,num_prefixes);
    }
    //if prefix is greater than cnet,check t->rsub
    else{
        if (t->rsub == NULL){
            return num_prefixes;
        }
        return bst_prefix_helper(f,t->rsub,prefix,len,num_prefixes);
    }
}


unsigned int bst_prefix_show(FILE* f, bst* t, const char* prefix)
{
    return bst_prefix_helper(f,t,prefix,strlen(prefix),0);
}


/* Free the bst and all vcards as well. */
void bst_free(bst* t)
{
    if (t==NULL){
        free(t);
    }
    else {
        vcard_free(t->vc);
        bst_free(t->lsub);
        bst_free(t->rsub);
	free(t);
    }
}
