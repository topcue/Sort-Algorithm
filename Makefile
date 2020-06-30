CC=gcc
CFLAGS=-g -Wall
TARGET=Sort-Algorithm
OBJS=Sort-Algorithm.o
 
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
	rm $(OBJS)

clean:
	rm $(OBJECT) $(TARGET)

