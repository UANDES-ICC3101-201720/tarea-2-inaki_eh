CC=gcc
FLAGS=-std=gnu11 -Wall -Werror
ejecutable=virtmem

virtmem: main.o page_table.o disk.o program.o
	$(CC) $(FLAGS) -o $(ejecutable) main.o page_table.o disk.o program.o -o virtmem

main.o: main.c
	$(CC) $(FLAGS) -c main.c -o main.o

page_table.o: page_table.c
	$(CC) $(FLAGS) -c page_table.c -o page_table.o

disk.o: disk.c
	$(CC) $(FLAGS) -c disk.c -o disk.o

program.o: program.c
	$(CC) $(FLAGS) -c program.c -o program.o


clean:
	rm *.o
	rm $(ejecutable)
