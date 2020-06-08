/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "name.h"
#include "common.h"

/*return actor/actress' names*/
int nameRowFilter(char *row[])
{
    char* ddd =(char*)(strstr(row[4], "actor") || strstr(row[4], "actress"));
    return ddd != NULL;
}

int nameMatchLineNums (char *filename)
{
    int (*p)(char *[]);
    p=nameRowFilter;
    return matchLineNums(filename, p);
}

/*getNameBasics: fill in values of nconst/primaryname in struct*/
void getNameBasics (char *filename, NameBasic* nameBasic, int size)
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
        *nameBasic = (NameBasic) malloc(sizeof(NameBasicNode) * size);
        /*get names*/
        p=nameRowFilter;
        while (fgets(buf, sizeof(buf), fp) != NULL) 
        {
            char *revbuf[16] = {0};
            split(buf,"\t",revbuf);
            if((*p)(revbuf))
            {
                (*nameBasic+i)->nconst = ( char* )malloc(sizeof(char)*(strlen(revbuf[0]) + 1));
                strcpy((*nameBasic+i)->nconst,revbuf[0]);
                (*nameBasic+i)->primaryName = ( char* )malloc(sizeof(char)*(strlen(revbuf[1]) + 1));
                strcpy((*nameBasic+i)->primaryName,revbuf[1]);
                i++;
                if(i == size)
                {
                    break;
                }
            }
        }
    }
}



