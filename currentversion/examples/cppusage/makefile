CCFLAGS = -I./ -g
LFLAGS = -L./
all: maincode.o prologcode.o mypred.o
	g++ $(LFLAGS) -o pltest maincode.o prologcode.o mypred.o -lfrog -lbip

maincode.o: maincode.cpp prologcode.h
	g++ $(CCFLAGS) -c maincode.cpp
prologcode.o: prologcode.cpp
	g++ $(CCFLAGS) -c prologcode.cpp
prologcode.cpp prologcode.h: prologcode.pl
	frogprolog prologcode.pl -c -o prologcode
mypred.o: mypred.cpp mypred.h
	g++ $(CCFLAGS) -c mypred.cpp

clean:
	rm *.o
	rm prologcode.cpp
	rm prologcode.h
