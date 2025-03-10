#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Definitions
#define NUM_PHILS 5                 
#define THINKING 1
#define HUNGRY 2
#define EATING 3

pthread_mutex_t mutex;              // Initialize Mutex Lock
pthread_cond_t cond_var[NUM_PHILS]; // Initialize Condition Variable for each Philosopher
int state[NUM_PHILS];               // Initialize States (1-Thinking,2-Hungry,3-Eating) for each Philosopher

int rand_sleep() { // Sleep for 1-3 seconds
    int time = rand()%3 + 1;
    sleep(time);
    return time;
}

void pickup_forks (int philosopher_number) { // Function to invoke eating
    int left_phil = (philosopher_number + NUM_PHILS - 1) % NUM_PHILS;
    int right_phil = (philosopher_number + 1) % NUM_PHILS;
    
    pthread_mutex_lock(&mutex);     // Protect Against Race Conditions
    state[philosopher_number] = HUNGRY;  // Set Philosopher to Hungry

    while(state[left_phil] == EATING || state[right_phil] == EATING)    // Wait for neighbors to finishh eating
        pthread_cond_wait(&cond_var[philosopher_number], &mutex);
    
    state[philosopher_number] = EATING;  // After neighbors finish, philosopher can Eat
    pthread_mutex_unlock(&mutex);   // End Race Condition Protection
}

void return_forks (int philosopher_number) { // Function to finish eating
    int left_phil = (philosopher_number + NUM_PHILS - 1) % NUM_PHILS;
    int right_phil = (philosopher_number + 1) % NUM_PHILS;

    pthread_mutex_lock(&mutex);     // Protect Against Race Conditions
    state[philosopher_number] = THINKING;  // End Eating and Start Thinking (Idle)

    // Signal neighbors if Hungry/Waiting for Forks (end pthread_cond_wait on cond_var)
    pthread_cond_signal(&cond_var[left_phil]);  // Signals left_phil cond_var
    pthread_cond_signal(&cond_var[right_phil]); // Signals right_phil cond_var

    pthread_mutex_unlock(&mutex);   // End Race Condition Protection
}

void *philosopher_thread_func(void *id) {    // pthread loop
    int phil_id = *(int*)id;

    while(1) {
        // Think
        int time = rand_sleep();
        printf("Philosopher #%d took %x000ms thinking\n", phil_id, time);
        
        // Hungry/Eat
        pickup_forks(phil_id);
        printf("Forks are with Philosopher #%d\n", phil_id);
        time = rand_sleep();
        printf("Philosopher #%d took %x000ms eating\n", phil_id, time);

        // Finish
        time = rand_sleep();
        return_forks(phil_id);
    }
}

int main() {
    pthread_t phil_thread[NUM_PHILS];   // Initialize Philosopher respective Threads
    int phil_id[NUM_PHILS];             // Initialize Philosopher List
    srand(time(0));                     // Randomize rand()
    pthread_mutex_init(&mutex, NULL);   // Initialize Mutex Lock
    
    // Create each Philosopher Thread
    for (int i=0; i<NUM_PHILS; i++) {
        pthread_cond_init(&cond_var[i], NULL);  // Initalize Each Condition Variable
        phil_id[i] = i;  // Set Philosopher IDs
        state[i] = 1;   // Set all Philosophers to Think
        pthread_create(&phil_thread[i], NULL, philosopher_thread_func, &phil_id[i]); // Standard pthread
    }

    // Block Main Thread with Philosopher Threads
    for (int i=0; i<NUM_PHILS; i++) 
        pthread_join(phil_thread[i], NULL);
    
    // Potential Clean Up
    pthread_mutex_destroy(&mutex);
    for (int i=0; i<NUM_PHILS; i++) 
        pthread_cond_destroy(&cond_var[i]);
    
    return 0;
}