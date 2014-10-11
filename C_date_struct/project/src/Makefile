vpath %.h /study/code/C_date_struct/project/include
vpath %.c /study/code/C_date_struct/project/src
OBJ=$(TARGET)
INCDIR=/study/code/C_date_struct/project/include
FLAGS= -c -g -I
CC=gcc

.PHONY : all
all: $(OBJ)
	$(CC) $(OBJ) -o $(PRODIR)/$(PRONAME)
$(OBJ):%.o:%.c
	$(CC) $(FLAGS) $(INCDIR)  $< 

.PHONY : clean
clean:
	-rm *.o
	-rm *.c~
