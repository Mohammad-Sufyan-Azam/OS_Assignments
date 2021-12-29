#include "header2.h"
#include <pthread.h>
// THREADS USE (PART 2)

int main()
{
    pthread_t thread_id1, thread_id2;
    char* section = "A";
    double avgA[7], avgB[7], avg[6];
    if (pthread_create(&thread_id1, NULL, file_read, section) != 0) {
        printf("ERROR encountered while creating first thread.");
        perror("Program: ");
        exit(1);
    }
    pthread_join(thread_id1, NULL);
    for(int i=0; i<7; i++)
        avgA[i] = result[i];
    section = "B";
    if (pthread_create(&thread_id2, NULL, file_read, section) != 0) {
        printf("ERROR encountered while creating second thread.");
        perror("Program: ");
        exit(1);
    }
    pthread_join(thread_id2, NULL);
    for(int i=0; i<7; i++)
        avgB[i] = result[i];

    // printing average score of each assignment
    char write_data[200];
    char assignment_name[] = {'A','s','s','i','g','n','m','e','n','t',' ','0',':',' '};
    char statement[] = {'A','v','e','r','a','g','e',' ','S','c','o','r','e',' ','O','f',' ','E','a','c','h',' ','A','s','s','i','g','n','m','e','n','t','-','\n'};
    int total = (int)(avgA[0] + avgB[0]), j = 0;
    
    for(int k=0; k<34; k++)
        write_data[j++] = statement[k];
        
    for(int i = 1; i <= 6; i++) {
        char p[9 + 1];
        avg[i - 1] = (avgA[0] * avgA[i] + avgB[0] * avgB[i]) / total;
        sprintf(p, "%2.6f", avg[i - 1]);
        p[9] = '\n';
        
        char assign = i+'0';
        assignment_name[11] = assign;
        for(int k=0; k<14; k++)
            write_data[j++] = assignment_name[k];
            
        for(int k=0; k<=9; k++)
            write_data[j++] = p[k];
    }
    write(1 , write_data, j);
    printf("-------------------------------------------\n");
   exit(0);
}
