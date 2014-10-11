/*
* 二叉树建立 二叉树遍历 二叉树复制 判断等价性 线索二叉树 历遍线索二叉树
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FIFO.h"


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
	    (*LocalNode)->lchild = NULL;
	    (*LocalNode)->rchild = NULL;

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

/*
* @fucntion : Level order the binary tree
*/
int LevelOrder(FIFO BinTreeQueue, BinTreeNode *root)
{
    PUSH(BinTreeQueue, root);
    for (;;){
      if (POP(BinTreeQueue,root) == 0){
         printf("%d\n",root->date);
	 if(root->lchild)
	   PUSH(BinTreeQueue, root->lchild);
	 if(root->rchild)
	   PUSH(BinTreeQueue, root->rchild);       
      }else{
    	 break;
      }
    }
}
/*
* @function : copy the binary tree
*/
BinTreeNode *Copy(BinTreeNode *T)
{
    BinTreeNode *LocalTree;
    if (T){
        LocalTree = malloc(sizeof(BinTreeNode));
	LocalTree->date = T->date;
	LocalTree->lchild = Copy(T->lchild);
	LocalTree->rchild = Copy(T->rchild);
	return LocalTree;
    }
    return NULL;
}

int Equal(BinTreeNode *FirstRoot, BinTreeNode *SecondRoot)
{
    return ((!FirstRoot && !SecondRoot) || ((FirstRoot && 
		SecondRoot) && (FirstRoot->date == SecondRoot->date) && 
		Equal(FirstRoot->lchild,SecondRoot->lchild) && 
		Equal(FirstRoot->rchild,SecondRoot->rchild)));
}



/*
void main()
{
   BinTreeNode *T = NULL;
   BinTreeNode *CopyT = NULL;
   DECLARE_FIFO(BinTreeQueue,10);

   T = BinTreeCreat(10,BinTreeQueue);
   LevelOrder(BinTreeQueue,T);
   CopyT = Copy(T);
   LevelOrder(BinTreeQueue,CopyT);
 
   if (Equal(T,CopyT)){
	printf("Equal\n");
   }else{
	printf("Unequal\n");
   }
}
*/




