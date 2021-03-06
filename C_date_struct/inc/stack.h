#ifdef __cplusplus
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
   void *stack;
   void *sp;
   int size;
   int sta;
}stack;

#define STACK_CREAT(name,ssize) \
stack name;\
name.stack = malloc((ssize));\
memset(name.stack,0,(ssize));\
name.sta=ssize;\
name.size=ssize;\
name.sp = (void *)(name.stack+(ssize))

#define IS_FULL(name) \
(name.sp <= name.stack ? 1 : 0)

#define IS_EMPTY(name) \
(name.sp >= (name.stack + name.size) ? 1 : 0)

#define PUSH(name,num,type) do{\
    *((type *)(name.sp)) = num;\
     name.sp -= sizeof(type);\
     name.sta -= sizeof(type);\
}while(0)

#define POP(name,buf,type)  \
 name.sp += sizeof(type);\
 buf = *((type *)name.sp);\
 name.sta += sizeof(type)\

#define DESTORY(name) \
    name.sp = NULL ;\
    free(name.stack)

/***************************************************************
			deamo
****************************************************************
void main()
{
    STACK_CREAT(my_stack,100);
    PUSH(my_stack,100,int);

    if(IS_EMPTY(my_stack)){
	printf("Is empty\n");	
	}else{
      printf("No empty\n");
    }

    
    printf("pop the : %d \n",POP(my_stack,int));
}
*****************************************************************

*****************************************************************/



















#ifdef __cplusplus
}
#endif
