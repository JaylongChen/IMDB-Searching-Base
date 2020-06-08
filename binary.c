/*Student name: Zhelong Chen
 *Student number: 1054831
 *Email: zhelong@uoguelph.ca
 * Clarification: This program was done with the help of my brother, who finishes bachelor's degree a few years ago. 
 * 				  He helped me with main, binary and a few algorithms.
 * 				  In this file, he helped me with insert,search and remove.
 */
#include "binary.h"
#include "name.h"

static KeyType Unavailable = INT_MIN;

/*malloc modes for a tree*/
static BPlusTree MallocNewNode()
{
    BPlusTree NewNode;
    int i;
    NewNode = malloc(sizeof(struct BPlusNode));
    if (NewNode == NULL)
    {
        exit(EXIT_FAILURE);
	}

    i = 0;
    while (i < M + 1)
    {
        NewNode->Key[i] = Unavailable;
        NewNode->Children[i] = NULL;
        i++;
    }
    
    NewNode->Next = NULL;
    NewNode->KeyNum = 0;

    return NewNode;
}

/*initialize a tree by calling mallocNewNode*/
extern BPlusTree Initialize()
{

    BPlusTree T;
    if (M < (3))
    {
        printf("M too low");
        exit(EXIT_FAILURE);
    }
    T = MallocNewNode();

    return T;
}

static Position FindMostLeft(Position P)
{
    Position Tmp;

    Tmp = P;

    while (Tmp != NULL && Tmp->Children[0] != NULL) 
    {
        Tmp = Tmp->Children[0];
    }
    return Tmp;
}

static Position FindMostRight(Position P)
{
    Position Tmp;

    Tmp = P;

    while (Tmp != NULL && Tmp->Children[Tmp->KeyNum - 1] != NULL) 
    {
        Tmp = Tmp->Children[Tmp->KeyNum - 1];
    }
    return Tmp;
}

static Position FindSibling(Position Parent,int i)
{
    Position Sibling;
    int Limit;

    Limit = M;

    Sibling = NULL;
    if (i == 0)
    {
        if (Parent->Children[1]->KeyNum < Limit)
            Sibling = Parent->Children[1];
    }
    else if (Parent->Children[i - 1]->KeyNum < Limit)
        Sibling = Parent->Children[i - 1];
    else if (i + 1 < Parent->KeyNum && Parent->Children[i + 1]->KeyNum < Limit)
    {
        Sibling = Parent->Children[i + 1];
    }

    return Sibling;
}

/*insertElement: insert elements at the correct spot of tree */
static Position InsertElement(int isKey, Position Parent,Position X,KeyType Key,int i,int j, void *Entry){

    int k;
    if (isKey)
    {
        k = X->KeyNum - 1;
        while (k >= j)
        {
            X->Key[k + 1] = X->Key[k];
            X->Entry[k + 1] = X->Entry[k];
            k--;
        }

        X->Key[j] = Key;
        X->Entry[j] = Entry;
        if (Parent != NULL)
            Parent->Key[i] = X->Key[0];

        X->KeyNum++;

    }
    else
    {

        if (X->Children[0] == NULL)
        {
            if (i > 0)
                Parent->Children[i - 1]->Next = X;
            X->Next = Parent->Children[i];
        }

        k = Parent->KeyNum - 1;
        while (k >= i)
        {
            Parent->Children[k + 1] = Parent->Children[k];
            Parent->Key[k + 1] = Parent->Key[k];
            k--;
        }
        Parent->Key[i] = X->Key[0];
        Parent->Entry[i] = Entry;
        Parent->Children[i] = X;

        Parent->KeyNum++;

    }
    return X;
}

/*remove items in tree*/
static Position RemoveElement(int isKey, Position Parent,Position X,int i,int j)
{

    int k,Limit;

    if (isKey)
    {
        Limit = X->KeyNum;
        k = j + 1;
        while (k < Limit)
        {
            X->Key[k - 1] = X->Key[k];
            X->Entry[k - 1] = X->Entry[k];
            k++;
        }

        X->Key[X->KeyNum - 1] = Unavailable;

        Parent->Key[i] = X->Key[0];
        X->KeyNum--;
    }else{
        if (X->Children[0] == NULL && i > 0){
            Parent->Children[i - 1]->Next = Parent->Children[i + 1];
        }
        Limit = Parent->KeyNum;
        k = i + 1;
        while (k < Limit){
            Parent->Children[k - 1] = Parent->Children[k];
            Parent->Key[k - 1] = Parent->Key[k];
            k++;
        }

        Parent->Children[Parent->KeyNum - 1] = NULL;
        Parent->Key[Parent->KeyNum - 1] = Unavailable;

        Parent->KeyNum--;

    }
    return X;
}


