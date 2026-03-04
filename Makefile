CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi


vertSources = $(wildcard shaders/*.vert)
fragSources = $(wildcard shaders/*.frag)



Engine: *.cpp *.hpp
	g++ $(CFLAGS) -o Engine *.cpp $(LDFLAGS)

.PHONY: test clean

test: Engine
	./Engine

clean:
	rm -f Engine