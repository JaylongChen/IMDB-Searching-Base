/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 */
#ifndef A3_TITLE_H
#define A3_TITLE_H

typedef struct title_basics *TitleBasic;
struct title_basics {
    char *tconst;
    char *primaryTitle;
}TitleBasicNode;

void getTitleBasics (char *filename, TitleBasic* principalsBasic, int size);
int titleMatchLineNums (char *filename);

#endif
