.SUFFIXES: .c .o
CC=gcc
PROC=proc

PROCSRCS=oracle.pc
DBSRCS=$(PROCSRCS:.pc=.c)

SRCS=main.c\
	$(DBSRCS)
	
OBJS=$(SRCS:.c=.o)

ORACLE_HOME=/opt/oracle/product/11.2.0
ORAFLAGS1=/usr/include/linux
ORAFLAGS2=/usr/lib/gcc/x86_64-redhat-linux/4.4.4/include/

EXEC=myoracle

all: $(OBJS)	
	$(CC) -L${ORACLE_HOME}/lib -lclntsh -o $(EXEC) $(OBJS) 	
	@echo '^_^ ^_^ ^_^ ^_^ ^_^ ^_^ OK ^_^ ^_^ ^_^ ^_^ ^_^ ^_^'

.c.o: $(DBSRCS)	
	$(CC) -Wall -g -o $@ -c $<

$(DBSRCS):	
	$(PROC) INAME=$(PROCSRCS) INCLUDE=$(ORAFLAGS1) INCLUDE=$(ORAFLAGS2) CPOOL=YES MODE=ANSI CODE=ANSI_C PARSE=PARTIAL THREADS=YES ONAME=$(DBSRCS)

clean:
	rm -f $(OBJS)	
	rm -f $(DBSRCS)
	rm -f $(EXEC)
