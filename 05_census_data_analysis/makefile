main: census_functions.o main.o
	gcc census_functions.o main.o -o main

census_functions.o: census_functions.c
	gcc -g -Wall -Wshadow -c census_functions.c

main.o: main.c
	gcc -g -Wall -Wshadow -c main.c
