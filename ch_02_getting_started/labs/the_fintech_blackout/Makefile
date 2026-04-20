CXX= = g++
CXXFLAGS = -Wall -std=c++17

app: main.o
	g++ main.o -o app

main.o: main.cpp
	g++ -c main.cpp

run: app
	./app

clean:
	rm -f *.o app