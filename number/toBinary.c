#include "../number.h"

void printBinary(long long n){
	if (n==0) {
		printf("0\n");return;
	}
	char* s;
    printBinaryInMemory(&n,sizeof(long long),&s);
	printf("%s\n",strstr(s, "1"));
	free(s);
}

void printBinaryInMemory(void* num,size_t bytes,void* val){
	char *s = num;
	char* b;
	unsigned char c;
	memory* m =initMemoryWithFilledBytes('0', bytes*8+1);
	for (int i = bytes-1;i>=0;i--) {
		c = s[i];
		b = tobinary2(c);
		replaceMemoryAtOffsetWithArray(b+24, 8, (bytes-i-1)*8, m);
		free(b);
	}
	char* res;
	freeMemory(m,&res);
	res[bytes*8]='\0';
	if (val!=NULL) {
		memcpy(val, &res, sizeof(char*));
	}
	else {
		printf("%s\n",res);
		free(res);
	}	
}


char* tobinary(int n){
	if (n<2) {char* temp = (char *)malloc(sizeof(char)*2); temp[0]= (n==0)? '0':'1';temp[1]='\0';return temp;}
	char* temp = tobinary(n/2);
	int len = (int)strlen(temp);
	char* temp1 = (char *)malloc(sizeof(char)*(len+2));
	strcpy(temp1,temp);
	sprintf(temp1+len,"%d",n%2);
	temp1[len+1]='\0';
	free(temp);
	return temp1;
}


char* tobinary2(int n){
	int size = sizeof(int)*8;
	char* temp = (char *)malloc(sizeof(char)*(size+1));
	memset(temp,'0',size);
	temp[size]='\0';
	char *result = temp;
	int count=0;
	if (n<0) {n=-n;temp[size-1]='-';}
	for (int i = 0; i < n; n/=2)
	{
		sprintf(temp++,"%d",n%2);
		count++;
	}
	result[count]='0';
	temp = strrev1(result);
    free(result);
    return temp;
}

