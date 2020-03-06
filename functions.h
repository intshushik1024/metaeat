void reg(char *berp, FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp);
void hand(char *berp, FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp);
void rawdata(char *data, FCGX_Stream *out);
void orders(char *berp,MYSQL *mysql);
void art(FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp);
int tpl(char *filename, FCGX_Stream *out);
void postreg(char *berp, FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp);
int tplcpy (char *filename, char *fuck);
