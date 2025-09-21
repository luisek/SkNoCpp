#include <iostream>
#include <coroutine>
#include <utility>
#include <string>

using namespace std::string_literals;

struct Chat
{
    struct promise_type
    {
        std::string msgOut_{};
        std::string msgIn_{};

        //what to do in case of exception
        auto unhandled_exception() noexcept -> void 
        {
            std::cerr <<"Unhandled exception in coroutine" <<std::endl;
            std::terminate();
        }
        //Coroutine creation
        auto get_return_object() -> Chat
        {
            return Chat{this};
        }
        //Startup
        auto initial_suspend() noexcept -> std::suspend_always
        {
            return {};
        }

        //value from co_yield
        auto yield_value(std::string msg) noexcept -> std::suspend_always
        {
            msgOut_ = std::move(msg);
            return {};
        }

        //value from co_await
        auto await_transform(std::string) noexcept
        {
            //customized version instead of using suspend_always or suspend_never
            struct awaiter
            {
                promise_type& pt;
                auto await_ready() const noexcept -> bool
                {
                    return  ;
                }
                auto await_resume() const noexcept -> std::string
                {
                    return std::move(pt.msgIn_);
                }
                auto await_suspend(std::coroutine_handle<>) const noexcept -> void
                {}
            };
            return awaiter{*this};
        }

        //value from co_return
        auto return_value(std::string msg) noexcept -> void 
        {
            msgOut_ = std::move(msg);
        }
        //ending
        auto final_suspend() noexcept -> std::suspend_always
        {
            return {};
        }
    };
    using Handle = std::coroutine_handle<promise_type>;
    Handle mCoroHdl{};

    //get the handle from the promise
    explicit Chat(promise_type* p) : mCoroHdl{Handle::from_promise(*p)} {}
    Chat(Chat&& rhs) : mCoroHdl {std::exchange(rhs.mCoroHdl, nullptr)}{} //Move only!

    //care taking, destroying the handle if needed
    ~Chat()
    {
        if(mCoroHdl)
        {
            mCoroHdl.destroy();
        }
    }
    //active the coroutine and wait for data
    auto listen() -> std::string
    {
        if(not mCoroHdl.done())
        {
            mCoroHdl.resume();
        }
        return std::move(mCoroHdl.promise().msgOut_);
    }

    //send data to the coroutine and activate it
    auto answer(std::string msg) -> void
    {
        mCoroHdl.promise().msgIn_=msg;
        if(not mCoroHdl.done())
        {
            mCoroHdl.resume();
        }
    }
};

Chat Fun()
{
    co_yield "Hello!\n"s; //call promise_type.yield_value

    std::cout << co_await std::string{}; //calls promise_type.await_transform

    co_return "Here!\n"s;
}

void Use()
{
    Chat chat = Fun();

    std::cout <<chat.listen();
    chat.answer("Where are you?\n");
    std::cout <<chat.listen();
}

int main()
{
    Use();
    return 0;
}

