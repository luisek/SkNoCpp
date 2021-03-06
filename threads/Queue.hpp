#pragma once
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <iostream>

namespace mpb
{
    template <typename T>
    class ThreadSafeQueue
    {
    public:
        ThreadSafeQueue()
        {}
        ThreadSafeQueue(const ThreadSafeQueue& other)
        {
            std::lock_guard<std::mutex> lk(mut);
            data_queue = other.data_queue;
        }

        void push(T new_value)
        {
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(new_value);
            std::cout <<__PRETTY_FUNCTION__ <<'\n';
            data_condition.notify_one();
        }

        void wait_and_pop(T& value)
        {
            std::unique_lock<std::mutex> lk(mut);
            data_condition.wait(lk, [this]{return !data_queue.empty();});
            value = data_queue.front();
            data_queue.pop();
        }

        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_lock<std::mutex> lk(mut);
            data_condition.wait(lk,[this]{return !data_queue.empty();});
            auto ret = std::make_shared<T>(data_queue.front());
            data_queue.pop();
            return ret;  //move
        }

        bool try_pop(T& value)
        {
            std::lock_guard<std::mutex> lk(mut);
            if(data_queue.empty())
                return false;
            value = data_queue.front();
            data_queue.pop();
            return true;
        }

        std::shared_ptr<T> try_pop()
        {
            std::lock_guard<std::mutex> lk(mut);
            if(data_queue.empty())
                return std::shared_ptr<T>();
            auto ret = std::make_shared<T>(data_queue.front());
            data_queue.pop();
            return ret;
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data_queue.empty();
        }
    private:
        mutable std::mutex mut;
        std::queue<T> data_queue;
        std::condition_variable data_condition;
    };
}