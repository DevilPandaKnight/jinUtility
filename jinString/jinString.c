#include "../jinString.h"
char* getstring(){
	vector *v = charVector();
	char c;
	while ((c=fgetc(stdin)) != '\n' && c!= EOF) {
		pushToVector(c,v);
	}
	if (v->currentSize==0) return NULL;
	
	char* result = (char *)malloc(sizeof(char)*(v->currentSize+1));
	if (result==NULL) return NULL;
	char* temp = (char *)v->value;
#define _CRT_SECURE_NO_WARNINGS
	strncpy(result,temp,v->currentSize);
	result[v->currentSize]='\0';
    freeVector(v);
	return result;
}



char* strrev1(char* string){
    cRaise(string==NULL, "string is null.");
    size_t len = strlen(string);
    char buf[len+1];
    size_t count = len;
    for (int i = 0; i<len; i++) {
        buf[i]=string[--count];
    }
    buf[len]='\0';
    return strdup(buf);
}



char randomChar(int start){
    srand(start);
    return rand() % 26+97;
}


char* randomStringWithLength(int len){
    int t = (int)time(NULL);
    char* string = (char*)malloc(sizeof(char)*(len+1));
    memset(string, '\0', sizeof(char)*len+1);
    for (int i = 0; i<len; i++) {
        string[i] = randomChar(t+rand());
    }
    return string;
}

char* randomString(){
    int len = rand()%10+10;
    return randomStringWithLength(len);
}

void replaceChar(char* s,char oldc,char newc){
    unsigned long len = strlen(s);
    for (int i =0; i<len; i++) {
        if (s[i]==oldc) {
        s[i] = newc;
        }
    }
}

char* replaceStr(char* s,char* olds, char* news){
    if (s==NULL || olds ==NULL || news==NULL) {return NULL;}
    if (!strstr(s, olds)) {return strdup(s);}

    long oldlen = strlen(olds);
    vector *v = charVector();
    char* result;
    if (oldlen==0) {
        long strlength = strlen(s);
        for (int i =0; i<strlength; i++) {
            pushStringToVector(news, 0, v);
            pushToVector(s[i], v);
        }
        pushStringToVector(news, -1, v);
        result=strdup(v->value);
        freeVector(v);
        return result;
    }
    char* next;
    while((next = strstr(s,olds)) != NULL){
        if ((next-s) != 0){
            pushStringToVector(s,next-s,v);
        }
        pushStringToVector(news,0,v);
        s = next+oldlen;
    }
    pushStringToVector(s,-1,v);
    result = strdup(v->value);
    freeVector(v);
    return result;
}

char* stringByAppendString(char* first,char* second){
    vector* v = charVector();
    pushStringToVector(first, 0, v);
    pushStringToVector(second, -1, v);
    char* result = (char*)strdup(v->value);
    freeVector(v);
    return result;
}

static const char format[] = {'a','A','c','d','e','E','f','g','G','i','o','p','s','x','X','u','p'};
static int formatLength = sizeof(format);
static char buffer[BUFSIZ];

static bool isFormatLetter(char c){
    for (int i = 0; i<formatLength; i++) {
        if (c==format[i]) {
            return true;
        }
    }
    return false;
}

char* stringWithFormat(char* expression,...){
    va_list arg_ptr;
    size_t expLen = strlen(expression);
    va_start(arg_ptr, expression);
    
    char c;
    vector *v = charVector();
    vector *temp;
    int i = 0;
    bool afterPercent = false;
    for (; i<expLen; i++) {
        c = expression[i];
        if (c != '%' && afterPercent ==false) {
            pushToVector(c, v);
        }
        else{
            if(!afterPercent) {i++;temp = charVector();pushToVector('%', temp);}
            c = expression[i];
            if (c=='%') {
                pushToVector(expression[i], v);
                freeVector(temp);
                continue;
            }
            afterPercent = true;
            
            
            if (!isFormatLetter(c) && c!='l' && c!='L' && isalpha(c)) {
                pushToVector(c,temp);
                pushToVector('\0', temp);
                pushStringToVector(temp->value, 0, v);
                freeVector(temp);
                afterPercent = false;
                continue;
            }
            if (!isFormatLetter(c)) {
                pushToVector(c, temp);
                continue;
            }
            else{
                char ctemp = getCharValueFromIndex((int)temp->currentSize-1, temp);
                pushToVector(c,temp);
                pushToVector('\0', temp);
#define toString1(type) memset(buffer,'\0',BUFSIZ);sprintf(buffer, temp->value,va_arg(arg_ptr,long type));pushStringToVector(buffer,0,v);

#define toString2(type) memset(buffer,'\0',BUFSIZ);sprintf(buffer, temp->value,va_arg(arg_ptr, type));pushStringToVector(buffer,0,v);
                if (ctemp=='l' || ctemp == 'L') {
                    if (strstr(temp->value,"lf")!=NULL) {
                        toString2(double)
                        freeVector(temp);
                        afterPercent = false;
                        continue;
                    }
                    if (strstr(temp->value,"lld")!=NULL) {
                        toString1(long int)
                        freeVector(temp);
                        afterPercent = false;
                        continue;
                    }
                    if (c == 'a' ||  c == 'A' || c == 'e' || c == 'E' || c == 'f' || c == 'g' || c == 'G') {
                        toString1(double)
                    }
                    else if (c == 'd' || c== 'i'){
                        toString1(int)
                    }
                    else if (c == 'o' || c == 'x' || c == 'X' || c == 'u'){
                        toString1(unsigned int)
                    }
                }else{
                    if (c == 'a' ||  c == 'A' || c == 'e' || c == 'E' || c == 'f' || c == 'g' || c == 'G') {
                        toString2(double)
                    }
                    else if (c == 'd' || c== 'i'){
                        toString2(int)
                    }
                    else if (c == 'o' || c == 'x' || c == 'X' || c == 'u'){
                        toString2(unsigned int)
                    }
                }

                if (c== 'c'){
                    memset(buffer,'\0',BUFSIZ);
                    sprintf(buffer, temp->value,va_arg(arg_ptr, int));
                    pushStringToVector(buffer, 0, v);
                }
                else if (c == 'p'){
                    memset(buffer,'\0',BUFSIZ);
                    sprintf(buffer, temp->value,va_arg(arg_ptr, void*));
                    pushStringToVector(buffer, 0, v);
                }
                else if (c=='s'){
                    pushStringToVector(va_arg(arg_ptr, char*), 0, v);
                }
                freeVector(temp);
                afterPercent = false;
                continue;
            }
        }
    }
    pushToVector('\0', v);
    char* result = (char*)strdup(v->value);
    freeVector(v);
#undef toString1
#undef toString2
    va_end(arg_ptr);
    return result;
}



stack* stringSplit(char* string,char *sym){
    cRaise(!string,"NULL string.");
    cRaise(!sym,"NULL separator.");
    stack* s = stringStack();
    char* temp;
    if (*sym=='\0')
    {
        char c;
        while((c=*string++)!='\0'){
            temp = malloc(sizeof(char)*2);
            temp[0] = c;
            temp[1]='\0';
            pushStack(&temp,s);
        }
        return s;
    }
    char* next = NULL;
    int symLen = (int)strlen(sym);
    while((next=strstr(string,sym))!=NULL){
        temp = malloc(sizeof(char)*(next-string)+1);
        temp[next-string]='\0';
        strncpy(temp,string,next-string);
        string = next+symLen;
        pushStack(&temp,s);
    }
    temp = strdup(string);
    pushStack(&temp,s);
    return s;
}