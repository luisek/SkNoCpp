#include "Queue.hpp"
#include <iostream>
#include <thread>

using namespace mpb;

ThreadSafeQueue<int> data_queue;
std::vector<int> data{1,2,3,4,5,6,7,8,9,11,12,14,15,1000};
auto iterBeg = data.begin();

bool is_last(int a)
{
    return 1000 == a;
}

void process(int data)
{
    std::cout <<__PRETTY_FUNCTION__ <<data <<'\n';
}

bool get_data(int& a)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    if(iterBeg != data.end())
    {
        a = *iterBeg;
        ++iterBeg;
    }
}

void data_preparation_thread()
{
    std::cout <<__PRETTY_FUNCTION__ <<'\n';
    int data;
    while(get_data(data))
    {
        std::cout <<"data_queue push: " <<data <<'\n';
        data_queue.push(data);
    }
}

void data_processing_thread()
{
    std::cout <<__PRETTY_FUNCTION__ <<'\n';
    while(true)
    {
        int data;
        data_queue.wait_and_pop(data);
        process(data);
        if(is_last(data))
        {
            std::cout <<"break\n";
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    std::thread processThread(data_processing_thread);
    std::thread dataPreaparationThread(data_preparation_thread);

    processThread.join();
    dataPreaparationThread.join();
    return 0;
}