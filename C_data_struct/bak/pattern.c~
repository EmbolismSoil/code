#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
typedef struct{
    char *str;
    int *filure;
}pattern;

#define CHANGE_MARCO

#define DECLARE_PATTERN(pat_name,patstr) \
	pattern pat_name = {\
        .str = patstr, \
	.filure = malloc(sizeof(int)*strlen(patstr)),}
/*
*@function : print the filure of the pattern
*'pat' is the pointer of this pattern
*/ 
#ifdef CHANGE_MARCO
#define pint_filure(pat) do{\
    printf("the filure array is :\n");\
    printf("%d\n",(pat)->filure[0]);\
    for ((pat)->filure[0] = 1; (pat)->filure[0] < \
    	strlen((pat)->str); (pat)->filure[0]++) \
      printf("%d\n",(pat)->filure[(pat)->filure[0]]);\
}while(0)
#else
void pint_filure(pattern *pat)
{
    int count;
    int size;
    size = strlen(pat->str);
    for (count = 0;count < size; count++)
       printf("the filure array is :%d \n",pat->filure[count]);
}
#endif

/*
*@function : compute the fail function of the pattern
*/
void fail(pattern *pat)
{
    int i = 0,j = 0;
    int len = strlen(pat->str);
#ifdef CHANGE_FAILE
   
    for (j = 1; j < len; j++){
      if (pat->str[i] == pat->str[j]){
          pat->filure[j] = pat->filure[j-1]+1;
	  i++;
      }else{
          pat->filure[j] = -1;
	  i = 0;
      }
    }
#else
    pat->filure[0] = -1;
    for (j = 1; j < len; j++){
      i = pat->filure[j-1];
      while((pat->str[j] != pat->str[i+1]) && (i >= 0))
        i = pat->filure[i];
	if(pat->str[j]  == pat->str[i+1])
	  pat->filure[j] = i + 1;
	else pat->filure[j] = -1;
    } 
#endif
}

void main()
{
    clock_t start,stop;
    start = clock();
    DECLARE_PATTERN(pat,"hello world");
    fail(&pat);
    pint_filure(&pat);
    stop = clock();
    printf("%f\n",((double)(stop - start)));
}
#ifdef __cplusplus
}
#endif
