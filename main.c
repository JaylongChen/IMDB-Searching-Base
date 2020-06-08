/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 */
#include <stdio.h>
#include <string.h>
#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"
#include "common.h"

#define NAME_BASIC "/name.basics.tsv"
#define TITLE_BASIC "/title.basics.tsv"
#define TITLE_PRINCIPALS "/title.principals.tsv"


void safe_flush(FILE *fp) {
    int ch;
    while ((ch = fgetc(fp)) != EOF && ch != '\n');
}

/*mystrcat: helper function to merge character by character*/
void mystrcat(char *s1, char *s2, char *s3) 
{
    int i = 0, j = 0, k = 0;
    while (i < strlen(s2)) 
    {
        s1[k++] = s2[i++];
    }
    while (j < strlen(s3)) 
    {
        s1[k++] = s3[j++];
    }
    s1[k] = '\0';
}

int main(int argc, char **argv) 
{
    char order[10] = {0};
    char param[128] = {0};
    int orderindex = 0;
    int paramindex = 0;
    int i = 0;
    int lastchar = 0;
    char NAME_BASIC_FILE[300] = {0};
    char TITLE_BASIC_FILE[300] = {0};
    char TITLE_PRINCIPALS_FILE[300] = {0};
    char str[1000], p[] = "end";
    BPlusTree bPlusTreeFound1;
    BPlusTree bPlusTreeFound2;
    BPlusTree bPlusTreeFound3;

    NameBasic nameBasicFound;
    TitleBasic titleBasicFound;
    PrincipalsBasic principalsBasicFound;

    int foundIndex1 = 0;
    int foundIndex2 = 0;
    int foundIndex3 = 0;

    KeyType key = 0;
    KeyType key1 = 0;
    KeyType key2 = 0;
    KeyType key3 = 0;

    NameBasic nameBasicNodes;
    TitleBasic titleBasicNodes;
    PrincipalsBasic principalsBasicNodes;

    BPlusTree Name_Basics_NConst;
    BPlusTree Name_Basics_PrimaryName;
    BPlusTree Title_Basics_TConst;
    BPlusTree Title_Basics_PrimaryTitle;
    BPlusTree Principals_Basics_TConst;
    BPlusTree Principals_Basics_NConst;

    int num = 0;
    int found = 0;
    /*check valid command line arguments*/
    if (argc > 2) 
    {
        printf("too many params.\n");
        return 0;
    }
    if (argc < 2) 
    {
        printf("too few params.\n");
        return 0;
    }

	/*call helper function to merge directories and files together*/
    mystrcat(NAME_BASIC_FILE, argv[1], NAME_BASIC);

    mystrcat(TITLE_BASIC_FILE, argv[1], TITLE_BASIC);

    mystrcat(TITLE_PRINCIPALS_FILE, argv[1], TITLE_PRINCIPALS);
    
    printf("constructing by b plus tree..pls wait..\n");

	/*initialize a tree for names*/
    Name_Basics_NConst = Initialize();
    
    num = nameMatchLineNums(NAME_BASIC_FILE);
    
    /*fill in name_basics struct*/
    getNameBasics(NAME_BASIC_FILE, &nameBasicNodes, num);
    
    /*insert keys to nodes of tree*/
    for (; found < num; found++) 
    {
        key = const2int((nameBasicNodes + found)->nconst);
        Name_Basics_NConst = Insert(Name_Basics_NConst, key, nameBasicNodes + found);
    }

    Name_Basics_PrimaryName = Initialize();
    found = 0;
    for (; found < num; found++) 
    {
        key = str2int((nameBasicNodes + found)->primaryName);
        Name_Basics_PrimaryName = Insert(Name_Basics_PrimaryName, key, nameBasicNodes + found);
    }
    Title_Basics_TConst = Initialize();
    num = titleMatchLineNums(TITLE_BASIC_FILE);
    getTitleBasics(TITLE_BASIC_FILE, &titleBasicNodes, num);
    found = 0;
    for (; found < num; found++) 
    {
        key = const2int((titleBasicNodes + found)->tconst);
        Title_Basics_TConst = Insert(Title_Basics_TConst, key, titleBasicNodes + found);
    }

    Title_Basics_PrimaryTitle = Initialize();
    found = 0;
    for (; found < num; found++) 
    {
        key = str2int((titleBasicNodes + found)->primaryTitle);
        Title_Basics_PrimaryTitle = Insert(Title_Basics_PrimaryTitle, key, titleBasicNodes + found);
    }
    Principals_Basics_TConst = Initialize();
    num = principalMatchLineNums(TITLE_PRINCIPALS_FILE);
    getPrincipalsBasics(TITLE_PRINCIPALS_FILE, &principalsBasicNodes, num);
    found = 0;
    for (; found < num; found++) 
    {
        key = const2int((principalsBasicNodes + found)->tconst);
        Principals_Basics_TConst = Insert(Principals_Basics_TConst, key, principalsBasicNodes + found);
    }
    Principals_Basics_NConst = Initialize();
    found = 0;
    for (; found < num; found++) 
    {
        key = const2int((principalsBasicNodes + found)->nconst);
        Principals_Basics_NConst = Insert(Principals_Basics_NConst, key, principalsBasicNodes + found);
    }
    
    /*get user input for search*/
    while (strcmp(str, p) != 0) 
    {
        printf("> ");
        scanf("%[^\n]", str);
        safe_flush(stdin);
        memset(order, 0, 10);
        memset(param, 0, 128);
        orderindex = 0;
        paramindex = 0;
        i = 0;
        lastchar = 0;

        while (str[i] != '\0') 
        {
            if (str[i] == ' ') 
            {
                if (strlen(order) == 0) 
                {
                    i++;
                    continue;
                } 
                else 
                {
                    order[orderindex] = '\0';
                    break;
                }
            } 
            else 
            {
                order[orderindex++] = str[i++];
            }
        }
        while (str[i] != '\0') 
        {
            if (str[i] == ' ') 
            {
                if (strlen(param) == 0) 
                {
                    i++;
                    continue;
                } 
                else 
                {
                    param[paramindex++] = str[i++];
                }
            } 
            else 
            {
                lastchar = paramindex;
                param[paramindex++] = str[i++];
            }
        }
        
        param[++lastchar] = '\0';
        if (strlen(param) == 0) 
        {
            printf("wrong order or param!!\n");
        } 
        /*this part is done with the help of my brother*/
        else if (strcmp(order, "name") == 0) 
        {
            key1 = str2int(param);
            bPlusTreeFound1 = Search(Name_Basics_PrimaryName, key1);
            if (bPlusTreeFound1 == NULL) 
            {
                continue;
            }
            while (bPlusTreeFound1 != NULL) 
            {
                foundIndex1 = 0;
                for (; foundIndex1 < bPlusTreeFound1->KeyNum; foundIndex1++) 
                {
                    if (bPlusTreeFound1->Key[foundIndex1] == key1) 
                    {
                        nameBasicFound = (NameBasic) (bPlusTreeFound1->Entry[foundIndex1]);
                        key2 = const2int(nameBasicFound->nconst);
                        bPlusTreeFound2 = Search(Principals_Basics_NConst, key2);
                        if (bPlusTreeFound2 == NULL) 
                        {
                            continue;
                        }
                        while (bPlusTreeFound2 != NULL) 
                        {
                            foundIndex2 = 0;
                            for (; foundIndex2 < bPlusTreeFound2->KeyNum; foundIndex2++) 
                            {
                                if (bPlusTreeFound2->Key[foundIndex2] == key2) 
                                {
                                    principalsBasicFound = (PrincipalsBasic) (bPlusTreeFound2->Entry[foundIndex2]);
                                    key3 = const2int(principalsBasicFound->tconst);
                                    bPlusTreeFound3 = Search(Title_Basics_TConst, key3);
                                    if (bPlusTreeFound3 == NULL) 
                                    {
                                        continue;
                                    }
                                    while (bPlusTreeFound3 != NULL) 
                                    {
                                        foundIndex3 = 0;
                                        for (; foundIndex3 < bPlusTreeFound3->KeyNum; foundIndex3++) 
                                        {
                                            if (bPlusTreeFound3->Key[foundIndex3] == key3) 
                                            {
                                                titleBasicFound = (TitleBasic) (bPlusTreeFound3->Entry[foundIndex3]);
                                                printf("%s , %s", titleBasicFound->primaryTitle, principalsBasicFound->characters);
                                            } 
                                            else if (bPlusTreeFound3->Key[foundIndex3] > key3) 
                                            {
                                                bPlusTreeFound3 = NULL;
                                                break;
                                            }
                                        }
                                        if (bPlusTreeFound3 != NULL) 
                                        {
                                            bPlusTreeFound3 = bPlusTreeFound3->Next;
                                        }
                                    }
                                } 
                                else if (bPlusTreeFound2->Key[foundIndex2] > key2) 
                                {
                                    bPlusTreeFound2 = NULL;
                                    break;
                                }
                            }
                            if (bPlusTreeFound2 != NULL) 
                            {
                                bPlusTreeFound2 = bPlusTreeFound2->Next;
                            }
                        }


                    } 
                    else if (bPlusTreeFound1->Key[foundIndex1] > key1) 
                    {
                        bPlusTreeFound1 = NULL;
                        break;
                    }
                }
                if (bPlusTreeFound1 != NULL) 
                {
                    bPlusTreeFound1 = bPlusTreeFound1->Next;
                }
            }


        } 
        else if (strcmp(order, "title") == 0) 
        {
            key1 = str2int(param);
            bPlusTreeFound1 = Search(Title_Basics_PrimaryTitle, key1);
            if (bPlusTreeFound1 == NULL) 
            {
                continue;
            }
            while (bPlusTreeFound1 != NULL) 
            {
                foundIndex1 = 0;
                for (; foundIndex1 < bPlusTreeFound1->KeyNum; foundIndex1++) 
                {
                    if (bPlusTreeFound1->Key[foundIndex1] == key1) 
                    {
                        titleBasicFound = (TitleBasic) (bPlusTreeFound1->Entry[foundIndex1]);
                        key2 = const2int(titleBasicFound->tconst);
                        bPlusTreeFound2 = Search(Principals_Basics_TConst, key2);
                        if (bPlusTreeFound2 == NULL) 
                        {
                            continue;
                        }
                        while (bPlusTreeFound2 != NULL) 
                        {
                            foundIndex2 = 0;
                            for (; foundIndex2 < bPlusTreeFound2->KeyNum; foundIndex2++) 
                            {
                                if (bPlusTreeFound2->Key[foundIndex2] == key2) 
                                {
                                    principalsBasicFound = (PrincipalsBasic) (bPlusTreeFound2->Entry[foundIndex2]);
                                    key3 = const2int(principalsBasicFound->nconst);
                                    bPlusTreeFound3 = Search(Name_Basics_NConst, key3);
                                    if (bPlusTreeFound3 == NULL) 
                                    {
                                        continue;
                                    }
                                    while (bPlusTreeFound3 != NULL) 
                                    {
                                        foundIndex3 = 0;
                                        for (; foundIndex3 < bPlusTreeFound3->KeyNum; foundIndex3++) 
                                        {
                                            if (bPlusTreeFound3->Key[foundIndex3] == key3) 
                                            {
                                                nameBasicFound = (NameBasic) (bPlusTreeFound3->Entry[foundIndex3]);
                                                printf("%s , %s", nameBasicFound->primaryName, principalsBasicFound->characters);
                                            } 
                                            else if (bPlusTreeFound3->Key[foundIndex3] > key3) 
                                            {
                                                bPlusTreeFound3 = NULL;
                                                break;
                                            }
                                        }
                                        if (bPlusTreeFound3 != NULL) 
                                        {
                                            bPlusTreeFound3 = bPlusTreeFound3->Next;
                                        }
                                    }
                                } 
                                else if (bPlusTreeFound2->Key[foundIndex2] > key2) 
                                {
                                    bPlusTreeFound2 = NULL;
                                    break;
                                }
                            }
                            if (bPlusTreeFound2 != NULL) 
                            {
                                bPlusTreeFound2 = bPlusTreeFound2->Next;
                            }
                        }


                    } 
                    else if (bPlusTreeFound1->Key[foundIndex1] > key1) 
                    {
                        bPlusTreeFound1 = NULL;
                        break;
                    }
                }
                if (bPlusTreeFound1 != NULL) {
                    bPlusTreeFound1 = bPlusTreeFound1->Next;
                }
            }


        } 
        else 
        {
            printf("wrong order or param!!\n");
        }
    }
    return 0;
}
