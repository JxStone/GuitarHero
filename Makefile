all: GuitarHero GStest

GuitarHero: GuitarString.o GuitarHero.o RingBuffer.o
	g++ -o GuitarHero GuitarString.o GuitarHero.o RingBuffer.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lboost_unit_test_framework

GStest: GuitarString.o RingBuffer.o GStest.o
	g++ -o GStest GuitarString.o GStest.o RingBuffer.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lboost_unit_test_framework

GStest.o: GStest.cpp GuitarString.hpp
	g++ -c -g -Wall -ansi -pedantic GStest.cpp

GuitarHero.o: GuitarHero.cpp GuitarString.hpp
	g++ -c -g -Wall -ansi -pedantic GuitarHero.cpp

GuitarString.o: GuitarString.cpp GuitarString.hpp
	g++ -c -g -Wall -ansi -pedantic GuitarString.cpp

RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	g++ -c -g -Wall -ansi -pedantic RingBuffer.cpp

clean:
	rm *.o GuitarHero GStest
