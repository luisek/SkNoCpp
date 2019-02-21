#pragma once 
#include <utility>

namespace mpb
{
    template <typename T>
    class uniquePtr
    {
    public:
        using Pointer = T*;
        uniquePtr(const uniquePtr&) = delete;
        uniquePtr& operator=(const uniquePtr&) = delete;

        uniquePtr(Pointer pt) noexcept
        {
            p = pt;
        }
        constexpr uniquePtr() noexcept
        {
            p = nullptr;
        }

        ~uniquePtr()
        {
            delete p;
        }

        uniquePtr(uniquePtr&& rt) noexcept
        {
            p = rt.p;
            rt.p = nullptr;
        }

        uniquePtr& operator=(uniquePtr&& rt)
        {
            p = rt.p;
            rt.p = nullptr;
            return *this;
        }

        Pointer get() const noexcept
        {
            return p;
        }

    private:
        
        Pointer p;
    };

template<typename T, typename... Ts>
uniquePtr<T> make_unique(Ts&&... params)
{
    return uniquePtr<T>(new T(std::forward<Ts>(params)...));
}
}