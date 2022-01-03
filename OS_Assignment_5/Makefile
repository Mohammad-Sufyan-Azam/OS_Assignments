all: program_1 program_2 program_3
	gcc -Wall -lpthread -lrt program_1.o -o p1
	gcc -Wall -lpthread -lrt program_2.o -o p2
	gcc -Wall -lpthread -lrt program_3.o -o p3

program_1: program_1.c
	gcc -c program_1.c -o program_1.o

program_2: program_2.c
	gcc -c program_2.c -o program_2.o

program_3: program_3.c
	gcc -c program_3.c -o program_3.o

clean:
	rm *.o p1 p2 p3
