/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "principals.h"
#include "common.h"

int principalsRowFilter(char *row[])
{
    return (strcmp(row[3], "actor") == 0 || (strcmp (row[3], "actress")) == 0);
}

int principalMatchLineNums (char *filename)
{
    int (*p)(char *[]);
    p=principalsRowFilter;
    return matchLineNums(filename, p);
}

/*getPrincipalsBasics: fill in values of nconst/primaryname in struct*/
void getPrincipalsBasics (char *filename, PrincipalsBasic* principalsBasic, int size)
{
    int i = 0;
    FILE *fp;
    char buf[2048];
    int (*p)(char *[]);
    fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        printf("open error!\n");
        return;
    }
    else 
    {
        *principalsBasic = (PrincipalsBasic) malloc(sizeof(PrincipalsBasicNode) * size);
        
        p=principalsRowFilter;
        while (fgets(buf, sizeof(buf), fp) != NULL) 
        {
            char *revbuf[16] = {0};
            split(buf,"\t",revbuf);
            if((*p)(revbuf))
            {
                (*principalsBasic+i)->tconst = ( char* )malloc(sizeof(char)*(strlen(revbuf[0]) + 1));
                strcpy((*principalsBasic+i)->tconst,revbuf[0]);
                (*principalsBasic+i)->nconst = ( char* )malloc(sizeof(char)*(strlen(revbuf[2]) + 1));
                strcpy((*principalsBasic+i)->nconst,revbuf[2]);
                (*principalsBasic+i)->characters = ( char* )malloc(sizeof(char)*(strlen(revbuf[5]) + 1));
                strcpy((*principalsBasic+i)->characters,revbuf[5]);
                i++;
                if(i == size)
                {
                    break;
                }
            }
        }
    }
}





