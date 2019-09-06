a.out : main.o IntVector.o 
	g++ main.o IntVector.o

main.o : main.cpp IntVector.h
	g++ -c main.cpp

IntVector.o : IntVector.cpp IntVector.h
	g++ -c IntVector.cpp

clean :
	rm *.o a.out