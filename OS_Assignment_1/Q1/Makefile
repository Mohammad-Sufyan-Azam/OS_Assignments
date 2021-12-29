first: main1.o file.o
	gcc main1.o file.o -o output1

main1.o: main1.s
	gcc -c main1.s -o main1.o
	
main1.s: main1.c
	gcc -S main1.c -o main1.s
	
file.o: file.s
	gcc -c file.s -o file.o
	
file.s: file.c header1.h
	gcc -S file.c -o file.s
	
second: main2.o threads.o
	gcc -pthread main2.o threads.o -o output2

main2.o: main2.s
	gcc -c main2.s -o main2.o

main2.s: main2.c
	gcc -S main2.c -o main2.s

threads.o: threads.s
	gcc -c threads.s -o threads.o
	
threads.s: threads.c header2.h
	gcc -S threads.c -o threads.s

clean:
	rm *.o *.s output1 output2

clean1:
	rm *.o *.s output1

clean2:
	rm *.o *.s output2
