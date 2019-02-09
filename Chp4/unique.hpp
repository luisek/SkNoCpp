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

        uniquePtr(Pointer pt)
        {
            p = pt;
        }
        constexpr uniquePtr()
        {
            p = new T;
        }

        ~uniquePtr()
        {
            delete p;
        }

        uniquePtr(uniquePtr&& rt)
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
        
        Pointer p = nullptr;
    };

template<typename T, typename... Ts>
//uniquePtr<T> 
decltype(auto) make_unique(Ts&&... params)
{
    return uniquePtr<T>(new T(std::forward<Ts>(params)...));
}
}