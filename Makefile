# Change the following values to suit your system.

CFLAGS=`sdl2-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0 -I `sdl2-config --prefix`/include/
SDL_LIB=`sdl2-config --libs` -lSDL2_image
CCC=clang++

OBJECTS = frameGenerator.o gameObject.o rain.o building.o detective.o criminal.o \
stageObject.o lightning.o fadeout.o textureManager.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp frameGenerator.h
	$(CCC) $(CFLAGS) -c main.cpp

frameGenerator.o: frameGenerator.cpp frameGenerator.h
	$(CCC) $(CFLAGS) -c frameGenerator.cpp

gameObject.o: gameObject.cpp gameObject.h
	$(CCC) $(CFLAGS) -c gameObject.cpp

textureManager.o: textureManager.cpp textureManager.h
	$(CCC) $(CFLAGS) -c textureManager.cpp

rain.o: rain.cpp rain.h gameObject.h
	$(CCC) $(CFLAGS) -c rain.cpp

building.o: building.cpp building.h gameObject.h
	$(CCC) $(CFLAGS) -c building.cpp
	
detective.o: detective.cpp detective.h gameObject.h
	$(CCC) $(CFLAGS) -c detective.cpp

criminal.o: criminal.cpp criminal.h gameObject.h
	$(CCC) $(CFLAGS) -c criminal.cpp

stageObject.o: stageObject.cpp stageObject.h gameObject.h
	$(CCC) $(CFLAGS) -c stageObject.cpp

lightning.o: lightning.cpp lightning.h
	$(CCC) $(CFLAGS) -c lightning.cpp

fadeout.o: fadeout.cpp fadeout.h
	$(CCC) $(CFLAGS) -c fadeout.cpp

clean:
	rm -f run *.o
	rm -f *~
	rm -f frames/*.bmp
