#include "FIFO.h"
#include <stdio.h>
#include <stdlib.h>

#define ADD_HEAD(__ROOT) do{\
	ThreadBinTreeNode *__HEAD = \
		malloc(sizeof(ThreadBinTreeNode)); \
	__HEAD->data = -1;\
	__HEAD->lchild = (__ROOT); \
	while((__ROOT)->rchild) \
	  (__ROOT) = (__ROOT)->rchild; \
	__HEAD->rchild = (__ROOT); \
	(__ROOT)->rchild = __HEAD; \
	(__ROOT)->RTag = Thread;\
	(__ROOT) = __HEAD->lchild; \
	while((__ROOT)->LTag == Link) \
	   (__ROOT) = (__ROOT)->lchild; \
	(__ROOT)->lchild = __HEAD; \
	(__ROOT) = __HEAD;}while(0)

#define INIT_THREAD(__TREE) do{\
	ThreadBinTreeNode *__PRE; \
	__PRE = malloc(sizeof(ThreadBinTreeNode)); \
	InThreading((__TREE), &__PRE);\
	ADD_HEAD(*(__TREE));}while(0)

#define CREAT_THREAD_TREE(__name, __nodes) \
	DECLARE_FIFO(__name##FIFO,__nodes*10);\
	ThreadBinTreeNode *__name = NULL;\
	__name = CreatTree(__name##FIFO,__nodes);\
	INIT_THREAD(&__name)
	

typedef enum {Link, Thread} PointerTag;
typedef struct _BinTree{
    int data;
    PointerTag LTag;
    PointerTag RTag;
    struct _BinTree *lchild;
    struct _BinTree *rchild;
}ThreadBinTreeNode;
typedef int (*OrderAction)(void *arg);


ThreadBinTreeNode *CreatTree(FIFO BinTreeQueue, int nNodes)
{
    ThreadBinTreeNode *root;
    ThreadBinTreeNode **LocalNode = &root;
    ThreadBinTreeNode **LocalChildNode;
    PUSH(BinTreeQueue, LocalNode);
    
    int count;
     for (count = 0; count < nNodes; count++){
          POP(BinTreeQueue, LocalNode);
	 *LocalNode = malloc(sizeof(ThreadBinTreeNode));
	  (*LocalNode)->data = count;
	  (*LocalNode)->lchild = NULL;
	  (*LocalNode)->rchild = NULL;
	  (*LocalNode)->RTag = Link;
	  (*LocalNode)->LTag = Link;
	  LocalChildNode = &(*LocalNode)->lchild;
	  PUSH(BinTreeQueue, LocalChildNode);
	  LocalChildNode = &(*LocalNode)->rchild;
	  PUSH(BinTreeQueue, LocalChildNode);
    }
    return root;
}

/*
* @function : Init thread
*/
void InThreading(ThreadBinTreeNode **T, 
		ThreadBinTreeNode **pre)
{
	
  if (*T){
    InThreading(&(*T)->lchild,pre);
 
    if ((*T)->lchild == NULL){
        (*T)->lchild = *pre;
	(*T)->LTag = Thread;
    }
    if ((*pre)->rchild == NULL){
	(*pre)->rchild = *T;
    	(*pre)->RTag = Thread;
    }
     *pre = *T;
    InThreading(&(*T)->rchild,pre);
  }
}

void ThreadBinTreeLVROrder(ThreadBinTreeNode *const Head, 
				OrderAction Action)
{
    ThreadBinTreeNode *T = Head->lchild;

    while (T->LTag == Link)
      T = T->lchild;
    printf("%d  ",T->data);
    
    while (T->rchild != Head){
      if (T->RTag == Thread){
        T = T->rchild;
	printf("%d  ",T->data);      
      }else{
        T = T->rchild;
	while (T->LTag == Link)
	  T = T->lchild;
	printf("%d  ",T->data);
      }
    }
    printf("\n");
}

int 
LevelOrder(FIFO BinTreeQueue, ThreadBinTreeNode *root)
{
    PUSH(BinTreeQueue, root);
    for (;;){
      if (POP(BinTreeQueue,root) == 0){
         printf("%d\n",root->data);
	 if(root->lchild)
	   PUSH(BinTreeQueue, root->lchild);
	 if(root->rchild)
	   PUSH(BinTreeQueue, root->rchild);       
      }else{
    	 break;
      }
    }
}
void main(void)
{
   CREAT_THREAD_TREE(T, 10); 
   ThreadBinTreeLVROrder(T,NULL);
}
