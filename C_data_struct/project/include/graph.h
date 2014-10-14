#ifndef __graph_h__
#define __graph_h__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define MaxVertex 	10
#define  INFINITY 65535

#define DECLARE_GRAPH(__name,__arcs,__verfunction,__arcfunction) \
	GraphType *__name = malloc(sizeof(GraphType));\
	__name->NumVertex = MaxVertex;\
	__name->NumArc = __arcs;\
	if (!__verfunction) \
	    __name->GetVertex = DefaultGetVertex;\
	if (!__arcfunction) \
	    __name->GetArc = DefaultGetArc;\
	__name->GetVertex = __verfunction;\
	__name->GetArc = __arcfunction

#define DEBUG_CHECK_ASSERT(__condiction) \
	if ((__condiction)){\
	    printf("error : " #__condiction" is failed!\n");\
	    assert((__condiction));\
	}

typedef int  VertexType[MaxVertex];
typedef int  ArcType[MaxVertex][MaxVertex];
typedef int (*GraphFunction)(void *Arg1, void *Arg2);

typedef struct{
    VertexType  Vertexs;
    ArcType	Arc;
    GraphFunction GetVertex;
    GraphFunction GetArc;
    int NumVertex;
    int NumArc;
}GraphType;

extern DefaultGetVertex(void *const Graph, void *unuse);
extern DefaultGetArc(void *const Graph, void *unuse);

#endif
