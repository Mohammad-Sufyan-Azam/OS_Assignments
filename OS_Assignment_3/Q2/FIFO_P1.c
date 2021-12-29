// Created by sufyan on 13/12/21.
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void random_string(int len, int no, char **buff);
char* IntToChar(int N);
void transfer(char *myfifo, char **arr, int noOfString, int strLength);

void random_string(int len, int no, char **buff) {
    char *temp = "~`|!@#$%^&*()-_=+[]';./,<>?:{}abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    char *randomString = NULL;

    if (len) {
        randomString = malloc(sizeof(char) * (len +1));
        if (randomString) {
            for(int i=0; i<no; i++) {
                for (int j = 0; j < len; j++) {
                    int key = rand() % (int)(strlen(temp) -1);
                    randomString[j] = temp[key];
                    *(*(buff+i)+j) = *(temp+key);
                }
                randomString[len] = '\0';
            }
        }
    }
}

char* IntToChar(int N)
{
    if (N==0)
        return "0";
    int m = N;
    int digit = 0;
    while (m) {
        digit++;
        m /= 10;
    }
    char* arr;
    char arr1[digit];
    arr = (char*)malloc(digit);
    int index = 0;
    while (N) {
        arr1[++index] = N%10 + '0';
        N /= 10;
    }
    int i;
    for (i = 0; i < index; i++) {
        arr[i] = arr1[index - i];
    }
    arr[i] = '\0';

    return (char*)arr;
}

void transfer(char myfifo[], char **arr, int noOfString, int strLength) {

    int string_id = 0, r = 0, fd, c, counter = 0;
    char buff[30] = {0};
    while(1) {
        counter++;
        // WRITING
        fd = open(myfifo, O_WRONLY);
        if (fd < 0) {
            perror("Error in opening FIFO\n");
            exit(EXIT_FAILURE);
        }
        bzero(buff, 30);
        c=0;
        for(int i=0; i<=29; i++) {
            if(c == 5) {
                buff[i] = r + 32;
                c = 0; r++;
                continue;
            }
            buff[i] = arr[r][c];
            c++;
        }

        if (write(fd,buff,sizeof(buff)) < 0) {
            perror("Error in writing to FIFO\n");
            exit(EXIT_FAILURE);
        }
        close(fd);

        // READING
        fd = open(myfifo, O_RDONLY);
        if (fd < 0) {
            perror("Error in opening FIFO\n");
            exit(EXIT_FAILURE);
        }
        char recieved_id[100];
        if (read(fd,recieved_id,2) < 0) {
            perror("Error in reading from FIFO\n");
            exit(EXIT_FAILURE);
        }
        close(fd);

        int id = (int)(recieved_id[0]);
        string_id = id - 32;
        printf("Client data: %d\n",string_id);

        if (counter == noOfString/5)
            break;
    }
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    int length = 5, no = 50;

    // Declaring a 2D array from pointers
    char **arr = (char **) malloc(no * sizeof(char *));
    for (int i = 0; i < no; i++)
        arr[i] = (char *) malloc(length * sizeof(char));

    // Initialising the 2D array
    random_string(length, no, arr);

    char filename[] = "myfifo";
    remove(filename);

    if (mkfifo(filename, 0777) < 0) {
        perror("Error in creating FIFO\n");
        exit(EXIT_FAILURE);
    }

    transfer(filename, arr, no, length);

    return 0;
}
