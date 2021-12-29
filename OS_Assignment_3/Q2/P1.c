// Created by sufyan on 07/12/21.
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#define PORT 8080
//                                      UNIX DOMAIN SOCKETS - SENDER

void random_string(int len, int no, char **buff);
char* IntToChar(int N);
void transfer(int sockfd, char **arr, int noOfString, int strLength);

void random_string(int len, int no, char **buff) {
    char *temp = "~`|!@#$%^&*()-_=+[]';./,<>?:{}abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    if (len) {
        for(int i=0; i<no; i++) {
            for (int j = 0; j < len; j++) {
                int key = rand() % (int)(strlen(temp) -1);
                *(*(buff+i)+j) = *(temp+key);
            }
            *(*(buff+i)+len) = '\0';
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

void transfer(int sockfd, char **arr, int noOfString, int strLength) {
    int MAX = 80, id = 0, i, counter = 0;
    char buff[MAX];

    while(1) {
        counter++;
        bzero(buff, MAX);
        i = 0;
        for(; i<strLength; i++)
            buff[i] = arr[id][i];

        char *no = IntToChar(id);
        for(int m=0; m<strlen(no); m++, i++)
            buff[i] = no[m];
        buff[i] = '\0';

        write(sockfd, buff, sizeof(buff));

        if (counter%5 == 0) {
            bzero(buff, MAX);
            read(sockfd, buff, sizeof(buff));
            printf("From client: %s\n", buff);
        }

        id++;
        if (counter == noOfString) {
            break;
        }
    }
}

int main(int argc, char *argv[]) {

    srand(time(0));
    int length = 5, no = 50;

    // Declaring a 2D array from pointers
    char **arr = (char **)malloc(no * sizeof(char*));
    for (int i = 0; i < no; i++)
        arr[i] = (char*)malloc((length * sizeof(char))+1);

    // Initialising 2D array with random characters
    random_string(length, no, arr);

    // Generationg output of array
    // for(int i=0; i<no; i++)
    //     printf("%s\n", arr[i]);

    printf("Server side request initiated...\n");
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    transfer(new_socket, arr, no, length);
    close(new_socket);
    return 0;
}

/*
P1 sends a group of five consecutive elements of the array of strings to P2 along with the ID’s of
the strings, where ID is the index of the array corresponding to the string.

P2 needs to accept the received strings, and send back the highest ID received to P1 to acknowledge the strings received.
P2 then simply prints the ID’s and the strings on the console.

On receiving the acknowledged packet, P1 sends the next five strings, with the string elements
starting from the successor of the acknowledged ID.
*/
