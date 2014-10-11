#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/*
*@定义方向 
*/
#define N	0
#define NE	1
#define E	2
#define SE	3
#define S	4
#define SW	5
#define W	6
#define NW	7

#define MAX_LEN 20

#define MOVE_N(cite)  do{ \
    (cite)->site.vert -= 1; }while(0) 

#define MOVE_NE(cite) do{\
    (cite)->site.vert -= 1; \
    (cite)->site.horiz += 1;\
    }while(0)

#define MOVE_E(cite) do{ \
    cite->site.horiz += 1; \
    }while(0)

#define MOVE_SE(cite) do{\
    (cite)->site.vert += 1; \
    (cite)->site.horiz += 1;\
    }while(0)

#define MOVE_S(cite) do{\
    (cite)->site.vert += 1; }while(0)

#define MOVE_SW(cite) do{\
	(cite)->site.vert += 1; \
	(cite)->site.horiz -= 1;\
	}while(0)

#define MOVE_W(cite) do{(cite)->site.horiz -= 1;}while(0)

#define MOVE_NW(cite) do{\
        (cite)->site.vert -= 1; \
	(cite)->site.horiz -= 1;}while(0)

#define MARK_OUT(player) player.map[player.site.vert][player.site.horiz] = 5;
#define DECLARE_INIT_PLAYER(name) \
player name = {\
    .site = {.vert = 2, .horiz = 2},\
    .forward = move_forward,\
    .back = move_back,\
    .checkdoor = check_door,\
    .lastdir = 10,\
    .nextdir = 10,\
    .mark = mark_path,\
    .record = record_site,\
    .exit = exit_game,\
}
/*坐标*/
typedef struct{
    short int vert;
    short int horiz;
}location;


/*动作*/
typedef int (*action)(void *obj);

typedef struct{
   location site;    /*当前坐标*/
   action forward;     /*前进*/
   action back;	     /*返回上一层*/
   action checkdoor;      /*查看门*/
   action record;	/*记录当前位置信息*/
   action mark;		/*做路标*/
   action exit;
   stack route;      /*进来的路线*/
   int dir[8];	     /*可以进入的门*/
   int lastdir;      /*原来的方向*/
   int nextdir	;     /*下一个方向*/
   char (*map)[MAX_LEN];  /*手中的地图*/
   void *private;	     /*私有数据，留作拓展*/
}player;


/*
*@记录当前位置坐标
*/
int record_site(void *obj)
{
    player *cite = (player *)obj;
    cite->lastdir = cite->nextdir;
    location buf;
 
    if (IS_FULL((*cite).route)){
        printf("Stack overflow!\n");
	printf("site : (%d,%d)\n\n",cite->site.horiz,cite->site.vert);
	printf("stack status : %d\n\n",cite->route.sta);
	return 0;	
    }else{
      	 PUSH((*cite).route, (*cite).site, location);
	 POP((*cite).route, buf, location); 
	 if (buf.horiz == (*cite).site.horiz && buf.vert == (*cite).site.vert)
	     PUSH((*cite).route, (*cite).site, location);	
    }
	return 1;
}

/*
*@做路标
*/
int mark_path(void *obj)
{
   player *cite = (player *)obj;
   cite->map[cite->site.vert][cite->site.horiz] = 4;
}

