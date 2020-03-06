#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define orders 1
// Helper macro to convert two-character hex strings to character value
#define ToHex(Y) (Y>='0'&&Y<='9'?Y-'0':Y-'A'+10)

char InputData[4096];

void getAllParams(char *tmp) {
  
  strcpy(InputData,tmp);
}

void getParam(const char *Name, char *Value) {
  char *pos1 = strstr(InputData, Name);

  if (pos1) {
    pos1 += strlen(Name);

    if (*pos1 == '=') { // Make sure there is an '=' where we expect it
      pos1++;

      while (*pos1 && *pos1 != '&') {
	if (*pos1 == '%') { // Convert it to a single ASCII character and store at our Valueination
	  *Value++ = (char)ToHex(pos1[1]) * 16 + ToHex(pos1[2]);
	  pos1 += 3;
	} else if( *pos1=='+' ) { // If it's a '+', store a space at our Valueination
	  *Value++ = ' ';
	  pos1++;
	} else {
	  *Value++ = *pos1++; // Otherwise, just store the character at our Valueination
	}
      }

      *Value++ = '\0';
      return;
    }

  }

  strcpy(Value, "undefine"); // If param not found, then use default parameter
  return;
}

 void getvar(char *uri,long action, long id) {
//  char *action;
  char id1[8];
  char action1[8];
  getAllParams(uri);
  getParam("action", id1);
  getParam("id", action1);
  action= atoi(action1);
  id = atoi(id1);;
/*
  printf("QueryString: %s", InputData);
  printf("<br>");
  printf("action: %s", action);
  printf("<br>");
  printf("id: %s", id);

*/
}
