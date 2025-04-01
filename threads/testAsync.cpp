#include <iostream>
#include "reallyAsync.hpp"

using namespace std;

int main()
{
    auto lb = [](){
        cout <<"START Thread id: " <<std::this_thread::get_id() <<endl;
        for(auto i = 0; i < 10;++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            cout <<"Hello: " <<i  <<" threadid: " <<std::this_thread::get_id() <<endl;
        }
    };
    cout <<"Main thid: " <<std::this_thread::get_id() <<endl;
    auto fut = mpb::reallyAsync(lb);
    auto hgw = async(std::launch::any, lb);

    fut.get();
    hgw.get();

    return 0;

}
