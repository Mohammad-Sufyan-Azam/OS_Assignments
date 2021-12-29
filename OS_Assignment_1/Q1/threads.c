// Created by sufyan on 24/10/21.
#include "header2.h"
double result[7];

void* file_read(void* section) {
    int file1;
    char buff[1000];            // For read() system call
    char* memory[30][1000];     // Converting data to 2D string array

    // opening the file
    file1 = open("student_record.csv", O_RDONLY);
    if (file1 == -1) {
        printf("ERROR NUMBER %d\n", errno);
        perror("Program");
        exit(1);
    }
    // reading content of file1
    printf("-------------------------------------------\n");
/*
    printf("File student_record.csv is opened.\n");
    printf("-------------------------------------------\n");
*/
    ssize_t bytes_read = read(file1, buff, 1000);
    if (bytes_read == -1) {
        printf("ERROR: File student_record.csv could not be read.\n");
        exit(1);
    }
    int r = 0, c = 0;
    char *token = strtok(buff, ",");
    bool new_line = false;
    while (token != NULL) {
        for(int i=0; token[i] != '\0'; i++) {
            if (token[i] == '\n') {
                memory[r][c] = token;
                r += 1; c = 0;
                new_line = true;
            }
        }
        if (new_line == false) {
            memory[r][c] = token;
        }
        new_line = false;
        c += 1;
        token = strtok(NULL, ",");
    }
    // Printing average
    double a[6];
    char *endptr, write_data[100];
    int size = 0, j = 0;
    for(int i=0; i<r; i++) {
        if (strcmp(memory[i][1], section) == 0) {
            for(int ptr = 2; ptr <= 7; ptr++)
                a[ptr-2] += strtod(memory[i][ptr], &endptr);
            size++;
        }
    }
    char* sect = (char*)section;
    char assignment_name[] = {'A','s','s','i','g','n','m','e','n','t',' ','0',':',' '};
    printf("No of students in section %s: %d\n", sect, size);
    for(int i = 0; i < 6; i++) {
        char p[9 + 1];
        a[i] = a[i] / size;
        sprintf(p, "%2.6f", a[i]);
        p[9] = '\n';
        char assign = i+1+'0';
        assignment_name[11] = assign;
        for(int k=0; k<14; k++)
            write_data[j++] = assignment_name[k];
        for(int k=0; k<=9; k++)
            write_data[j++] = p[k];
    }
    write(1 , write_data, j);
    
    result[0] = size;
    for(int i=1; i<7; i++)
        result[i] = a[i-1];
    
    // closing the file
    close(file1);
    printf("-------------------------------------------\n");

    return NULL;
}
