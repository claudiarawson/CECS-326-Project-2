#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define num_phils 5                 // # of philosophers
pthread_mutex_t mutex;              // Initialize Mutex Lock
pthread_cond_t cond_var[num_phils]; // Initialize Condition Variable for each Philosopher
int state[num_phils];               // Initialize States (1-Thinking,2-Hungry,3-Eating) for each Philosopher

void rand_sleep() { // Sleep for 1-3 seconds
    sleep(rand()%3 + 1);
    return;
}

int pickup_forks (int philosopher_number) { // Function to invoke eating
    pthread_mutex_lock(&mutex);     // Protect Against Race Conditions
    state[philosopher_number] = 2;  // Set Philosopher to Hungry


    
    pthread_mutex_unlock(&mutex);   // End Race Condition Protection
}

int return_forks (int philosopher_number) { // Function to finish eating
    pthread_mutex_lock(&mutex);     // Protect Against Race Conditions
    state[philosopher_number] = 1;  // End Eating


    pthread_mutex_unlock(&mutex);   // End Race Condition Protection
}

int main() {
    pthread_t phil_thread[num_phils];   // Initialize Philosopher respective Threads
    int phil_id[num_phils];             // Philosopher List
    srand(time(0));

    

    return 0;
}