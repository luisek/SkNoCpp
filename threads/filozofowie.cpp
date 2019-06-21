#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


std::mutex data[5];

class philosopher
{
    void think()
    {

    }

    void eat()
    {

    }

    void take_fork()
    {
        
    }

    void put_fork()
    {

    }

public:
    philosopher(int _id) : philosopherId{_id}
    {}
    void dine()
    {
        think();
        take_fork();
        eat();
        put_fork();
    }
    int philosopherId;
};