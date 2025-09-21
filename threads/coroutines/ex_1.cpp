#include <iostream>
#include <coroutine>
#include <utility>
#include <vector>



struct Generator
{

    struct promise_type 
    {
        int val_{};

        auto get_return_object() ->Generator 
        {
            return Generator{this};
        }

        auto initial_suspend() noexcept -> std::suspend_never
        {
            return {};
        }

        auto final_suspend() noexcept -> std::suspend_always
        {
            return {};
        }

        auto yield_value(int v) noexcept ->std::suspend_always
        {
            val_ = v;
            return {};
        }

        auto unhandled_exception()
        {
            std::cout <<"Unhandled exception, terminate" <<std::endl;
            std::terminate();
        }
    };

    using Handle = std::coroutine_handle<promise_type>;
    Handle mCoroHdl{};

    explicit Generator(promise_type* p) : mCoroHdl{Handle::from_promise(*p)}
    {}

    Generator(Generator&& rhs) : mCoroHdl{std::exchange(rhs.mCoroHdl, nullptr)}
    {}

    ~Generator()
    {
        if(mCoroHdl)
        {
            mCoroHdl.destroy();
        }
    }

    auto value() const 
    {
        return mCoroHdl.promise().val_;
    }

    auto finished() const -> bool
    {
        return mCoroHdl.done();
    }

    auto resume() -> void
    {
        if(not finished())
        {
            mCoroHdl.resume();
        }
    }

    // struct sentinel {};

    // struct iterator
    // {
    //     Handle mCoroHdl{};

    //     auto operator==(sentinel) const -> bool
    //     {
    //         return mCoroHdl.done();
    //     }
    //     auto operator++() -> iterator&
    //     {
    //         mCoroHdl.resume();
    //         return *this;
    //     }
    //     auto operator*() const -> const int
    //     {
    //         return mCoroHdl.promise().val_;
    //     }
    // };

    // iterator begin()
    // {
    //     return {mCoroHdl};
    // }
    // sentinel end()
    // {
    //     return {};
    // }
};
Generator interleaved(std::vector<int> a, std::vector<int> b)
{
    auto lamb = [](std::vector<int>& v) -> Generator {
        for(const auto& e: v)
        {
            co_yield e;
        }
    };
    auto x = lamb(a);
    auto y = lamb(b);
    while(not x.finished() or not y.finished()) {
        if(not x.finished()) {
            co_yield x.value();
            x.resume();
        }
        if(not y.finished()) {
            co_yield y.value();
            y.resume();
        }
    }
}



void Use()
{
    std::vector a{2,4,6,8};
    std::vector b{3,5,7,9};

    Generator g{interleaved(std::move(a), std::move(b))};

    while(not g.finished())
    {
        std::cout <<g.value() <<"\n";
        g.resume();
    }

    // for(const auto& e : g)
    // {
    //     std::cout <<e <<std::endl;
    // }
}

int main()
{
    Use();
    return 0;
}

