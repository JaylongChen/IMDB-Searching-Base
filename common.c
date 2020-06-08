#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "binary.h"
#include "common.h"
#include "name.h"
#include "title.h"

/*split: split a word*/
void split(char *src,const char *separator,char **dest) 
{
    char *pNext;
    if (src == NULL || strlen(src) == 0)
    {
        return;
	}
	
    if (separator == NULL || strlen(separator) == 0)
    {
        return;
	}
    pNext = (char *)strtok(src,separator);
    while(pNext != NULL) 
    {
        *dest++ = pNext;
        pNext = (char *)strtok(NULL,separator);
    }
}

/*matchLineNums: */
int matchLineNums ( char *filename, int (*p)(char *[]) )
{
    FILE *fp;
    char buf[2048];
    int count = 0;
    fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        printf("open error!\n");
        return 0;
    }
    else 
    {
        while (fgets(buf, sizeof(buf), fp) != NULL) 
        {
            char *revbuf[16] = {0};
            split(buf,"\t",revbuf);
            if((*p)(revbuf))
            {
				count ++;
            }
        }
        fclose(fp);
        return count;
    }
}

KeyType str2int(char *src)
{
    char *p;
    KeyType h = 0;
    for(p=src; *p; p++)
    {
        h = h*31 + *p;
    }
    return h;
}

KeyType const2int(char *str){
    KeyType sum = 0;
    int i = 0;
    while(str[i]!= '\0')
    {
        if(str[i]>='0'&&str[i]<='9')
            sum=sum*10+(str[i]-'0');
        i++;
    }
    return sum;
}
