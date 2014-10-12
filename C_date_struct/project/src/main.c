#include <stdio.h>
#include <max_heap.h>

void main(void)
{
   MaxHeapCreat(Heap,100);
   MaxHeapInsertKey(&Heap, 100);
   printf("the max iterm is : %d\n", MaxHeapDelectKey(&Heap));
}
