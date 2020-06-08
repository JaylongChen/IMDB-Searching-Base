/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 */
#ifndef A3_COMMON_H
#define A3_COMMON_H

#include "name.h"
#include "title.h"
#include "principals.h"
#include "binary.h"

int matchLineNums (char *filename, int (*p)(char *[]) );
KeyType str2int(char *src);
KeyType const2int();
void split(char *src,const char *separator,char **dest);
#endif
