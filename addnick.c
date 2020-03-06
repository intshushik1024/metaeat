char *method;
    method = (char*)calloc(300, sizeof(char));
    method = FCGX_GetParam("REQUEST_METHOD", envp);
    if(method == "POST") {
//     rawdata(method,out);
        int i;
        size_t length; 
        length =  atoi(FCGX_GetParam("CONTENT_LENGTH",envp));
        char *pdata;
        pdata = (char*)calloc(length+1, sizeof(char));
        
        FCGX_GetStr(pdata, length, in);
//      rawdata(pdata,out);
        }
