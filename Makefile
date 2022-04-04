CC = g++
OBJECTS = objects

all: clean magazijnLading.o magazijnHerindeler.o kraan.o magazijnRegels.o move
	$(CC) -o program magazijn.cpp $(OBJECTS)/magazijnLading.o $(OBJECTS)/magazijnHerindeler.o $(OBJECTS)/kraan.o $(OBJECTS)/magazijnRegels.o

clean:
	rm -rf $(OBJECTS)
	mkdir $(OBJECTS)

move:
	mv *.o $(OBJECTS)

magazijnLading.o:
	$(CC) -c magazijnLading.cpp

magazijnHerindeler.o:
	$(CC) -c magazijnHerindeler.cpp

kraan.o:
	$(CC) -c kraan.cpp

magazijnRegels.o:
	$(CC) -c magazijnRegels.cpp