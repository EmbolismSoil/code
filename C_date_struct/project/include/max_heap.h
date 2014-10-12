
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

extern int MaxHeapInsertKey(MaxHeap *Heap, int Key);
extern int MaxHeapDelectKey(MaxHeap *Heap);
