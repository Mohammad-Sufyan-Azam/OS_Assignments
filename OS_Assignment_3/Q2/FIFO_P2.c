// Created by sufyan on 13/12/21.
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void transfer(char *myfifo) {

    int fd, counter = 0, noOfString = 50;
    char buffer[30];

    while (1) {
        counter++;
        fd = open(myfifo, O_RDONLY);
        if (fd < 0) {
            perror("Error in opening FIFO\n");
            exit(EXIT_FAILURE);
        }

        if (read(fd,buffer,30) < 0) {
            perror("Error in reading from FIFO\n");
            exit(EXIT_FAILURE);
        }

        char id[2];
        for(int i = 0; i<=29; i++) {
            if(i%6 == 5) {
                printf("\n");
                continue;
            }
            if(i%6 == 0) {
                printf("ID: %d\t Server data: ",buffer[i+5] - 32);
                id[0] = buffer[i+5];
            }
            printf("%c",buffer[i]);
        }

        close(fd);

        // WRITING
        fd = open(myfifo, O_WRONLY);
        if (fd < 0) {
            perror("Error in opening FIFO\n");
            exit(EXIT_FAILURE);
        }
        if (write(fd,id,2) < 0) {
            perror("Error in writing to FIFO\n");
            exit(EXIT_FAILURE);
        }

        close(fd);

        if (counter == noOfString/5)
            exit(0);
    }
}

int main(int argc, char const *argv[]) {
    transfer("myfifo");
    return 0;
}
