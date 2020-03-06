#include "intr.h"
#include "functions.h"

void hand(char *berp, FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp)
{

char *method;
    method = (char*)calloc(300, sizeof(char));
    method = FCGX_GetParam("REQUEST_METHOD", envp);
    if(method == "POST") {
        int i;
        size_t length; 
        length =  atoi(FCGX_GetParam("CONTENT_LENGTH",envp));
        char *pdata;
	pdata = (char*)calloc(10000, sizeof(char));

//        pdata = (char*)calloc(length+1, sizeof(char));
        FCGX_GetStr(pdata, length, in);
	strcpy(berp,pdata);
        }


}