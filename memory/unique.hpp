#pragma once
#include <utility>

namespace mpb{

template<typename T>
class UniquePtr
{
public:
    using Pointer = T*;
    using Reference = T&;

    UniquePtr() : ptr_{nullptr}
    {}

    UniquePtr(Pointer ptr) : ptr_{ptr}
    {}

    ~UniquePtr()
    {
        delete ptr_;
    }

    UniquePtr(UniquePtr&& other) noexcept : ptr_{other.ptr_}
    {
        other.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
        if(this != &other)
        {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    Pointer operator->() const
    {
        return ptr_;
    }
    Reference operator*() const
    {
        return *ptr_;
    }
    Pointer get() const
    {
        return ptr_;
    }
    Pointer release()
    {
        Pointer tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }
    void reset(Pointer ptr = nullptr)
    {
        if(ptr_ == ptr)
            return;
        delete ptr_;
        ptr_ = ptr;
    }
    operator bool() const
    {
        return ptr_ != nullptr;
    }
private:
    Pointer ptr_;
};

template<typename T, typename ...Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}


}//namespace mpb