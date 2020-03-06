#include <time.h>
#include "intr.h"
#include "functions.h"
#include <unistd.h>
#include <wand/MagickWand.h>

//    char * method = getenv("REQUEST_METHOD");
char *gencook()
{
    srand(time(NULL));
    unsigned int cook;
    cook = rand();
    char *cookbla;
    cookbla = (char*)calloc(150, sizeof(char));
    sprintf(cookbla, "%d", cook);
    return cookbla; 
};

void reg(char *berp,FCGX_Stream *in,FCGX_Stream *out,MYSQL *mysql,FCGX_ParamArray envp)
{ 
    char *cook1;
    cook1 = (char*)calloc(150, sizeof(char));
    cook1 = gencook();
//    char *burp;
//    burp = (char*)calloc(5000, sizeof(char));
//    char *cookie;	
//    cookie = (char*)calloc(100, sizeof(char));
    int i;
/*    MD5_CTX md5handler;
    unsigned char md5digest[MD5_DIGEST_LENGTH];
        
    MD5_Init(&md5handler);
    MD5_Update(&md5handler, "cook1", strlen(cook1));
    MD5_Final(md5digest,&md5handler);
    for (i=0;i<MD5_DIGEST_LENGTH;i++) {
        sprintf(cookie,"%02x",md5digest[i]);
    };
*/	        
    int r1; 
    r1 = rand() % 10;
    int r2;
    r2 = rand() % 10;
    int res;
    res = r1 + r2;
    char *query;
    query=(char*)calloc(200, sizeof(char));
//    char *err;
//    err=(char*)calloc(250, sizeof(char));
    query = "insert into sessions (cookie,type,captcha) values ('cook1','2','res')";
    mysql_real_query(mysql,query,strlen(query));
//    rawdata(err,out);


//    tplcpy("tpl/form.tpl",burp);
 
//    free(form);


    char tmp[50];
    char *buf;
    buf = (char*)calloc(50, sizeof(char)); 
    sprintf(buf,"%d+%d=", r1, r2); 
    strcpy(tmp,buf);
    char *buf1;
    buf1 = (char*)calloc(50, sizeof(char)); 
    sprintf(buf1,"tmp/%s.gif", cook1);
    char tmp1[50];
    strcpy(tmp1,buf1);


    MagickWand *source = NULL;
    DrawingWand *drawing = NULL;
    PixelWand *pixel = NULL;


source = NewMagickWand();
drawing = NewDrawingWand();
pixel = NewPixelWand();
PixelSetColor(pixel,"#ff0000");
DrawSetFillColor(drawing,pixel);
DrawSetFont ( drawing , "Helvetica" );
DrawSetFontSize( drawing,30);
DrawSetFontWeight(drawing,100);
MagickReadImage(source, "images/white.gif");
MagickSetFormat(source, "GIF");
DrawAnnotation(drawing, 30, 30 , tmp);
MagickDrawImage(source, drawing);
MagickWriteImage(source,tmp1);

    if(source)source = DestroyMagickWand(source);
    if(drawing)drawing = DestroyDrawingWand(drawing);
    if(pixel)pixel = DestroyPixelWand(pixel);


    char *buf3;
    buf3 = (char*)calloc(2000, sizeof(char));
    sprintf(buf3,"<pСайт абсолютно анонимный. Лучше я вас запомню по вашему нику.</p><p>Только  английские буквы большие и маленькие,а так же  цифры.</p><table border=2px><form action=\"http://work.shushik.net/hand\" method=\"POST\"><tr><td>Ваш ник ник-нейм, которорый будет так же вашиим логином.</td><td><input type=\"text\" name=\"login\"></td><tr><tr><td>Ваш пароль. Записать и спарятать в сейф.</td><td><input type=\"password\" name=\"pass1\"></td>/<tr><tr><td>Повторение - мать учения. Введите еще раз для подтверждения.</td><td><input type=\"password\" name=\"pass1\"></td></tr><tr><td>email. Никакаих рассылок, никакого спама, просто на крайний случай.<br>Я лично пароль восстанавливать не буду.<br>Не хотите - оставьте пустым.</td><td><input type=\"text\" name=\"email\"></td></tr><tr><td>Простенькая супер каптча. :)<img src=\"%s\"%></td><td><input type=\"text\" name=\"answer\"></td></tr></table><br><input type=\"submit\" value=\"Поехали!\"></form>",tmp1);
    strcpy(berp,buf3);
//    rawdata(buf3,out);
    free(cook1);
    free(buf);
    free(buf1);
    free(buf3);
//    free(cookie)
//    strcty(berp, burp);
//    free(burp);
}


