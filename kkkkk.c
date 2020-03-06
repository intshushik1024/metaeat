#include "intr.h"
#include "mypasswd.h"
#include "functions.h"
#include <pcre.h>

#define OVECCOUNT 30    /* should be a multiple of 3 */

MYSQL *mysql_con()
{
    MYSQL *mysql;

	mysql = mysql_init(NULL);
	mysql_real_connect(mysql, MYHOST, MYUSER, MYPASS, MYDB, 0,NULL,0);
	mysql_set_character_set(mysql, "utf8");
    
    return mysql;
}

int ovector[OVECCOUNT];

char parseuri(char *uri, char *upattern, char flag )
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

int match = 0;
if (rc < 0)
  {
  switch(rc)
    {
    case PCRE_ERROR_NOMATCH: match=0; break;
    /*
    Handle other special cases if you like
    */
    default: printf("Matching error %d\n", rc); match = 0;
    } 
  } else match=1;

}

}
/*char a1[64];
char n1[64];*/

/*
pcre_copy_substring (
      subject,
      ovector,
      1,
      1,
      n1,
      64
);

pcre_copy_substring (
      subject,
      ovector,
      1,
      1,
      a1,
      64
   );

if (flag(strcmp(flag,a1)==0) return a1 else return n1; 
*/

//int getaction(FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp)
//{
//    MYSQL_ROW row;
//    char *input = FCGX_GetParam("QUERY_STRING", envp);
//    if (!strcmp(input,NULL)) {
//    action=(input,"^(\\w+*)",
//    char query[150];
//    sprintf(query,"select id from service where action='%s'", buffer );
//    strcpy(query,"select id from service where action='register'");

//    mysql_real_query(mysql,query,strlen(query));
//    MYSQL_RES *result = mysql_store_result(mysql);
//    row = mysql_fetch_row(result);
//    rawdata(input,out);
//    int act;
//    act = atoi(row[0]);
//    return act;
//    mysql_free_result(result);
//    free(buffer);
//   }

//}

void echodata(char *data, FCGX_Stream *out)
{
	        FCGX_PutS("Content-type: text/html\r\n", out); 
	        FCGX_PutS("\r\n", out); 
    		FCGX_PutS(data,out);
}

void rawdata(char *data, FCGX_Stream *out)
{
    FCGX_PutS(data,out);
}

int tpl(char *filename, FCGX_Stream *out) {
    FILE    *infile;
    char    *buffer;
    long    numbytes;
 
infile = fopen(filename, "r");
 
    if(infile == NULL)
	return 1;
 
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
 
    fseek(infile, 0L, SEEK_SET);	
 
    buffer = (char*)calloc(numbytes, sizeof(char));	
 
    if(buffer == NULL)
	return 1;
 
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    rawdata(buffer,out);
 
    free(buffer);
}


void art(FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp)
{
    FCGX_PutS("Content-type: text/html\r\n", out); 
    FCGX_PutS("\r\n", out);
    tpl("tpl/header.tpl",out);
    char query[150];

    char *input = FCGX_GetParam("REQUEST_URI", envp);
    rawdata(input,out);   
    
    MYSQL_ROW row;
    if (!strcmp(input,NULL)) {
    sprintf(query,"select id from service where action='%s'", input);

    mysql_real_query(mysql,query,strlen(query));
    MYSQL_RES *result = mysql_store_result(mysql);
    row = mysql_fetch_row(result);
    char *input = FCGX_GetParam(row[0], envp);
    int act;
    act = atoi(row[0]);
//    parseurl(input,a,n);
//    act = getaction(out,mysql,envp);
//    act = 2;
    switch(act) {
	case 1:
    	    orders(out,mysql);
	break;
	case 2:
	    rawdata("Да, щас буду писать",out);
	break;
    }
  
    tpl("tpl/footer.tpl",out);
}

void doit() 
{ 
    FCGX_Stream *in, *out, *err;
    FCGX_ParamArray envp;
    MYSQL *mysql = mysql_con();
    while (FCGX_Accept(&in, &out, &err, &envp) >= 0) 
    {
	
	art(out,mysql,envp);
    }
    mysql_close(mysql);
} 

int main(void) 
{
    doit();    
    return 0; 
}
