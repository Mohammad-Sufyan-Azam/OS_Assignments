#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NO_OF_PHILOSOPHER 5
#define NO_OF_FORK 5

void start_eating(int n, int LEFT, int RIGHT);
void end_eating(int n);
void* process_start(void * phil);

pthread_t philosopher[NO_OF_PHILOSOPHER];
sem_t Fork[NO_OF_FORK];
sem_t count;
sem_t bowls;

void start_eating(int n, int LEFT, int RIGHT) {
    printf("Philosopher %d starts eating using forks %d and %d\n", n, LEFT, RIGHT);
    sleep(1);
}

void end_eating(int n) {
    printf("-------Philosopher %d has finished eating-------\n", n);
}

void* process_start(void * phil) {
    int n=*(int *)phil;		
    int LEFT = n, RIGHT = (n+1) % NO_OF_FORK;

    sem_wait(&count);
    sem_wait(&Fork[LEFT]);
    sem_wait(&Fork[RIGHT]);
    sem_wait(&bowls);

    int no[1];
    sem_getvalue(&bowls, no);
    printf("Philosopher %d takes the sauce bowl number %d\n", n, no[0]);
    start_eating(n, LEFT, RIGHT);
    end_eating(n);

    sem_post(&Fork[LEFT]);
    sem_post(&Fork[RIGHT]);
    sem_post(&bowls);
    sem_post(&count);

    return NULL;
}

int main() {

    for(;;) {

        sem_init(&count, 0, 4);
        sem_init(&bowls, 0, 4);

        int var[5];
        for(int i=0; i<NO_OF_FORK; i++) {
            var[i] = i;
            sem_init(&Fork[i], 0, 1);
        }
        
        for(int i=0; i<NO_OF_PHILOSOPHER; i++)
            pthread_create(&philosopher[i], NULL, process_start, (void *)&var[i]);
              
        for(int i=0; i<NO_OF_PHILOSOPHER; i++)
            pthread_join(philosopher[i], NULL);
        
        sem_destroy(&count);
        sem_destroy(&bowls);

        for(int i=0; i<NO_OF_FORK; i++)
            sem_destroy(&Fork[i]);
    }

    return 0;
}