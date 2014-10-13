#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BLOCK_SIZE 2

#define BLOCK_IS_EMPTY(_ptr) ((_ptr)->mlist_head->size >= BLOCK_SIZE ? 1 : 0)
#define BLOCK_IS_FULL(_ptr)  ((_ptr)->mlist_head->size <= 0 ? 1 : 0) 
#define PRE_BLOCK_IS_NULL(_ptr) (!((_ptr)->mlist_head->pre)) 
#define PUSH(_ptr,_date) push(_ptr, _date, sizeof(_date))
#define POP(_ptr,_buf) pop(_ptr, _buf, sizeof(_buf))

#define ARRAY_NUM(array) (sizeof(array)/sizeof(array[0]))

#define INIT_ARRAY(array) do{\
    for ( array[0] =  (ARRAY_NUM(array) - 1);\
		 array[0] > 0; array[0]--) \
	array[array[0]] = array[0]; \
}while(0)

#define PRINT_FINAL_ARRAY(array) do{\
    printf("the %s is :\n",#array);\
    printf("%d  ",array[0]);\
    for (array[0] = 1; array[0] < \
    	ARRAY_NUM(array); array[0]++) \
      printf("%d  ",array[array[0]]);\
    printf("\n\n");\
}while(0)

#define GET_STA(ptr) printf("the status : %d\n",ptr->size)

#define ALLOC_DYSTACK(name) \
	stack *name = malloc(sizeof(stack));\
	name->mlist_head = malloc(sizeof(memnode));\
	name->mlist_head->mem = malloc(BLOCK_SIZE);\
	name->mlist_head->size = BLOCK_SIZE;\
	name->mlist_head->next = NULL;\
	name->mlist_head->pre = NULL;\
	name->size = BLOCK_SIZE;\
	name->sp = name->mlist_head->mem

/*
*@ each stack has its own memory block list
*  obviously,this stack is dynamic so it can 
*  grow up 
*/
typedef struct _memblock{
    void *mem;
    int size;
    struct _memblock *next;
    struct _memblock *pre;
}memnode;

typedef struct{
    memnode *mlist_head;
    char *sp;
    int size;
}stack;

/*
* @function : add an memory block to the 
* head of the stack's memory list
*/
int add_block(stack *ptr, int size)
{
    
    memnode *block  = malloc(sizeof(memnode));
    if (!(block->mem = malloc(size)))
        return -1;
    block->size = size;
    
    ptr->mlist_head->pre = block;
    block->next = ptr->mlist_head;
    block->pre = NULL;
    ptr->mlist_head = block;

    ptr->sp = ptr->mlist_head->mem;
    ptr->size += size;

    return 0;
}
/*
* @notice :The users should avoid to using the 
* functions directly. I will prove an MACRO for you later
*/
int push(stack *ptr, void *date, int len)
{	
    int count;

    for (count = 0; count < len; count++){
      if (BLOCK_IS_FULL(ptr)){
        if(PRE_BLOCK_IS_NULL(ptr)){
	  if (add_block(ptr, BLOCK_SIZE))
	     return -1;
        }else{
	    ptr->mlist_head = ptr->mlist_head->pre;
	    ptr->sp = ptr->mlist_head->mem;
        } 	
      }
        *(ptr->sp++ ) = *((char *)date + count);
	ptr->size--;
    	ptr->mlist_head->size--;
    }

   return 0;
}

int pop(stack *ptr, void *buf, int len)
{
    int count;

    for (count = 0; count < len; count ++){
	if (BLOCK_IS_EMPTY(ptr)){
	    ptr->mlist_head = ptr->mlist_head->next;
	    ptr->sp = ptr->mlist_head->mem + BLOCK_SIZE;
	    free(ptr->mlist_head->pre->mem);
	    ptr->mlist_head->pre = NULL;
	    ptr->size -= BLOCK_SIZE;
	}
	*((char *)buf  + len - count - 1 ) =  *(--ptr->sp);
	ptr->size++;
    	ptr->mlist_head->size++;
    }

    return 0;
}	


void main()
{
   char w_buf[10];
   char r_buf0[10];
   char r_buf1[10];
   unsigned int stick;
   int iw_buf[1000];
   int ir_buf[1000];
   stick = clock();

   INIT_ARRAY(w_buf);
    INIT_ARRAY(iw_buf);

   ALLOC_DYSTACK(test);
   GET_STA(test);

   PUSH(test, w_buf);
   GET_STA(test);
   POP(test, r_buf0);
   GET_STA(test);

   PUSH(test, w_buf);
   GET_STA(test);
   POP(test, r_buf1);
   GET_STA(test);

   PUSH(test,iw_buf);
   POP(test,ir_buf);
   GET_STA(test);

   PRINT_FINAL_ARRAY(ir_buf);
   PRINT_FINAL_ARRAY(r_buf0);
   PRINT_FINAL_ARRAY(r_buf1);

   stick = clock() - stick;
   printf("the time is : %u\n",stick);
}









#ifdef __cplusplus
}
#endif
