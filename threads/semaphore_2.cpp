#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std;

mutex m;
int i = 0;
condition_variable cv_empty;
condition_variable full;

void producent()
{
    while(1)
    {
        unique_lock<mutex> loc(m);
        full.wait(loc, []{return i < 20;});
        ++i;
        cout <<"producent " <<i<<endl;
        cv_empty.notify_one();
    }
}

void konsument()
{
    while(1)
    {
        std::unique_lock<mutex> loc(m);
        cv_empty.wait(loc,[]{return i > 0;});
        --i;
        cout <<"kons " <<i <<endl;
        full.notify_one();
    }
}

int main(int argc, char* argv[])
{
    thread t1(konsument), t2(producent);

    t1.join();
    t2.join();

    return 0;
}