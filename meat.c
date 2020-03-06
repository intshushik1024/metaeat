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

int tplcpy (char *filename, char *fuck) {
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
    
    strcpy(buffer,fuck);
 
    free(buffer);
}

void postreg(char *berp,FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp)
{
    char *method;
    method = (char*)calloc(100, sizeof(char));
    method = FCGX_GetParam("REQUEST_METHOD", envp);
     
     if (method == "POST")
        
     {
        int i;
        size_t length; 
        length =  atoi(FCGX_GetParam("CONTENT_LENGTH",envp));
        char *pdata;
        pdata = (char*)calloc(length+1, sizeof(char));
        
        FCGX_GetStr(pdata, length, in);
        
        strcpy(berp,pdata);
//      FCGI_fread(pdata,length,1,in);
        
     }

}

int pout(FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp)
{

    char *input;
    input = (char*)calloc(300, sizeof(char));
    input = FCGX_GetParam("REQUEST_URI", envp);

    if (strcmp(input, "/"))
    {
	char query[200];
        int sz = strlen(input);
	memmove(input, input + 1, sz - 1);
	input[sz - 1] = 0;
	sprintf(query,"select id from service where action='\%s'", input);
	MYSQL_ROW row;
	mysql_real_query(mysql,query,strlen(query));
	MYSQL_RES *result = mysql_store_result(mysql);
	row = mysql_fetch_row(result);
	int act;
	act = atoi(row[0]);
	mysql_free_result(result);
	return act;
    } 

/*	mysql_free_result(result);
    }
*/

}
void art(FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp)
{	
    char *berp;
    berp = (char*)calloc(10000, sizeof(char));
    char *burp;
    burp = (char*)calloc(6000, sizeof(char));



	int act = pout(in,out,mysql,envp);
        switch(act) {
	    case 1:
        	 orders(berp,mysql);
	    break;
	    case 2:
		 reg(berp,in,out,mysql,envp);
	    break;
	//    case 3:
	//	preout(pdata,in,out,mysql,envp);
	//    break;
	}


    FCGX_PutS("Content-type: text/html\r\n", out); 
    FCGX_PutS("\r\n", out);
    tpl("tpl/header.tpl",out);

    rawdata(berp,out);
    
    free(berp);
    tpl("tpl/footer.tpl",out);

}

void doit() 
{ 
    FCGX_Stream *in, *out, *err;
    FCGX_ParamArray envp;
    MYSQL *mysql = mysql_con();
    while (FCGX_Accept(&in, &out, &err, &envp) >= 0) 
    {
	art(in,out,mysql,envp);
    }
    mysql_close(mysql);
} 

int main(void) 
{
    doit();    
    return 0; 
}
