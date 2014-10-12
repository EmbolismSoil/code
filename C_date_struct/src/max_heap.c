#include <stdio.h>
#include <stdlib.h>
#include "max_heap.h"

static int MaxHeapInsertNode(MaxHeap *Heap, 
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
