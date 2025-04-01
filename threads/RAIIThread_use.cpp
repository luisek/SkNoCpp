#include "RAIIThread.hpp"
#include <iostream>

using namespace std;

int main()
{
    auto lb = [](){
        cout <<"START Thread id: " <<this_thread::get_id() <<endl;
        for(auto i = 0; i < 10;++i)
        {
            this_thread::sleep_for(chrono::seconds(2));
            cout <<"Hello: " <<i  <<" thread id: " <<this_thread::get_id() <<endl;
        }
    };
    cout <<"Main thid: " <<this_thread::get_id() <<endl;
    mpb::RAIIThread t1(thread(lb), mpb::RAIIThread::DtorAction::JOIN);
    mpb::RAIIThread t2(thread(lb), mpb::RAIIThread::DtorAction::DETACH);

    return 0;

}