# Change the following values to suit your system.

CFLAGS=`sdl2-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0 -I `sdl2-config --prefix`/include/
SDL_LIB=`sdl2-config --libs` -lSDL2_image
CCC=g++

OBJECTS = frameGenerator.o gameObject.o rain.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp frameGenerator.h
	$(CCC) $(CFLAGS) -c main.cpp

frameGenerator.o: frameGenerator.cpp frameGenerator.h
	$(CCC) $(CFLAGS) -c frameGenerator.cpp

gameObject.o: gameObject.cpp gameObject.h
	$(CCC) $(CFLAGS) -c gameObject.cpp

rain.o: rain.cpp rain.h gameObject.h
	$(CCC) $(CFLAGS) -c rain.cpp

clean:
	rm -f run *.o
	rm -f *~
	rm -f frames/*.bmp
