#include <iostream>
#include <coroutines>

enum class ExecutionStatus {
    WAITING,
    RUNNING,
    PAUSED,
    FINISHED
};

struct RunConcept {
    struct promise_type {
        ExecutionStatus value_{};
        RunConcept get_retrun_object()
        {
            return RunConcept{this};
        }
        std::suspned_always initial_suspend()
        {
            return {};
        }
        
        auto return_value() const ->ExecutionStatus
        {
            return value_;
        }

        void unhandled_exception()
        {
            std::cerr <<"  " <<std::endl;
            std::terminate();
        }
        std::suspend_always final_suspend() noexcept
        {
            return {};
        }
    };

    using Handle = std::coroutine_handle<promise_type>;
    Handle mHandler_{};

    explicit RunConcept(promise_type* p) : mHandler_{Handle::from_promise(*p)}
    {}

    RunConcept(RunConcept&& rhs) : mHandler_{std::exchange(rhs.mHandler_, nullptr)}
    {}
    ~RunConcept()
    {
        if(mHandler_)
        {
            mHandler_.destroy();
        }
    }
    auto run() 
    {

    }

    auto value() const 
    {
        return mHandler_.promise().val_;
    }

    auto finished() const -> bool
    {
        return mHandler_.done();
    }

    auto resume() -> void
    {
        if(not finished())
        {
            mHandler_.resume();
        }
    }
};