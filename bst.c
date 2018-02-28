#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

const char *_bst_todo_format = "TODO [bst]: %s\nhalting\n";

bst* bst_singleton(vcard* vc)
{
  fprintf(stderr,_bst_todo_format,"bst_singleton");
  exit(1);
}

int bst_insert(bst* t, vcard* vc)
{
  fprintf(stderr,_bst_todo_format,"bst_insert");
  exit(1);
}

unsigned int bst_num_entries(bst* t)
{
  fprintf(stderr,_bst_todo_format,"bst_num_entries");
  exit(1);  
}

unsigned int bst_height(bst* t)
{
  fprintf(stderr,_bst_todo_format,"bst_height");
  exit(1);
}

vcard* bst_search(bst* t, const char* cnet, int* n_comparisons)
{
  fprintf(stderr,_bst_todo_format,"bst_search");
  exit(1);
}

unsigned int bst_prefix_show(FILE* f, bst* t, const char* prefix)
{
  fprintf(stderr,_bst_todo_format,"bst_prefix_show");
  exit(1);
}

void bst_free(bst* t)
{
  fprintf(stderr,_bst_todo_format,"bst_free");
  exit(1);
}
