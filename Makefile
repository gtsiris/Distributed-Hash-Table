objects=Exercise_11.o DHTImplementation.o
Exercise_11 : $(objects)
	gcc $(objects) -o Exercise_11
Exercise_11.o :Exercise_11.c DHTInterface.h DHTTypes.h
	gcc -c Exercise_11.c
DHTImplementation.o :DHTImplementation.c DHTInterface.h DHTTypes.h
	gcc -c DHTImplementation.c
clean:
	rm Exercise_11 $(objects)
