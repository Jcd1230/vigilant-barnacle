CC = cc
LINKER = -lm
FLAGS = -Wall -g3
TARGET = aos-example
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

all: aos soa

aos:
	$(CC) $(FLAGS) -o aos-example src/aos-example.c $(LINKER)

soa:
	$(CC) $(FLAGS) -o soa-example src/soa-example.c $(LINKER)

%.o: %.c
	$(CC) -c $(FLAGS) -o $@ $<

clean: clean-obj clean-bin

clean-obj:
	rm -f $(OBJECTS)
	
clean-bin:
	rm -f $(TARGET)
	
