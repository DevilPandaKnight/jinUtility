#include "../number.h"
double IEEE754ToFloat(char* binary,int precision){
	int e,mb;
	char* shifte;
	if (precision==32) {
		e=8;
		mb = 23;
		shifte = "127";
	}
	else if(precision == 64){
		e = 11;
		mb = 52;
		shifte = "1023";
	}
	else {
		printf("only 32 bits precision or 64 bits precision are allowed.\n");
		return 0;
	}
	cRaise(binary==NULL, "input is NULL.");
	char buf[precision+1];
	memset(buf, '0', precision);
	long len = strlen(binary);
	if (len > precision) {
		len = precision;
	}
	memcpy(buf, binary, len);
	buf[precision] = '\0';
	char s[] = "(-1)^x";
	s[5] = buf[0];
	char ex[e+1];
	memcpy(ex, buf+1, e);
	ex[e] = '\0';
	char m[mb];
	memcpy(m, buf+e+1, mb);
	m[mb] = '\0';
	char* reversm = strrev1(m);
	double rm = binarySummation("m*2^-i", reversm, 1,mb)+1;
	free(reversm);
	double exm = binarySummation("m*2^i", ex, 0, e);
	char str[1024];
	sprintf(str,"%s*2^(%f-%s)*%.16f",s,exm,shifte,rm);
	double result = evaluate(str);
	return result;
}






static char hex[] = {'A','a','B','b','C','c','D','d','E','e','F','f'};

static bool inhex(char c){
	for (int i = 0,len = sizeof(hex);i<len;i++) {
		if (hex[i]==c) {
			return true;
		}
	}
	return false;
}

unsigned long htd(char* str){
	size_t len = strlen(str);
	unsigned long result = 0;
	size_t count = len-1;
	int num;
	char c;
	for (int i = 0;i<len;i++) {
		c = str[count];
		if (isalpha(c) && inhex(c)) {
			c = tolower(c);
			num = c - 87;
		}
		else if(isdigit(c)){
			num = c-48;
		}
		else {
			cRaise(true, "input is not a hex number.");
			return 0;
		}
		result += num*(unsigned long)pow(16, i);
		count--;
	}
	return result;
}






char* htb(char* hex){
	cRaise(hex==NULL,"NULL input.");
	size_t len = strlen(hex);
	char c;
	char* temp = NULL;
	vector *v = charVector();
	for (int i = 0; i < len; ++i)
	{
		c = hex[i];
		if (isalpha(c) && inhex(c))
		{	
			c=tolower(c);
			temp = tobinary2(c-87);
			pushStringToVector(temp+28,0,v);
			free(temp);
		}
		else if(isdigit(c)){
			temp = tobinary2(c-48);
			pushStringToVector(temp+28,0,v);
			free(temp);
		}
		else{
			printf("this is not a hex number.\n");
			freeVector(v);
			return 0;
		}
	}
	pushToVector('\0',v);
	int i =0;
	len = v->currentSize-1;
	for (; i <len ; ++i)
	{
		if (((char*)v->value)[i]=='1')
		{
			break;
		}
	}
	if (i==len){i--;}
	temp = strdup((char*)(v->value)+i);
	freeVector(v);
	return temp;
}
