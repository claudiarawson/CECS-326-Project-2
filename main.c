#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_PHILS 5                 // # of philosophers
pthread_mutex_t mutex;              // Initialize Mutex Lock
pthread_cond_t cond_var[NUM_PHILS]; // Initialize Condition Variable for each Philosopher
int state[NUM_PHILS];               // Initialize States (1-Thinking,2-Hungry,3-Eating) for each Philosopher

void rand_sleep() { // Sleep for 1-3 seconds
    sleep(rand()%3 + 1);
    return;
}

void test_eat(int philosopher_number) {
    return;

}
void pickup_forks (int philosopher_number) { // Function to invoke eating
    int left_phil = (philosopher_number + NUM_PHILS - 1) % NUM_PHILS;
    int right_phil = (philosopher_number + 1) % NUM_PHILS;
    
    pthread_mutex_lock(&mutex);     // Protect Against Race Conditions
    state[philosopher_number] = 2;  // Set Philosopher to Hungry

    while(state[left_phil] == 3 || state[right_phil] == 3)    // Wait for neighbors to finishh eating
        pthread_cond_wait(&cond_var[philosopher_number], &mutex);
    
    state[philosopher_number] = 3;  // After neighbors finish, philosopher can Eat
    pthread_mutex_unlock(&mutex);   // End Race Condition Protection
}

void return_forks (int philosopher_number) { // Function to finish eating
    int left_phil = (philosopher_number + NUM_PHILS - 1) % NUM_PHILS;
    int right_phil = (philosopher_number + 1) % NUM_PHILS;

    pthread_mutex_lock(&mutex);     // Protect Against Race Conditions
    state[philosopher_number] = 1;  // End Eating and Start Thinking (Idle)

    // Signal neighbors if Hungry/Waiting for Forks (end pthread_cond_wait on cond_var)
    pthread_cond_signal(&cond_var[left_phil]);  // Signals left_phil cond_var
    pthread_cond_signal(&cond_var[right_phil]); // Signals right_phil cond_var

    pthread_mutex_unlock(&mutex);   // End Race Condition Protection
}

void *philosopher_thread(void *id) {    // pthread loop
    int phil_id = *(int*)id;

    // NOT FINISHED
    while(1) {
        printf("bruh");
    }
}

int main() {
    pthread_t phil_thread[NUM_PHILS];   // Initialize Philosopher respective Threads
    int phil_id[NUM_PHILS];             // Philosopher List
    srand(time(0));



    return 0;
}