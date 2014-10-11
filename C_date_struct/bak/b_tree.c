/*
* 二叉树建立 二叉树遍历 二叉树复制 判断等价性 线索二叉树 历遍线索二叉树
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FIFO.h"

#define INIT_DATE	10

#define contain_of(ptr, type, num) \
	(type *)((ptr) - (int)(&((type *)0)->num))

typedef struct _BinTree{
    int date;
    struct _BinTree *lchild;
    struct _BinTree *rchild;
}BinTreeNode;

/*
* @function : Creat an binary tree with nNode left childs
* and right childs The '*T' is the root of this binary tree
*/

#ifdef recursion
int BinTreeCreat(BinTreeNode **T, int nNode)
{
    if (nNode <= 0)
	return -1;
    *T = (BinTreeNode *)malloc(sizeof(BinTreeNode));
    if (!(*T)){
       return -1;
    }
    (*T)->date = nNode;

    BinTreeCreat(&(*T)->lchild, --nNode);
    BinTreeCreat(&(*T)->rchild, --nNode);
    return 0;
}
#else
BinTreeNode *BinTreeCreat(int nNode,FIFO BinTreeQueue)
{
    BinTreeNode *root;
    BinTreeNode **LocalNode;
    BinTreeNode **Localchild;
    int count ;    

    LocalNode = &root;
    PUSH(BinTreeQueue, LocalNode);

    for (count = 0; count < nNode; count++){
	POP(BinTreeQueue, LocalNode);

	if (LocalNode){
	    *LocalNode = malloc(sizeof(BinTreeNode));
	    (*LocalNode)->date = count;

	    Localchild = &(*LocalNode)->lchild;
            PUSH(BinTreeQueue,Localchild);
	    Localchild = &(*LocalNode)->rchild;
	    PUSH(BinTreeQueue,Localchild);
	}else{
 	   break;	
	}  
    }

   return root;
}
#endif


/*
* @function : binary tree's  VLR traverse
*/
BinTreeNode *VLRTraverse(BinTreeNode *T)
{
    if (T == NULL)
	return;
    printf("date : %d\n",T->date);
    VLRTraverse(T->lchild);
    VLRTraverse(T->rchild);	
}

void main()
{
   BinTreeNode *T = NULL;

   DECLARE_FIFO(BinTreeQueue,100);

   T = BinTreeCreat(10,BinTreeQueue);
   VLRTraverse(T);
}





