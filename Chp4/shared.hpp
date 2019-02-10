#pragma once
#include <atomic>
#include <utility>
#include <iostream>

namespace mpb
{
    class ControlBlock
    {
    public:
        ControlBlock() = default;
        ControlBlock(const ControlBlock&) = default;
        ControlBlock& operator=(const ControlBlock&) = default;
        ControlBlock(ControlBlock&&) = default;
        ControlBlock& operator=(ControlBlock&&) = default;
        
        void incrementShared()
        {
            ++sharedCounter;
        }
        void decrementShared()
        {
            --sharedCounter;
        }
        int getSharedCount()
        {
            return sharedCounter.load();
        }
    private:
        std::atomic<int> sharedCounter{1};
    };

    template<typename T>
    class sharedPtr
    {
    public:
        using Pointer = T*;
        using Value = T;
        constexpr sharedPtr() : p{new T()}, ctrl{new ControlBlock}
        {
        }

        constexpr sharedPtr(Pointer value)
        {
            p = value;
            ctrl = new ControlBlock();
        }

        constexpr sharedPtr(Value value)
        {
            p = new T(value);
            ctrl = new ControlBlock();
        }

        constexpr sharedPtr(const sharedPtr& rt)
        {
            p = new T();
            p = rt.p;
            ctrl = rt.ctrl;
            ctrl->incrementShared();
        }

        sharedPtr& operator=(const sharedPtr& rt)
        {
            if(*this == rt)
                return *this;
            delete p;
            delete ctrl;
            p = new T;
            p = rt.p;
            ctrl = rt.ctrl;
            ctrl->incrementShared();

            return *this;
        }

        constexpr sharedPtr(sharedPtr&& rt)
        {
            p = rt.p;
            ctrl = rt.ctrl;
            rt.p = nullptr;
            rt.ctrl = nullptr;
        }

        sharedPtr& operator=(sharedPtr&& rt)
        {
            p = rt.p;
            ctrl = rt.ctrl;

            rt.p = nullptr;
            rt.ctrl = nullptr;
            return *this;
        }

        ~sharedPtr()
        {
            ctrl->decrementShared();
            if(0 == ctrl->getSharedCount())
            {
                delete p;
                delete ctrl;
            }
        }

        bool operator==(const sharedPtr<T>& other)
        {
            if(p == other.p)
                return true;
            return false;
        }
        
    private:
        Pointer p;
        ControlBlock* ctrl;
    };
}