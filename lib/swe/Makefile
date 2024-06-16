CFLAGS = -g -Wall -fPIC
OP = $(CFLAGS)  
CC = cc

.c.o:
	$(CC) -c $(OP) $<

swecl.o: swejpl.h sweodef.h swephexp.h swedll.h sweph.h swephlib.h
sweclips.o: sweodef.h swephexp.h swedll.h
swedate.o: swephexp.h sweodef.h swedll.h
swehel.o: swephexp.h sweodef.h swedll.h
swehouse.o: swephexp.h sweodef.h swedll.h swephlib.h swehouse.h
swejpl.o: swephexp.h sweodef.h swedll.h sweph.h swejpl.h
swemini.o: swephexp.h sweodef.h swedll.h
swemmoon.o: swephexp.h sweodef.h swedll.h sweph.h swephlib.h
swemplan.o: swephexp.h sweodef.h swedll.h sweph.h swephlib.h swemptab.h
sweph.o: swejpl.h sweodef.h swephexp.h swedll.h sweph.h swephlib.h
swephlib.o: swephexp.h sweodef.h swedll.h sweph.h swephlib.h
swetest.o: swephexp.h sweodef.h swedll.h
swevents.o: swephexp.h sweodef.h swedll.h

OBJECTS = sweph.o swephlib.o swejpl.o swedate.o swemmoon.o swemplan.o swehouse.o swecl.o swehel.o

all: $(OBJECTS)

main: main.o $(OBJECTS)
	g++ $(OP) -o main main.o $(OBJECTS) -lm -ldl

clean:
	rm -f $(OBJECTS)

