// Created by sufyan on 22/10/21.
#include <sys/wait.h>
#include <pthread.h>
#include "header1.h"
// Q1 PART 1
int main(int argc, char* argv[]) {
    pid_t p;
    int status;
    p = fork();
    
    if (p == 0) {
        // Child process
        file_read("A");
        exit(0);
    } 
    else if (p == -1) {
        // Error handling
        printf("ERROR NUMBER: %d\n", errno);
        perror("Program: ");
        exit(1);
    } 
    else {
        // Parent process
        waitpid(p, &status, 0);
        file_read("B");
    }
}
