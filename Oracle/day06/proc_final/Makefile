.SUFFIXES: .c .o

CC=gcc
PROC=proc

PROCSRCS=oracle.pc
SRCS=$(PROCSRCS:.pc=.c)
OBJS=$(SRCS:.c=.o)

ORACLE_HOME=/opt/oracle/product/11.2.0
ORAFLAGS1=/usr/include/linux
ORAFLAGS2=/usr/lib/gcc/x86_64-redhat-linux/4.4.4/include/

EXE=abc

all: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) -L$(ORACLE_HOME)/lib -lclntsh

.c.o: $(SRCS)
	$(CC) -Wall -g -o $@ -c $<

$(SRCS):
	$(PROC) INAME=$(PROCSRCS) INCLUDE=$(ORAFLAGS1) INCLUDE=$(ORAFLAGS2) CPOOL=YES MODE=ANSI CODE=ANSI_C PARSE=PARTIAL THREADS=YES ONAME=$(SRCS) 

clean:	
	rm -f $(OBJS)	
	rm -f $(SRCS)	
	rm -f core*
	rm -f $(EXE)
	rm -f oracle.lis
