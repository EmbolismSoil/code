#include <stdio.h>
#include <stdlib.h>

#define MaxHeapCreat(__name,__nodes) \
  MaxHeap *__name = { \
   .NodeList = malloc(sizeof(MaxHeapNode)*__nodes), \
   .CurrentSize = 0, \
   .MaxSize = __nodes,}

typedef struct{
    int lchild;
    int rchild;
    int key;    
}MaxHeapNode;

typedef struct{
   MaxHeapNode *NodeList;
   int CurrentSize;
   const int MaxSize;
}MaxHeap;

int MaxHeapInsert(MaxHeap *Heap, 
			MaxHeapNode Node)
{
    int Site;
    if (Heap->Current + 1 > Heap->MaxSize) return -1;

    Site = ++Heap->CurrenSize;
    while ((Site != 1) && Node.key > Heap->NodeList[Site/2] ){
	Heap->NodeList[Site] = Heap->NodeList[Site/2];
	Site /= 2;
    }
    
    Heap->NodeList[Site] = Node;
    return 0;       
}


