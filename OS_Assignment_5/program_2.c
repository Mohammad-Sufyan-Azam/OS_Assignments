#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NO_OF_PHILOSOPHER 5
#define NO_OF_FORK 5
#define NO_OF_BOWL 4

void start_eating(int n, int LEFT, int RIGHT);
void end_eating(int n);
void* process_start(void * phil);

pthread_t philosopher[NO_OF_PHILOSOPHER];
sem_t Fork[NO_OF_FORK];
sem_t Bowl[NO_OF_BOWL];

void start_eating(int n, int LEFT, int SAUCE_BOWL) {
    printf("Philosopher %d starts eating using fork %d and sauce bowl %d\n", n, LEFT, SAUCE_BOWL);
    sleep(1);
}

void end_eating(int n) {
    printf("-------Philosopher %d has finished eating-------\n", n);
}

void* process_start(void* phil) {
    int n = *(int *)phil;		
    int LEFT = n, SAUCE_BOWL = n % NO_OF_BOWL;

    sem_wait(&Fork[LEFT]);
    sem_wait(&Bowl[SAUCE_BOWL]);

    start_eating(n, LEFT, SAUCE_BOWL);
    end_eating(n);

    sem_post(&Fork[LEFT]);
    sem_post(&Bowl[SAUCE_BOWL]);

    return NULL;
}

int main() {

    for(;;) {

        int var[5];
        for(int i=0; i<NO_OF_FORK; i++) {
            var[i] = i;
            sem_init(&Fork[i], 0, 1);
        }

        for(int i=0; i<NO_OF_BOWL; i++) {
            sem_init(&Bowl[i], 0, 1);
        }
        
        for(int i=0; i<NO_OF_PHILOSOPHER; i++)
            pthread_create(&philosopher[i], NULL, process_start, (void *)&var[i]);
        
        for(int i=0; i<NO_OF_PHILOSOPHER; i++) {
            pthread_join(philosopher[i], NULL);
        }

        for(int i=0; i<NO_OF_FORK; i++)
            sem_destroy(&Fork[i]);

        for(int i=0; i<NO_OF_BOWL; i++)
            sem_destroy(&Bowl[i]);
    }

    return 0;
}