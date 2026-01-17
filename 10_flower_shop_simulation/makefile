prog: main.o flower_functions.o
	gcc main.o flower_functions.o -o prog

main.o: main.c linkedlist.h flower.h
	gcc -g -Wall -Wshadow -c main.c

flower_functions.o: flower_functions.c linkedlist.h flower.h
	gcc -g -Wall -Wshadow -c flower_functions.c
