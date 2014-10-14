#include "graph.h"

int DefaultGetVertex(void *const Graph, void *unuse)
{
    DEBUG_CHECK_ASSERT(!Graph);
    GraphType *LocalGraph = (GraphType *)Graph;
    int count = 0;   

    for (count = 0; count < LocalGraph->NumVertex; count++){
        printf("please input the vertex %d : \n",count);
        scanf("%d",&LocalGraph->Vertexs[count]);
    }
   
}

int DefaultGetArc(void *const Graph, void *unuse)
{
    DEBUG_CHECK_ASSERT(!Graph);
    GraphType *LocalGraph = (GraphType *)Graph;
    
    int cow , rol;
    int weigth;
    int control;
    
    for (cow = 0; cow < LocalGraph->NumVertex; cow++)
        for(rol = 0; rol < LocalGraph->NumVertex; rol++)
		LocalGraph->Arc[cow][rol] = INFINITY;	

    for (control = 0; control < LocalGraph->NumArc; control++){
        printf("please input the (vi,vj) and the weigth of this arc :(deamo : cow,rol,weigth)\n");
	scanf("%d,%d,%d",&cow,&rol,&weigth);
	LocalGraph->Arc[cow][rol] = weigth;	
    }
}

