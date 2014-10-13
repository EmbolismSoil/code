#include <stdio.h>

void main()
{
   char darray[3][3] = {1,2,3,
			4,5,6,
			7,8,9};
   char (*p)[3];
   p = darray;
  
   printf("%d",p[1][1]);
}
