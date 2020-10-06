CC=gcc
LD=gcc
CFLAGS=-c -Wall -O3 -Iinclude

# TODO: Insert your OS-specific libs for GLFW!
ifeq ($(OS),Windows_NT)
	LDFLAGS=-Llib -lglfw3 -ldl -lopengl32 -lgdi32
else
	LDFLAGS=-lglfw -ldl
endif

TARGET=Game-of-Life
OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS)