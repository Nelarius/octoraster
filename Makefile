
CC=g++

# there are for windows compilation
SDL_LINK = C:/dev/SDL2-2.0.3/build
SDL_COMP = C:/dev/SDL2-2.0.3/include

LINKER_INCLUDES = -L $(SDL_LINK)

CFLAGS = -Wall -g -DDEBUG

LDFLAGS =

EXECUTABLE =

ifeq ($(OS),Windows_NT)
	CFLAGS += -I./src -I $(SDL_COMP)
	LDFLAGS += -lmingw32 -lSDL2main -lSDL2 $(LINKER_INCLUDES)
	EXECUTABLE += rasterizer.exe
else
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS +=  -I ./src
        LDFLAGS +=  -lSDL2 
		EXECUTABLE += rasterizer
    endif
endif

OBJ = src/main.o \
	src/rasterizer.o \
	src/renderer.o \

all: $(EXECUTABLE)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECUTABLE): $(OBJ)
	$(CC) -o $(EXECUTABLE) $(OBJ) $(LDFLAGS)


.PHONY: clean

clean:
	rm $(OBJ) $(EXECUTABLE)
