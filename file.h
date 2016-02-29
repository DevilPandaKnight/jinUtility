#ifndef __FILE_H__
#define __FILE_H__
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "container.h"


/*************************************************************/
void file_copy(char* des, char* src);
void file_rename(char* new_name,char* old_name);
void file_remove(char* name);
void file_move(char* des, char *src);
/*************************************************************/



/*************************************************************/
bool writeToFile(void* array,size_t numberOfBytes,char* fileName,char* mode);

//pass in the arddress of the array pointer to get data. return bytes read.
size_t readFromFile(char* fileName,char* mode,void* array);
/*************************************************************/

#ifdef __cplusplus
};
#endif

#endif