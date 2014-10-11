#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include <stdlib.h>
/*we will add more arch please grep the /project/arch */
#define X86_ARCH
#ifdef X86_ARCH 
typedef unsigned int uint32_t;
typedef int 	     int32_t;
#endif 

typedef uint32_t (*Dlist_print)(void *date);
typedef struct _Dlist
{
  struct _Dlist *pre;
  struct _Dlist *next;
  void *date;
  Dlist_print pfunc;
}DlistNode;

/*
*@function : Init a static DlistNode
*notice : do not use the 'inline' keyword
*/
#define NODE_INIT(node) do{\
    (node)->pre = NULL;\
    (node)->next = NULL;\
    (node)->date = NULL;\
}while(0)
#define  IS_ERROR(node) ((node) ? 1 : 0)
/*
*@function : build an Dlist
* return the head's pointer
* date[] is an array which contain the menber of lis->date
*/ 
DlistNode *build_dlist(const uint32_t node_num,   int32_t *const date)
{
    DlistNode *local_dlist;
    DlistNode *head;
    DlistNode *new;
    uint32_t count;
    /**/
    head = malloc(sizeof(DlistNode));

    local_dlist = head;
    if(IS_ERROR(head)){
    	return NULL;
    }else{
    	NODE_INIT(head);
    }
    
    for(count = 0;count < node_num;count++ ){
	/*build list here*/        
	new = malloc(sizeof(DlistNode));
	if(IS_ERROR(new)){
	  return NULL;
  	}else{
	/*notice :add to tail*/
	  new->date = &date[count];
	  local_dlist->next = new;
          new->pre = local_dlist;
	  local_dlist = new;
	}
    }
    return head;
}





















#ifdef __cplusplus
}
#endif
