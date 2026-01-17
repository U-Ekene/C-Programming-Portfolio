restaurant_demo: main.o menu.o restaurant.o
	gcc main.o menu.o restaurant.o -o restaurant_demo

main.o: main.c menu.h restaurant.h
	gcc -g -Wall -Wshadow -c main.c

menu.o: menu.c menu.h
	gcc -g -Wall -Wshadow -c menu.c

restaurant.o: restaurant.c restaurant.h menu.h
	gcc -g -Wall -Wshadow -c restaurant.c
