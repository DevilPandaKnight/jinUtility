#include "../file.h"
void file_copy(char* des, char* src){
	if (des == NULL || src == NULL) {
		printf("des and src cannot be null\n");
		return;
	}
	int bytes;
	FILE *fp,*fp2;
	char buf[BUFSIZ];
	
	if ((fp=fopen(src,"rb"))==NULL) {
		printf("Failed to open %s\n",src);
		return;
	}
	
	if ((fp2=fopen(des,"wb"))==NULL) {
		printf("Failed to create %s\n",des);
		return;
	}
	
	while ((bytes=(int)fread(buf,sizeof(char),BUFSIZ,fp))>0) {
		fwrite(buf,sizeof(char),bytes,fp2);
	}
	fclose(fp2);
	fclose(fp);
}

void file_rename(char* new,char* old){
	rename(old,new);
}

void file_remove(char* name){
	fflush(stdin);
	remove(name);
}

void file_move(char* des, char *src){
    file_copy(des, src);
    file_remove(src);
}

