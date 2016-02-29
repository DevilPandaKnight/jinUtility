#include "../file.h"

//write binary stream to file
bool writeToFile(void* array,size_t numberOfBytes,char* fileName,char* mode){
	cRaise(strstr(mode, "r"), "If you want to read file, then use readFromFile.");
	FILE* fp = fopen(fileName, mode);
	cRaise(fp==NULL, "cannot open the file.");
	fwrite(array, sizeof(char), numberOfBytes, fp);
	fclose(fp);
	return true;
}


//read binary stream from file
size_t readFromFile(char* fileName,char* mode,void* array){
	cRaise(strstr(mode, "w") || strstr(mode, "a"), "If you want to write file, then use writeToFile.");
	FILE* fp = fopen(fileName, mode);
	cRaise(fp==NULL, "cannot open the file.");
	char buf[BUFSIZ];
	memory *m = initMemoryWithCapacity(BUFSIZ);
	int bytes;
	while (!feof(fp)) {
		bytes = fread(buf, sizeof(char), BUFSIZ, fp);
		writeToMemory(buf, bytes, m);
	}
	fclose(fp);
	return freeMemory(m,array);
}

