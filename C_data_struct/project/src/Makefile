vpath %.h /study/code/C_data_struct/project/include
vpath %.c /study/code/C_data_struct/project/src
OBJ=$(TARGET)
CC=gcc
FLAGS= -g  -c 
INCDIR= -I /study/code/C_data_struct/project/include


all: $(OBJ)
	$(CC) $(OBJ) -o $(PRODIR)/$(PRONAME)
$(OBJ):%.o:%.c	
	$(CC) $(FLAGS) $(INCDIR) $<

.PHONY : clean
clean:
	-rm *.o
	-rm *.*~
