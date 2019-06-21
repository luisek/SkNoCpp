#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <thread>

int i = 0;

sem_t empty;
sem_t mutex;
sem_t full;

void producent()
{
    while(1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        ++i;
        std::cout <<"producent: " <<i <<'\n';
        sem_post(&mutex);
        sem_post(&full);
    }
}

void konsument()
{
    while(1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        --i;
        std::cout <<"konsument xxx: " <<i <<'\n';
        sem_post(&mutex);
        sem_post(&empty);
    }
}



int main(int argc, char* argv[])
{
    sem_init(&empty, 0, 20);
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);

    std::thread t1(producent), t2(konsument);

    t1.join();
    t2.join();


    return 0;
}