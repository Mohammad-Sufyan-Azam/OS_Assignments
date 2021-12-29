// Created by sufyan on 14/12/21.
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void random_string(int len, int no, char **buff);
char* IntToChar(int N);
void transfer(int msgid, char **arr, int noOfString);

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


struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
    char mesg_text2[100];
    char mesg_text3[100];
    char mesg_text4[100];
    char mesg_text5[100];
} message;

void transfer(int msgid, char **arr, int noOfString) {
    int MAX = 100, id = 0, i, counter = 0, strLength = 5;

    while (1) {
        counter++;
        bzero(message.mesg_text, MAX);
        bzero(message.mesg_text2, MAX);
        bzero(message.mesg_text3, MAX);
        bzero(message.mesg_text4, MAX);
        bzero(message.mesg_text5, MAX);
        i = 0;
        for (; i < strLength; i++)
            message.mesg_text[i] = arr[id][i];
        char *no = IntToChar(id);
        for (int m = 0; m < strlen(no); m++, i++)
            message.mesg_text[i] = no[m];
        message.mesg_text[i] = '\0';
        id++;

        i = 0;
        for (; i < strLength; i++)
            message.mesg_text2[i] = arr[id][i];
        no = IntToChar(id);
        for (int m = 0; m < strlen(no); m++, i++)
            message.mesg_text2[i] = no[m];
        message.mesg_text2[i] = '\0';
        id++;

        i = 0;
        for (; i < strLength; i++)
            message.mesg_text3[i] = arr[id][i];
        no = IntToChar(id);
        for (int m = 0; m < strlen(no); m++, i++)
            message.mesg_text3[i] = no[m];
        message.mesg_text3[i] = '\0';
        id++;

        i = 0;
        for (; i < strLength; i++)
            message.mesg_text4[i] = arr[id][i];
        no = IntToChar(id);
        for (int m = 0; m < strlen(no); m++, i++)
            message.mesg_text4[i] = no[m];
        message.mesg_text4[i] = '\0';
        id++;

        i = 0;
        for (; i < strLength; i++)
            message.mesg_text5[i] = arr[id][i];
        no = IntToChar(id);
        for (int m = 0; m < strlen(no); m++, i++)
            message.mesg_text5[i] = no[m];
        message.mesg_text5[i] = '\0';
        id++;

        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);

        /*// display the message
        printf("Data 1 sent: %s\n", message.mesg_text);
        printf("Data 2 sent: %s\n", message.mesg_text2);
        printf("Data 3 sent: %s\n", message.mesg_text3);
        printf("Data 4 sent: %s\n", message.mesg_text4);
        printf("Data 5 sent: %s\n", message.mesg_text5);*/
        // msgrcv to receive message
        if (!msgrcv(msgid, &message, sizeof(message), 1, 0)) {
            perror("msgrcv error");
            exit(1);
        }

        printf("Data from client: %s\n", message.mesg_text);

        if(counter == noOfString/5)
            break;
    }
    msgctl(msgid, IPC_RMID, NULL);
}

int main()
{
    srand(time(0));
    int length = 5, no = 50;

    // Declaring a 2D array from pointers
    char **arr = (char **)malloc(no * sizeof(char*));
    for (int i = 0; i < no; i++)
        arr[i] = (char*)malloc((length * sizeof(char))+1);

    // Initialising 2D array with random characters
    random_string(length, no, arr);

    key_t key;
    int msgid;

    key = ftok("programhuehue", 76);
    if((msgid = msgget(key, 0644|IPC_CREAT)) == -1){
        perror("msgget error client: ");
        exit(1);
    }

    message.mesg_type = 1;
    transfer(msgid, arr, no);

    return 0;
}



