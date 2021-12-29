                   global B
                   extern C

                   section .bss
convert resb 8

                   section .text

B:
		mov [convert], rdi		; Storing arguement into variable convert
		mov rax, 1			; System call for write
		mov rdi, 1			; First parameter of write with fd 1 for STDOUT
		mov rsi, print			; Second parameter of write with string variable print
		mov rdx, 36			; Third parameter of write with string length 36
		syscall
		mov rax, 1
		mov rdi, 1
		mov rsi, convert		; Printing the converted ascii string
		mov rdx, 8
		syscall
		mov rax, 1
		mov rdi, 1
		mov rsi, linbrk		; Making a line break
		mov rdx, 1
		syscall
		mov r10, $C			; Storing address of C in r12 reg
		mov [rbp+8], r10		; Configuring the stack to return to C
		ret

                   section .data

print           db "In B Lies The Magic (ASCII STRING): " , 0
linbrk          db "", 10
