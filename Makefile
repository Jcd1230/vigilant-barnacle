CC = cc
LINKER = -lm
FLAGS = -Wall -O3 -DDEFAULT_MAX="(unsigned long)(1 << 26)"

all: aos soa malloc

aos:
	$(CC) $(FLAGS) -o aos-example src/aos-example.c $(LINKER)

soa:
	$(CC) $(FLAGS) -o soa-example src/soa-example.c $(LINKER)

malloc:
	$(CC) $(FLAGS) -o malloc-example src/malloc-example.c $(LINKER)

clean: clean-obj
	rm aos-example soa-example

clean-obj:
	rm -f $(OBJECTS)
	