static Position MoveElement(Position Src,Position Dst,Position Parent,int i,int n){
    KeyType TmpKey;
    void *TmpEntry;
    Position Child;
    int j,SrcInFront;

    SrcInFront = 0;

    if (Src->Key[0] < Dst->Key[0])
        SrcInFront = 1;

    j = 0;
    if (SrcInFront){
        if (Src->Children[0] != NULL){
            while (j < n) {
                Child = Src->Children[Src->KeyNum - 1];
                RemoveElement(0, Src, Child, Src->KeyNum - 1, Unavailable);
                InsertElement(0, Dst, Child, Unavailable, 0, Unavailable, NULL);
                j++;
            }
        }else{
            while (j < n) {
                TmpKey = Src->Key[Src->KeyNum -1];
                TmpEntry = Src->Entry[Src->KeyNum -1];
                RemoveElement(1, Parent, Src, i, Src->KeyNum - 1);
                InsertElement(1, Parent, Dst, TmpKey, i + 1, 0, TmpEntry);
                j++;
            }

        }

        Parent->Key[i + 1] = Dst->Key[0];
        if (Src->KeyNum > 0)
            FindMostRight(Src)->Next = FindMostLeft(Dst);

    }else{
        if (Src->Children[0] != NULL){
            while (j < n) {
                Child = Src->Children[0];
                RemoveElement(0, Src, Child, 0, Unavailable);
                InsertElement(0, Dst, Child, Unavailable, Dst->KeyNum, Unavailable, NULL);
                j++;
            }

        }else{
            while (j < n) {
                TmpKey = Src->Key[0];
                TmpEntry = Src->Entry[0];
                RemoveElement(1, Parent, Src, i, 0);
                InsertElement(1, Parent, Dst, TmpKey, i - 1, Dst->KeyNum, TmpEntry);
                j++;
            }

        }

        Parent->Key[i] = Src->Key[0];

        if (Src->KeyNum > 0)
            FindMostRight(Dst)->Next = FindMostLeft(Src);

    }

    return Parent;
}

static BPlusTree SplitNode(Position Parent,Position X,int i)
{
    int j,k,Limit;
    Position NewNode;

    NewNode = MallocNewNode();

    k = 0;
    j = X->KeyNum / 2;
    Limit = X->KeyNum;
    while (j < Limit)
    {
        if (X->Children[0] != NULL)
        {
            NewNode->Children[k] = X->Children[j];
            X->Children[j] = NULL;
        }
        NewNode->Key[k] = X->Key[j];
        NewNode->Entry[k] = X->Entry[j];
        X->Key[j] = Unavailable;
        NewNode->KeyNum++;X->KeyNum--;
        j++;k++;
    }

    if (Parent != NULL)
        InsertElement(0, Parent, NewNode, Unavailable, i + 1, Unavailable, NULL);
    else
    {
        Parent = MallocNewNode();
        InsertElement(0, Parent, X, Unavailable, 0, Unavailable, NULL);
        InsertElement(0, Parent, NewNode, Unavailable, 1, Unavailable, NULL);

        return Parent;
    }

    return X;
}


/*RecursiveInsert: insert nodes into tree*/
static BPlusTree RecursiveInsert(BPlusTree T,KeyType Key,int i,BPlusTree Parent, void *Entry)
{
    int j,Limit;
    Position Sibling;

    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j])
    {
        j++;
    }
    if (j != 0 && T->Children[0] != NULL) j--;

    if (T->Children[0] == NULL)
    {
        T = InsertElement(1, Parent, T, Key, i, j, Entry);
	}
    else
    {
        T->Children[j] = RecursiveInsert(T->Children[j], Key, j, T, Entry);
	}
    Limit = M;

    if (T->KeyNum > Limit)
    {
        if (Parent == NULL)
        {
            T = SplitNode(Parent, T, i);
        }
        else
        {
            Sibling = FindSibling(Parent, i);
            if (Sibling != NULL)
            {
                MoveElement(T, Sibling, Parent, i, 1);
            }
            else
            {
                T = SplitNode(Parent, T, i);
            }
        }

    }

    if (Parent != NULL)
    {
        Parent->Key[i] = T->Key[0];
    }
    return T;
}


extern BPlusTree Insert(BPlusTree T,KeyType Key, void *Entry)
{
    return RecursiveInsert(T, Key, 0, NULL, Entry);
}

/*search through trees*/
static BPlusTree RecursiveSearch(BPlusTree T,KeyType Key,int i,BPlusTree Parent)
{
    int j;
    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j])
    {
        if (Key == T->Key[j])
            break;
        j++;
    }

    if (T->Children[0] == NULL)
    {
        if (Key != T->Key[j] || j == T->KeyNum)
            return NULL;
    }else
    if (j == T->KeyNum || Key < T->Key[j]) 
    {
		j--;
	}

    if (T->Children[0] == NULL)
    {
        return T;
    }
    else
    {
        return RecursiveSearch(T->Children[j], Key, j, T);
    }

}


extern BPlusTree Search(BPlusTree T,KeyType Key)
{
    return RecursiveSearch(T, Key, 0, NULL);
}

/*free the malloced tree*/
extern BPlusTree free1(BPlusTree T){
    int i,j;
    if (T != NULL){
        i = 0;
        while (i < T->KeyNum + 1){
            free(T->Children[i]);i++;
        }
        j = 0;
        while (j < T->KeyNum)
            printf("%ld:",T->Key[j++]);
        printf(") ");
        free(T);
        T = NULL;
    }

    return T;
}




