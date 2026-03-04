CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi


VERT_SOURCES = $(wildcard shaders/*.vert)
FRAG_SOURCES = $(wildcard shaders/*.frag)
VERT_OBJS = $(VERT_SOURCES:.vert=.vert.spv)
FRAG_OBJS = $(FRAG_SOURCES:.frag=.frag.spv)

%.vert.spv: %.vert
	glslc $< -o $@

%.frag.spv: %.frag
	glslc $< -o $@

all: Engine $(VERT_OBJS) $(FRAG_OBJS)

Engine: *.cpp *.hpp
	g++ $(CFLAGS) -o Engine *.cpp $(LDFLAGS)


.PHONY: test clean all

test: Engine
	./Engine

clean:
	rm -f Engine
	rm -f shaders/*.vert.spv