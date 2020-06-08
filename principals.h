/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 */
#ifndef A3_PRINCIPALS_H
#define A3_PRINCIPALS_H

typedef struct title_principals *PrincipalsBasic;

struct title_principals {
    char *tconst;
    char *nconst;
    char *characters;
}PrincipalsBasicNode;

void getPrincipalsBasics (char *filename, PrincipalsBasic* principalsBasic, int size);
int principalMatchLineNums (char *filename);

#endif
