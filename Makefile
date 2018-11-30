CC = cc
LINKER = -lm
FLAGS = -Wall -DDEFAULT_MAX="(unsigned long)(1 << 24)"

all: aos soa

aos:
	$(CC) $(FLAGS) -o aos-example src/aos-example.c $(LINKER)

soa:
	$(CC) $(FLAGS) -o soa-example src/soa-example.c $(LINKER)

clean: clean-obj
	rm aos-example soa-example

clean-obj:
	rm -f $(OBJECTS)
	
