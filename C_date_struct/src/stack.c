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
}stack;

#define STACK_CREAT(name,ssize) \
stack name;\
name.stack = malloc((ssize));\
memset(name.stack,0,(ssize));\
name.size=ssize;\
name.sp = (void *)(name.stack+(ssize))

#define IS_FULL(name) \
(name.sp <= name.stack ? 1 : 0)

#define IS_EMPTY(name) \
(name.sp >= (name.stack + name.size) ? 1 : 0)

#define PUSH(name,num,type) do{\
    *((type *)(name.sp)) = num;\
     name.sp -= sizeof(type);\
}while(0)

#define POP(name,buf,type)  \
 name.sp += sizeof(type);\
 buf = *((type *)name.sp);

#define DESTORY(name) \
    name.sp = NULL ;\
    free(name.stack)


/*坐标*/
typedef struct{
    short int vert;
    short int horiz;
}location;

/*移动*/
typedef int (*move)(void *obj);
/*查看到底有几个方向可以走*/
typedef int (*probe)(void *obj);
/*查看要走的方向是不是原来的位置*/
typedef struct{
   char (*map)[10];  /*手中的地图*/
   location site;    /*当前坐标*/
   move forward;     /*前进*/
   move back;	     /*返回上一层*/
   probe check;      /*查看门*/
   stack route;      /*进来的路线*/
   int dir[8];	     /*可以进入的门*/
   int lastdir;      /*原来的方向*/
}player;

void main()
{
    STACK_CREAT(my_stack,sizeof(player)*100);
    location site = {.horiz = 5,.vert = 5};

    location buf;

    memset(&buf, 0, sizeof(buf));

    PUSH(my_stack,site,location);
    if(IS_EMPTY(my_stack)){
	printf("Is empty\n");	
	}else{
      printf("No empty\n");
    }
    POP(my_stack,buf,location)
    printf("pop the : (%d,%d) \n",buf.horiz, buf.vert);
}




















#ifdef __cplusplus
}
#endif
