main: helpers.o string_toolkit.o main.o
	gcc helpers.o string_toolkit.o main.o -o main

helpers.o: helpers.c
	gcc -g -Wall -Wshadow -c helpers.c

string_toolkit.o: string_toolkit.c
	gcc -g -Wall -Wshadow -c string_toolkit.c

main.o: main.c
	gcc -g -Wall -Wshadow -c main.c
