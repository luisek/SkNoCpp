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
            std::cout <<__PRETTY_FUNCTION__ <<sharedCounter <<std::endl;
        }
        void decrementShared()
        {
            --sharedCounter;
            std::cout <<__PRETTY_FUNCTION__ <<sharedCounter <<std::endl;
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
        constexpr sharedPtr()
        {
            p = new T;
            ctrl = new ControlBlock;
        }

        constexpr sharedPtr(const sharedPtr& rt)
        {
            p = rt.p;
            ctrl = rt.ctrl;
            ctrl->incrementShared();
        }

        sharedPtr& operator=(const sharedPtr& rt)
        {
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
        
    private:
        Pointer p;
        ControlBlock* ctrl;
    };
}