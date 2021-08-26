./run:main2.o implementation.o
	gcc -o run main2.o implementation.o
main_file.o:main_file.c implementation.h
	gcc -c main2.c
implementation.o:implementation.c implementation.h
	gcc -c implementation.c
