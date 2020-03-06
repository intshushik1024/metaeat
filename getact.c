#include <stdio.h>
#include <string.h>
#include <pcre.h>
#define OVECCOUNT 30

int main() {

    char *subject;
    int subject_length;
    const char *error;
    int erroffset;
    pcre *re;
    int ovector[OVECCOUNT];
    int rc;
    char *input;
    input="action=register&id=256";
    char *pattern;
    pattern= "^(action=)(.*\?)\&(id=)(0-9)";

    subject_length=(int)strlen(input);

re = pcre_compile(
  pattern,              /* the pattern */
  0,                    /* default options */
  &error,               /* for error message */
  &erroffset,           /* for error offset */
  NULL);                /* use default character tables */


if (re == NULL)
  {
  printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
  return 1;
  }



rc = pcre_exec(
  re,                   /* the compiled pattern */
  NULL,                 /* no extra data - we didn't study the pattern */
  input,              /* the subject string */
  subject_length,       /* the length of the subject */
  0,                    /* start at offset 0 in the subject */
  0,                    /* default options */
  ovector,              /* output vector for substring information */
  OVECCOUNT);           /* number of elements in the output vector */


if (rc < 0)
  {
  switch(rc)
    {
    case PCRE_ERROR_NOMATCH: printf("No match\n"); break;
    /*
    Handle other special cases if you like
    */
    default: printf("Matching error %d\n", rc); break;
    }
  pcre_free(re);     /* Release memory used for the compiled pattern */
  return 1;
  }

/* Match succeded */

printf("\nMatch succeeded at offset %d\n", ovector[0]);

}