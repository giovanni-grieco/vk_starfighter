CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

Engine: *.cpp *.hpp
	g++ $(CFLAGS) -o Engine *.cpp $(LDFLAGS)

.PHONY: test clean

test: Engine
	./Engine

clean:
	rm -f Engine