#include <stdio.h>
#include <stdlib.h>

#define MaxHeapCreat(__name,__nodes) \
  MaxHeap __name = { \
   .NodeList = malloc(sizeof(MaxHeapNode)*__nodes), \
   .CurrentSize = 0, \
   .MaxSize = __nodes,}
#define DEBUG_CHECK_RETURN(__condiction,__ret) \
	if ((__condiction)) \
	{ printf(""#__condiction" is not meeted\n return : "#__ret" \n"); return (__ret);}
#define DEBUG_CHECK(__condiction) \
	if ((__condiction)) printf(""#__condiction" is failed! \n")
#define DEBUG_ASSERT(__condiction) \
	if ((__condiction)) printf(""#__condiction" is failed!\n");\
	assert((__condiction))

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
    DEBUG_CHECK_RETURN(Heap->CurrentSize + 1 > Heap->MaxSize, -1);

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
     DEBUG_CHECK_RETURN(Heap->CurrentSize + 1 > Heap->MaxSize, -1);
     MaxHeapNode Node = {.key = Key};
     MaxHeapInsertNode(Heap,Node);
     return 0;
}

int MaxHeapDelectKey(MaxHeap *Heap)
{
    DEBUG_CHECK(!Heap || !Heap->CurrentSize);

    int MaxIterm = Heap->NodeList[1].key;
    int LastIterm = Heap->NodeList[Heap->CurrentSize].key;
    int parent = 1;
    int child = 2;

    while (child < Heap->CurrentSize){
        if (Heap->NodeList[child].key < Heap->NodeList[child + 1].key)
	    child++;
        Heap->NodeList[parent] =  Heap->NodeList[child];
	parent = child;
	child *= 2; 
    }
    Heap->NodeList[parent].key = LastIterm;
    return MaxIterm;
}


void main(void)
{
   MaxHeapCreat(Heap,10);
   MaxHeapInsertKey(&Heap, 20);
   printf("the max iterm is : %d \n",MaxHeapDelectKey(&Heap));

}
