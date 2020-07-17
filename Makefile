avl: main.o avl.o
	g++ -std=c++11 main.o avl.o -o avl
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
avl.o: avl.h avl.cpp
	g++ -std=c++11 -c avl.cpp
clean:
	rm *.o avl
