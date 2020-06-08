/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "title.h"
#include "common.h"

int titleRowFilter(char *row[]){
    return strcmp(row[4], "0") == 0 && strcmp(row[1], "movie") == 0;
}

int titleMatchLineNums (char *filename){
    int (*p)(char *[]);
    p=titleRowFilter;
    return matchLineNums(filename, p);
}
void getTitleBasics (char *filename, TitleBasic* titleBasic, int size){
    int i = 0;
    FILE *fp;
    char buf[2048];
    int (*p)(char *[]);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("open error!\n");
        return;
    }
    else {
        *titleBasic = (TitleBasic) malloc(sizeof(TitleBasicNode) * size);
        
        p=titleRowFilter;
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            char *revbuf[16] = {0};
            split(buf,"\t",revbuf);
            if((*p)(revbuf)){
                (*titleBasic+i)->tconst = ( char* )malloc(sizeof(char)*(strlen(revbuf[0]) + 1));
                strcpy((*titleBasic+i)->tconst,revbuf[0]);
                (*titleBasic+i)->primaryTitle = ( char* )malloc(sizeof(char)*(strlen(revbuf[2]) + 1));
                strcpy((*titleBasic+i)->primaryTitle,revbuf[2]);
                i++;
                if(i == size){
                    break;
                }
            }
        }
    }
}


