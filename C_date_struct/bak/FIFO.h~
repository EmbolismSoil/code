#ifndef FIFO_H
#define FIFO_H

/*
*@we need the void pointer to build a genernal FIFO 
*needn't care the type of date
*/
typedef struct{
    void *fifo_base;
    void *fifo_top;
    void *tp;
    void *bp;
    int size;
}FIFO;

/*
*@define the operation of the FIFO queue
*/
#define DECLARE_FIFO(name,fsize) \
FIFO name = {\
  .fifo_base = malloc(fsize),\
  .fifo_top = name.fifo_base + fsize,\
  .tp = name.fifo_base,\
  .bp = name.fifo_base,\
  .size = fsize, \
}

#define PUSH(fifo_name, date) push(&fifo_name, &date, sizeof(date))
#define POP(fifo_name, date) pop(&fifo_name, &date, sizeof(date))
#define PUSH_BUF(fifo_name, buf) pop(&fifo_name, buf, sizeof(buf))

#define ARRAY_NUM(array) (sizeof(array)/sizeof(array[0]))

#define INIT_ARRAY(array) do{\
    for ( array[0] =  (ARRAY_NUM(array) - 1); array[0] > 0; array[0]--) \
	array[array[0]] = array[0]; \
}while(0)

#define PRINT_ARRAY(array) do{\
    printf("the array is :\n");\
    printf("%d  ",array[0]);\
    for (array[0] = 1; array[0] < \
    	ARRAY_NUM(array); array[0]++) \
      printf("%d  ",array[array[0]]);\
    printf("\n\n");\
}while(0)

extern int push(FIFO  *const fp,void *const date,int len);
extern int pop(FIFO *const fp, void *date, int len);


#endif
