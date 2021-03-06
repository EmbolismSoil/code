#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include <pthread.h>
//#include <spinlock.h>

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

#define DECLARE_INIT_PLAYER(name) \
player name = {\
    .site = {.vert = 2, .horiz = 2},\
    .lastdir = 10,\
    .forward = move_forward,\
    .check = check_door,\
    .div = cpoy_division,\
    .next_dir = 10,\
    .lcheck = check_last,\
}
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
typedef int (*lastsite)(void *boj,int dir);
/*分裂并进入各个方向*/
typedef int (*division)(void *boj);

/*
* 玩家进入一个房间后，记录当前位置，查看有几扇门是打开的，
* 记录下来门的信息后施展分身大法，指派各个分身进入各个方向的
* 门内进行重复的动作
*/

typedef struct{
   location site;    /*当前坐标*/
   int lastdir;    /*原来的方向*/
   move forward;     /*前进*/
   probe check;      /*查看门*/
   lastsite lcheck; /*检查上次过来的方向*/
   division div;     /*分身*/
   char (*map)[10];       /*手中的地图*/
   int dir[8];	     /*可以进入的门*/
   int next_dir;     /*下一步的门*/
}player;


/*检查路径*/
int check_last(void *obj, int dir)
{
    int last = ((player *)obj)->lastdir;
    int ret = 0;
    switch (last){
        case N : ret = (dir == S ? 0 : 1); 
		break; 
	case NE : ret = (dir == SW ? 0 :  1); 
		break; 
	case E : ret = (dir == W ? 0 :  1); 
		break; 
	case SE : ret = (dir == NW ? 0 :  1); 
		break; 
	case S  : ret = (dir == N ? 0 :  1); 
		break; 
	case SW : ret = (dir == NE ? 0 :  1); 
		break; 
 	case W : ret = (dir == E ? 0 :  1); 
		break; 
	case NW : ret = (dir == SE ? 0 :  1); 
		break; 
	default: 
		ret =1;
		break; 
    }

	return ret;
}
/*
*@ move_forward : 按照特定的方向前进
*/
int move_forward(void *obj)
{
    player *cite = (player *)obj;
    int dir = cite->next_dir;
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
    }
}
/*
*@检查各个方向的是否打开
*/
int  check_door(void *obj)
{ 
    short int vert = ((player*)obj)->site.vert;
    short int horiz = ((player*)obj)->site.horiz;
    char (*map)[10] = ((player*)obj)->map;

   ((player*)obj)->dir[N] = map[vert-1][horiz];
   ((player*)obj)->dir[NE] = map[vert-1][horiz+1];
   ((player*)obj)->dir[E] = map[vert][horiz+1];
   ((player*)obj)->dir[SE] = map[vert+1][horiz+1];
   ((player*)obj)->dir[S] = map[vert+1][horiz];
   ((player*)obj)->dir[SW] = map[vert+1][horiz-1];
   ((player*)obj)->dir[W] = map[vert][horiz-1];
   ((player*)obj)->dir[NW] = map[vert-1][horiz-1]; 
}
/*
*@分裂：拷贝player对象。然后进入门内。
*然后接着分裂，直到死路或者出口
*/
int cpoy_division(void *obj)
{
   int ret = 0;
   int count = 0;

    player *div_player = (player *)malloc(sizeof(player));
    if(!div_player)
	return 0;

    memset(div_player,0,sizeof(player));
    /*拷贝对象*/
    (*div_player) = (*((player *)obj));
    
    /*进入门内*/
    div_player->forward(div_player);
     printf("(%d,%d)-->", 
	    div_player->site.horiz,div_player->site.vert);	

    div_player->lastdir = div_player->next_dir ;
//    printf("last : %d\n",div_player->lastdir);
    div_player->check(div_player);
    
 //   printf("the door :\n");
  /*副本查看门结果，如果其中有2，则说明任务完成，返回当前副本所在坐标。
   如果全是0，副本自杀，并归还资源。如果有1，则副本继续往下分裂*/
   for ( count = 0; count < 8; count++){
//	printf("%d,  ",div_player->dir[count]);
     if(div_player->dir[count] && div_player->lcheck(div_player,count)){
	ret = div_player->dir[count];
       if(ret == 2){
         printf("here the result is : (%d,%d)\n", 
	    div_player->site.horiz,div_player->site.vert);	 
	 free(div_player);
	 exit(0);
       }
     }
   }
   
   if (!ret){
 //    printf("over here!\n");
 //    printf("here site is : (%d,%d)\n", 
	//    div_player->site.horiz,div_player->site.vert);	 
     free(div_player); 
     return 0;
   }


   for (count = 0; count < 8; count++)
     if (div_player->dir[count] == 1 && 
		div_player->lcheck(div_player,count)){
       div_player->next_dir = count;
//       printf("next : %d\n",div_player->next_dir);
       div_player->div(div_player);
     } 
	return 0;       
}

void main(void)
{
    DECLARE_INIT_PLAYER(hunter);
  /*  char map[20][20] = 
    {
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,2,
	2,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,2,
	2,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,0,2,
	2,0,0,0,1,0,0,0,0,0,1,1,1,0,0,1,0,0,0,2,
	2,0,0,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,
	2,0,0,0,0,0,1,0,1,0,0,1,0,1,0,1,1,1,0,2,
	2,0,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    };*/

     char map[10][10] = 
    {
	2,2,2,2,2,2,2,2,2,2,
	2,0,0,0,0,0,0,0,0,2,
	2,0,1,0,0,0,0,0,0,2,
	2,0,0,1,0,0,0,0,0,2,
	2,0,0,0,1,0,0,0,0,2,
	2,0,0,0,1,0,0,0,0,2,
	2,0,0,1,1,0,0,0,0,2,
	2,1,1,0,0,1,1,0,1,2,
	2,0,0,0,0,0,0,0,0,2,
	2,2,2,2,2,2,2,2,2,2,
    };

    hunter.map = map;
    hunter.div(&hunter);

    exit(0);
}



#ifdef __cplusplus
}
#endif
