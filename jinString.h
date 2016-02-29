#ifndef __JINSTRING_H__
#define __JINSTRING_H__
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "container.h"
#include "utility.h"



char* getstring();
char* strrev1(char* string);
char randomChar(int start);
char* randomString();
char* randomStringWithLength(int len);
char* replaceStr(char* s,char* olds, char* news);
void replaceChar(char* s,char oldc,char newc);
char* stringByAppendString(char* first,char* second);
char* stringWithFormat(char* expression,...);
stack* stringSplit(char* string,char *sym);


#ifdef __cplusplus
};
#endif

#endif