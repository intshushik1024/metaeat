#include <stdio.h>
#include <string.h>
#include <pcre.h>

#define OVECCOUNT 30    /* should be a multiple of 3 */


char parseuri(char *uri, char *upattern)
{
pcre *re;
const char *error;
char *pattern;
char *subject;
unsigned char *name_table;
unsigned int option_bits;
int erroffset;
int find_all;
int crlf_is_newline;
int namecount;
int name_entry_size;
int ovector[OVECCOUNT];
int subject_length;
int rc, i;
int utf8;


pattern = upattern;;
subject = uri;
subject_length = (int)strlen(subject);



re = pcre_compile(
  pattern,              /* the pattern */
  0,                    /* default options */
  &error,               /* for error message */
  &erroffset,           /* for error offset */
  NULL);                /* use default character tables */

if (re == NULL)
  {
  printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
   int error = 1;
  }

rc = pcre_exec(
  re,                   /* the compiled pattern */
  NULL,                 /* no extra data - we didn't study the pattern */
  subject,              /* the subject string */
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
  error = 1;
  }

printf("\nMatch succeeded at offset %d\n", ovector[0]);



char a1[16];
char n1[16];

pcre_copy_substring (
      subject,
      ovector,
      5,
      4,
      n1,
      16
);

pcre_copy_substring (
      subject,
      ovector,
      5,
      2,
      a1,
      16

   );

char data[32];
data=a1; data[16]= n1;
return data;

}
