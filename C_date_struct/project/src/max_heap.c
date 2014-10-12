#include <stdio.h>
#include <stdlib.h>

#define MaxHeapCreat(__name,__nodes) \
  MaxHeap __name = { \
   .NodeList = malloc(sizeof(MaxHeapNode)*__nodes), \
   .CurrentSize = 0, \
   .MaxSize = __nodes,}
#define DEBUG_CHECK(__condiction,__ret) \
	if ((__condiction)) \
	{ printf(""#__condiction" is not meeted\n return : "#__ret" \n"); return (__ret);}

typedef struct{
    int key;    
}MaxHeapNode;

typedef struct{
   MaxHeapNode *NodeList;
   int CurrentSize;
   const int MaxSize;
}MaxHeap;

int MaxHeapInsertNode(MaxHeap *Heap, 
			MaxHeapNode Node)
{
    int Site;
    DEBUG_CHECK(Heap->CurrentSize + 1 > Heap->MaxSize, -1);

    Site = ++Heap->CurrentSize;
    while ((Site != 1) && Node.key > Heap->NodeList[Site/2].key ){
	Heap->NodeList[Site] = Heap->NodeList[Site/2];
	Site /= 2;
    }
    
    Heap->NodeList[Site] = Node;
    return 0;       
}

int MaxHeapInsertKey(MaxHeap *Heap, int Key)
{
     DEBUG_CHECK(Heap->CurrentSize + 1 > Heap->MaxSize, -1);
     MaxHeapNode Node = {.key = Key};
     MaxHeapInsertNode(Heap,Node);
     return 0;
}

void main(void)
{
   MaxHeapCreat(Heap,10);
   MaxHeapInsertKey(&Heap, 20);
}
