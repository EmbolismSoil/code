vpath %.h /study/code/C_date_struct/project/include
vpath %.c /study/code/C_date_struct/project/src
vpath %.o /study/code/C_date_struct/project/src


export PRONAME=thread_tree
export PRODIR=$(shell pwd)
INCDIR=/study/code/C_date_struct/project/include
SRCDIR=/study/code/C_date_struct/project/src
PRODIR=$(shell pwd)

SRC=$(filter %.c ,$(shell ls $(SRCDIR)))
OBJS=$(filter %.o,$(subst .c,.o, $(SRC)))
INC=$(shell ls $(INCDIR))
CC=gcc
FLAGS= -g
LDFLAGS = 


all : $(OBJS) 
$(OBJS) : $(SRC) $(INC)
	make -C $(SRCDIR) TARGET="$(OBJS)" 

.PHONY:clean
clean :
	@-rm *.o
	@-rm *.out
	@-rm $(PRONAME)
	-make -C $(SRCDIR) clean 
