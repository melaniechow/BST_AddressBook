#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

const char *_bst_todo_format = "TODO [bst]: %s\nhalting\n";

bst* bst_singleton(vcard* vc)
{
    bst* bst_single=malloc(sizeof (bst));
    bst_single->vc=vc;
    bst_single->lsub=NULL;
    bst_single->rsub=NULL;
    return bst_single;
}

int bst_insert(bst* t, vcard* vc)
{
    char* cnet_toadd = vc->cnet;
    char* cnet_inBST = t->vc->cnet;
    int cmp= strcmp (cnet_toadd,cnet_inBST);
    //if tree empty, exit and return error
    if (t==NULL){
        fprintf(stderr,_bst_todo_format,"bst_insert - EMPTY TREE");
        exit(1);
    }

    //if vcard to add is LESS-->go into left branch
    if (cmp < 0){
        if (t->lsub == NULL){
            t->lsub=bst_singleton(vc);
            return 1;
        }
        return bst_insert(t->lsub, vc);
    }
    //if vcard to add is GREATER-->go to right branch
    if (cmp > 0){
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
    int cmp=strcmp (cnet,bst_cnet);
    //if cnet is less than bst's --> LSUB
    if (cmp < 0){
        counter++;
        *n_comparisons=counter;
        return bst_search_HELP(t->lsub,cnet,n_comparisons,counter);
    }
    //if cnet is greater than bst's --> RSUB
    if (cmp > 0){
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

unsigned int bst_prefix_show(FILE* f, bst* t, const char* prefix)
{
    return bst_prefix_helper(f,t,prefix,strlen(prefix));
}

unsigned int bst_prefix_helper(FILE *f, bst* t, const char* prefix, int len)
{
    if (t==NULL){
        return 0;
    }
    char* bst_cnet=t->vc->cnet;
    int cmp = strncmp(prefix,bst_cnet,len);
    //if it has the prefix, print and continue down both tree
    if (cmp == 0){
        unsigned int ret=1+bst_prefix_helper(f,t->lsub,prefix,len);
        fprintf(f,"%s\n",bst_cnet);
        ret+=bst_prefix_helper(f,t->rsub,prefix,len);
        return ret;
    }
    //if prefix is smaller than cnet, check t->lsub
    if (cmp < 0){
        return bst_prefix_helper(f,t->lsub,prefix,len);
    }
    //if prefix is greater than cnet,check t->rsub
    else{
        return bst_prefix_helper(f,t->rsub,prefix,len);
    }
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
