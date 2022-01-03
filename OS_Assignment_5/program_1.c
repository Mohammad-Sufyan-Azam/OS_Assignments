#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NO_OF_PHILOSOPHER 5
#define NO_OF_FORK 5

void start_eating(int n, int LEFT, int RIGHT);
void end_eating(int n);
void* process_start(void * phil);

pthread_t philosopher[NO_OF_PHILOSOPHER];
sem_t Fork[NO_OF_FORK];

void start_eating(int n, int LEFT, int RIGHT) {
    printf("Philosopher %d starts eating using forks %d and %d\n", n, LEFT, RIGHT);
    sleep(1);
}

void end_eating(int n) {
    printf("-------Philosopher %d has finished eating-------\n", n);
}

void* process_start(void* phil) {
    int n=*(int *)phil;		
    int LEFT = n, RIGHT = (n+1) % NO_OF_FORK;

    if (n != 4) {
        sem_wait(&Fork[LEFT]);
        sem_wait(&Fork[RIGHT]);
    }
    else {
        sem_wait(&Fork[RIGHT]);
        sem_wait(&Fork[LEFT]);
    }

    start_eating(n, LEFT, RIGHT);
    end_eating(n);

    if (n != 4) {
        sem_post(&Fork[LEFT]);
        sem_post(&Fork[RIGHT]);
    }
    else {
        sem_post(&Fork[RIGHT]);
        sem_post(&Fork[LEFT]);
    }

    return NULL;
}

int main() {

    for(;;) {

        int var[5];
        for(int i=0; i<NO_OF_FORK; i++) {
            var[i] = i;
            sem_init(&Fork[i], 0, 1);
        }
        
        for(int i=0; i<NO_OF_PHILOSOPHER; i++)
            pthread_create(&philosopher[i], NULL, process_start, (void *)&var[i]);
        
        for(int i=0; i<NO_OF_PHILOSOPHER; i++) {
            pthread_join(philosopher[i], NULL);
        }

        for(int i=0; i<NO_OF_FORK; i++)
            sem_destroy(&Fork[i]);
    }

    return 0;
}