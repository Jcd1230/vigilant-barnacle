CC = cc
LINKER = -ldl -lpthread `sdl2-config --libs` -lSDL2_image
FLAGS = -Wall -g3 `sdl2-config --cflags` -DDOD_VERSION=\"1\"
TARGET = demo
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

%.o: %.c
	$(CC) -c $(FLAGS) -o $@ $<

clean: clean-obj clean-bin

clean-obj:
	rm -f $(OBJECTS)
	
clean-bin:
	rm -f $(TARGET)
	
$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJECTS) $(LINKER)
