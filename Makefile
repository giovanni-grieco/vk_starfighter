include .env


LIBRARIES=$(TINY_OBJ_LOADER)

CFLAGS_PROD = -std=c++17 -O2 -I$(LIBRARIES)
CFLAGS_DEBUG = -std=c++17 -g -I$(LIBRARIES)
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi


VERT_SOURCES = $(wildcard shaders/*.vert)
FRAG_SOURCES = $(wildcard shaders/*.frag)
VERT_OBJS = $(VERT_SOURCES:.vert=.vert.spv)
FRAG_OBJS = $(FRAG_SOURCES:.frag=.frag.spv)

%.vert.spv: %.vert
	glslc $< -o $@

%.frag.spv: %.frag
	glslc $< -o $@

all_release: Engine_release $(VERT_OBJS) $(FRAG_OBJS)

all_debug: Engine_debug $(VERT_OBJS) $(FRAG_OBJS)


Engine_debug: *.cpp *.hpp
	g++ $(CFLAGS_DEBUG) -o Engine *.cpp $(LDFLAGS)

Engine_release: *.cpp *.hpp
	g++ $(CFLAGS_PROD) -o Engine *.cpp $(LDFLAGS)



.PHONY: test clean all

test: Engine
	./Engine

clean:
	rm -f Engine
	rm -f shaders/*.vert.spv