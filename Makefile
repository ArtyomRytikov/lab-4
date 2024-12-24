CC = gcc

CFLAGS = -Wall -g

LDFLAGS =

SOURCES = main.c queue.c

OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = lab4

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
