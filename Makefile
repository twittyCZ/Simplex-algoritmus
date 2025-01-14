CC=gcc
CFLAGS=-Wall -Wextra -pedantic
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
TARGET=lp.exe

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)