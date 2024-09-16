all: compile link

compile:
	g++ -Isrc/include -c coding/*.cpp

link:
	g++ *.o -o main $(shell pkg-config --libs --cflags sfml-graphics sfml-window sfml-system sfml-audio) -lGL


clean:
	rm -f *.o main