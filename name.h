/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 */
#ifndef A3_NAME_H
#define A3_NAME_H

typedef struct name_basics *NameBasic;
struct name_basics{
    char *nconst;
    char *primaryName;
}NameBasicNode;

void getNameBasics (char *filename, NameBasic* nameBasic, int size);
int nameMatchLineNums (char *filename);
#endif
