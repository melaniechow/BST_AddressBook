#include <stdlib.h>
#include <stdio.h>
#include "adrbook.h"

const char *_vcard_todo_format = "TODO [vcard]: %s\nhalting\n";

/* vcard_new : allocate a new vcard, copy all strings, return new object
 * note: this is a "deep copy" as opposed to a "shallow copy"; the string
 *   arguments are not to be shared by the newly allocated vcard
 */

vcard* vcard_new(const char* cnet, const char* email,
                 const char* fname, const char* lname, const char* tel)
{
        vcard* vcard=malloc(sizeof(vcard));
        vcard->cnet=strdup(cnet);
        vcard->email=strdup(email);
        vcard->fname=strdup(fname);
        vcard->lname=strdup(lname);
        vcard->tel=strdup(tel);
}

/* vcard_free : free vcard and the strings it points to
 */
void vcard_free(vcard* vc)
{
    free(vc->cnet);
    free(vc->email);
    free(vc->fname);
    free(vc->lname);
    free(vc->tel);
    free(vc);
}

void vcard_show(FILE* f, vcard* vc)
{
    fprintf(f, "CNET ID: %s\n",vc->cnet);
    fprintf(f, "EMAIL: %s\n",vc->email);
    fprintf(f, "FIRST NAME: %s\n",vc->fname);
    fprintf(f, "LAST NAME: %s\n",vc->lname);
    fprintf(f, "TELEPHONE: %s\n",vc->tel);
}
