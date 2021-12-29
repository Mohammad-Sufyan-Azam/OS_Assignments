
all: main.c B.o C.c
	gcc -no-pie main.c B.o C.c -o output

B.o: B.asm
	nasm -f elf64 B.asm

clean:
	rm *.o output
