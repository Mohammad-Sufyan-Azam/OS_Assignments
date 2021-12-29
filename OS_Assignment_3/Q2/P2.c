// Created by sufyan on 07/12/21.
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define PORT 8080
//                                      UNIX DOMAIN SOCKETS - RECEIVER

void transfer(int sockfd);

void transfer(int sockfd) {
    int MAX=80, counter = 0, noOfString = 50;
    char buff[MAX];
    while(1) {
        counter++;
        bzero(buff, sizeof(buff));
        if (read(sockfd, buff, sizeof(buff)) != sizeof(buff)) {
            perror("read command: \n");
            exit(-1);
        }

        // Printing server message
        printf("From server: ");
        for(int i=0; i<5; i++)
            printf("%c", buff[i]);

        printf("\t ID: ");
        for(int i=5; i<strlen(buff); i++)
            printf("%c", buff[i]);

        printf("\n");

        if (counter%5 == 0) {

            if (counter < 11) {
                char temp[1];
                temp[0] = buff[5];
                bzero(buff, sizeof(buff));
                buff[0] = temp[0];
            }
            else {
                char temp[2];
                temp[0] = buff[5]; temp[1] = buff[6];
                bzero(buff, sizeof(buff));
                buff[0] = temp[0]; buff[1] = temp[1];
            }

            write(sockfd, buff, sizeof(buff));
        }
        if (counter == noOfString)
            exit(0);
    }
}

int main(int argc, char *argv[]) {
    printf("Client side request initiated...\n");
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed\n");
        return -1;
    }

    transfer(sock);
    return 0;
}

