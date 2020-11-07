sources=liste.cpp Erreurs.cpp TestFinal.cpp
entete=liste.h Erreurs.h
objets=$(sources:.cpp=.o)

CC=g++
CXXFLAGS=-Wall -g

TestFinal: TestFinal.o Erreurs.o

TestFinal.o: liste.o

liste.o: liste.cpp liste.h Erreurs.o

Erreurs.o: Erreurs.cpp Erreurs.h

clean:
	rm -rf *.o