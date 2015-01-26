CFLAGS = -lmysqlclient
INCLUDE =
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

TARGET = mysql1

%.o : %.c	
	g++ -o $@ $< -c $(CFLAGS) $(INCLUDE)

$(TARGET): $(OBJS)
	g++ $^ -o $@ $(CFLAGS)
clean:
	rm -rf *.o $(TARGET)
