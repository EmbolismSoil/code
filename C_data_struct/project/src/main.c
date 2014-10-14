#include <stdio.h>
#include "graph.h"

void main(void)
{
   DECLARE_GRAPH(test,10,NULL,NULL);
   test->GetVertex(test,NULL);
   test->GetArc(test,NULL);
}
