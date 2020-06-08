/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 */
#ifndef A3_BINARY_H
#define A3_BINARY_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define M (128)
#define LIMIT_M_2 (M % 2 ? (M + 1)/2 : M/2)

typedef struct BPlusNode *BPlusTree,*Position;
typedef long KeyType;
struct BPlusNode{
    int KeyNum;
    KeyType Key[M + 1];
    void *Entry[M + 1];
    BPlusTree Children[M + 1];
    BPlusTree Next;
};

extern BPlusTree Initialize();
extern BPlusTree Insert(BPlusTree T,KeyType Key, void *Entry);
extern BPlusTree Search(BPlusTree T, KeyType Key);
extern BPlusTree free1(BPlusTree T);
#endif
