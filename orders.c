#include "intr.h"
#include "functions.h"
void orders(char *berp, MYSQL *mysql) 
{
    MYSQL_ROW row;	
    char *buffer;
    buffer = (char*)calloc(10000, sizeof(char));
    
    char *res;
    res = (char*)calloc(10000, sizeof(char));

    char query1[200] = "select orders.id,orders.note, users.login,users.id from orders left join users on orders.owner=users.id";
    mysql_real_query(mysql,query1,strlen(query1));
    MYSQL_RES *result = mysql_store_result(mysql);
    
    strcpy(res,"<ul>");
//    rawdata("<ul>",out);
    int i;
    int totalrows = mysql_num_rows(result);
    for( i = 0; i< totalrows; i++)
    { 
      row = mysql_fetch_row(result);
      buffer = (char*)calloc(10000, sizeof(char));
      sprintf(buffer,"<p><li><a href=\"?action=orderlook&id=%d\">%s</a>, написал(а) <a href=\"?action=userinfo&id=%d\">%s</a></li/p>", row[0],row[1],row[3],row[2]);
      strcat(res,buffer);
//      rawdata(ref,out);
      free(buffer);
    }
      
    strcat(res,"</ul>");
   mysql_free_result(result);
   strcpy(berp,res);
   free(res);
}