/*
*@ move_forward : 按照特定的方向前进
*/
int move_forward(void *obj)
{
    player *cite = (player *)obj;
    int dir = cite->nextdir;
    /*按照方向移动*/
    switch(dir){
      case N : MOVE_N(cite); break;
      case NE :MOVE_NE(cite);break;
      case E : MOVE_E(cite); break;
      case SE :MOVE_SE(cite); break;
      case S : MOVE_S(cite); break;
      case SW :MOVE_SW(cite); break;
      case W : MOVE_W(cite); break;
      case NW :MOVE_NW(cite);break;
      default : break;	
    }
}
/*
* @function : 返回上一层
*/
int move_back(void *obj)
{
    location buf;
    player *cite = (player *)obj;

    if (IS_EMPTY((*cite).route)){
	return 0;	
    }else{
      	POP((*cite).route,buf,location);
	//POP((*cite).route,buf,location); 	
    }

    cite->site = buf;
    return 1;
}
/*
*@检查各个方向的门是否打开
*/
int  check_door(void *obj)
{ 
    short int vert = ((player*)obj)->site.vert;
    short int horiz = ((player*)obj)->site.horiz;
    char (*map)[MAX_LEN] = ((player*)obj)->map;

   ((player*)obj)->dir[N] = map[vert-1][horiz];
   ((player*)obj)->dir[NE] = map[vert-1][horiz+1];
   ((player*)obj)->dir[E] = map[vert][horiz+1];
   ((player*)obj)->dir[SE] = map[vert+1][horiz+1];
   ((player*)obj)->dir[S] = map[vert+1][horiz];
   ((player*)obj)->dir[SW] = map[vert+1][horiz-1];
   ((player*)obj)->dir[W] = map[vert][horiz-1];
   ((player*)obj)->dir[NW] = map[vert-1][horiz-1]; 
}

int exit_game(void *obj)
{
    int v , h;
    char (*map)[MAX_LEN] = ((player *)obj)->map; 

    for(v = 0; v < MAX_LEN; 
		v++,printf("\n"))

      for(h = 0; h< MAX_LEN; h++)
	 if(map[v][h] == 4){
	   printf("* ");
	 }else if(map[v][h] == 5){
	    printf("O ");
	 }else{
	    printf("  ");	      
	 }
} 

void main()
{
  

    DECLARE_INIT_PLAYER(hunter);
    STACK_CREAT(route,(sizeof(hunter.site)*1000));
	
        char map[MAX_LEN][MAX_LEN] = 
    {/* 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 */
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//0
	2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,//1
	2,0,1,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,2,//2
	2,0,1,1,0,0,1,0,0,0,0,1,0,0,0,1,1,0,0,2,//3
	2,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,2,//4
	2,0,1,0,0,1,0,1,1,1,0,1,0,1,0,0,1,0,0,2,//5
	2,1,1,0,0,1,0,0,1,0,1,0,0,0,1,1,1,0,0,2,//6
	2,0,0,1,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,2,//7
	2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,//8
	2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,//9
	2,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,2,//10
	2,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,0,2,//11
	2,0,0,0,1,0,0,0,0,0,1,1,1,0,0,1,0,0,0,2,//12
	2,0,0,0,0,1,0,0,1,1,0,0,1,0,1,1,0,0,0,0,//13
	2,0,0,0,0,0,1,0,1,0,0,1,0,1,0,1,1,1,0,2,//14
	2,0,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,0,2,//15
	2,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,2,//16
	2,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,2,//17
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,//18
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//19
    };



    hunter.route = route;
    hunter.map = map;

    while(1){
	//hunter.record(&hunter);/*首先记录下当前的位置*/
	hunter.checkdoor(&hunter);/*检查一下哪些门是开着的*/

	int count = 0;
	int ret = 0;

	/*查看门的结果*/
        for(count = 0; count < 8; count++)
	  if (hunter.dir[count] !=0 && hunter.dir[count] != 4 
				&& hunter.dir[count] != 5)
	    if (hunter.dir[count] == 2){
	      printf("here the result : (%d,%d)\n",
	          hunter.site.horiz,hunter.site.vert);
		MARK_OUT(hunter);
		hunter.back(&hunter);
	      goto go_on;
	    }else{
	        ret = hunter.dir[count];
    	    }
          
	if (!ret){
	  /*做路标，然后返回上一层*/
	  hunter.mark(&hunter);
	  if(!hunter.back(&hunter)){
             printf("Finish!\n");
	     goto exit;
          }
	  goto go_on;
        }

	 for(count = 0; count < 8; count++)
	  if (hunter.dir[count] == 1){
	        hunter.nextdir = count;
		hunter.mark(&hunter);
		hunter.forward(&hunter);
		if (!hunter.record(&hunter))
		    goto exit;
		goto go_on;	
	  }
	 
	go_on:
	   continue;
	exit:	
	    hunter.exit(&hunter);
	   break;
    }
	
}
