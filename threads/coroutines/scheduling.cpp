#include <coroutine>
#include <iostream>
#include <list>


struct Scheduler
{
    std::list<std::coroutine_handle<>> tasks_{};

    bool schedule()
    {
        auto task = tasks_.front();
        tasks_.pop_front();

        if(not task.done())
        {
            task.resume();
        }
        return not tasks_.empty();
    }

    auto suspend()
    {
        struct awaiter : std::suspend_always{
            Scheduler& sched_;
            explicit awaiter(Scheduler& sched ) : sched_{sched}
            {}
            void await_suspend(std::coroutine_handle<> coro) const noexcept
            {
                sched_.tasks_.push_back(coro);
            }
        };
        return awaiter{*this};
    }
};

struct Task {
    struct promise_type {
        Task get_retrun_object(){return {};}
        std::suspend_never initial_suspend() noexcept {return {};}
        std::suspend_never final_suspend() noexcept {return {};}
        void unhandled_exception(){}
    };
};


Task taskA(Scheduler& sched)
{
    std::cout <<"Hello, from task A" <<std::endl;

    co_await sched.suspend();

    std::cout <<"a is back doing work" <<std::endl;

    co_await sched.suspend();

    std::cout <<"a is back doing more work" <<std::endl;
}


Task taskB(Scheduler& sched)
{
    std::cout <<"Hello, from task B" <<std::endl;

    co_await sched.suspend();

    std::cout <<"b is back doing work" <<std::endl;

    co_await sched.suspend();

    std::cout <<"b is back doing more work" <<std::endl;
}

void Use()
{
    Scheduler sched{};

    taskA(sched);
    taskB(sched);

    while(sched.schedule())
    {}
}

int main()
{
    Use();
    return 0;
}