// Created by sufyan on 14/12/21.
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <string.h>

void transfer(int msgid);

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
    char mesg_text2[100];
    char mesg_text3[100];
    char mesg_text4[100];
    char mesg_text5[100];
} message;

void transfer(int msgid) {
    int MAX = 100, id = 0, counter = 0, noOfString = 50;
    bool first = true;

    while(1) {
        counter++;
        bzero(message.mesg_text, sizeof(message.mesg_text));

        // msgrcv to receive message
        if (!msgrcv(msgid, &message, sizeof(message), 1, 0)) {
            perror("msgrcv error: ");
            exit(1);
        }

        // display the message
        printf("Server data: ");
        for (int i = 0; i < 5; i++)
            printf("%c", message.mesg_text[i]);
        printf("\tID: ");
        for(int i=5; i<strlen(message.mesg_text); i++)
            printf("%c", message.mesg_text[i]);
        printf("\n");

        // display the message
        printf("Server data: ");
        for (int i = 0; i < 5; i++)
            printf("%c", message.mesg_text2[i]);
        printf("\tID: ");
        for(int i=5; i<strlen(message.mesg_text2); i++)
            printf("%c", message.mesg_text2[i]);
        printf("\n");

        // display the message
        printf("Server data: ");
        for (int i = 0; i < 5; i++)
            printf("%c", message.mesg_text3[i]);
        printf("\tID: ");
        for(int i=5; i<strlen(message.mesg_text3); i++)
            printf("%c", message.mesg_text3[i]);
        printf("\n");

        // display the message
        printf("Server data: ");
        for (int i = 0; i < 5; i++)
            printf("%c", message.mesg_text4[i]);
        printf("\tID: ");
        for(int i=5; i<strlen(message.mesg_text4); i++)
            printf("%c", message.mesg_text4[i]);
        printf("\n");

        // display the message
        printf("Server data: ");
        for (int i = 0; i < 5; i++)
            printf("%c", message.mesg_text5[i]);
        printf("\tID: ");
        for(int i=5; i<strlen(message.mesg_text5); i++)
            printf("%c", message.mesg_text5[i]);
        printf("\n");

        bzero(message.mesg_text, sizeof(message.mesg_text));
        message.mesg_text[0] = message.mesg_text5[5];
        message.mesg_text[1] = message.mesg_text5[6];

        msgsnd(msgid, &message, sizeof(message), 0);
        //printf("Data sent: %s\n", message.mesg_text);

        first = false;
        if (counter == noOfString/5)
            break;
    }
}

int main()
{
    key_t key;
    int msgid;

    key = ftok("programhuehue", 76);
    if((msgid = msgget(key, 0644|IPC_CREAT)) == -1){
        perror("server error ");
        exit(1);
    }

    message.mesg_type = 1;
    transfer(msgid);

    return 0;
}




