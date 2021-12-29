STEPS FOLLOWED ALONG WITH THE IDEOLOGY-

1. Made changes in the kernel/sys.c file and arch/x86/entry/syscalls/syscall_64.tbl file.
2. Wrote the kernel code in the sys.c file. My kernel function took four parameters 
   (float *dest, float *src, int row, int col) and then defined it with SYSCALL_DEFINE4 
   as it had four parameters.
3. In the function i created a pointer whose memory was allocated in the RAM using kmalloc()
   and its total size was the same as the src size.
4. Then I read the src pointer array to the buff pointer array with copy_from_user() with 
   appropriate checks.
5. Finally i wrote the buff pointer array to the dest pointer array with copy_to_user() with 
   appropriate checks.
6. I introduced a buffer array as the copy_from/to_user() used memory from the kernel space 
   in one of the parameters and the other parameter was from user space.
7. Then i wrote the syscall_64.tbl so that it is recognised as a system call when recompiling 
   the kernel.
8. In the table i added it last in the 'common' section so that both 32 and 64 bit architecture 
   could access this function. I wrote the syscall_no, architecture_dependency, function name, 
   and sys_function_name in it.
9. For the test.c file I simply made two 2D arrays one of which was initialised and the 
   other wasn't. Then i called my syscall with its number and parameters using syscall() and 
   finally printed the uninitialised array.