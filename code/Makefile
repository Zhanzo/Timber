LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: Timber

Timber.o: Timber.cpp
	g++ -std=c++11 -c Timber.cpp -o Timber.o

Timber: Timber.o
	g++ -o Timber Timber.o $(LIBS)

run:
	./Timber

clean:
	@echo "Removing files"
	rm -rf Timber *.o
