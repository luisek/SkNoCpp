#pragma once
#include <thread>

namespace mpb {
    class RAIIThread
    {
        public:
            enum class DtorAction
            {
                JOIN,
                DETACH
            };
            RAIIThread(std::thread&& thread, DtorAction action = DtorAction::JOIN)
                : action_(action), thread_(std::move(thread))
            {}
            ~RAIIThread()
            {
                if(thread_.joinable())
                {
                    if(action_ == DtorAction::JOIN)
                    {
                        thread_.join();
                    }
                    else
                    {
                        thread_.detach();
                    }
                }
            }
            RAIIThread(RAIIThread&& other) = default;
            RAIIThread& operator=(RAIIThread&& other) = default;
            RAIIThread(const RAIIThread&) = delete;
            RAIIThread& operator=(const RAIIThread&) = delete;
            
            std::thread& get()
            {
                return thread_;
            }
        private:
            DtorAction action_;
            std::thread thread_;
    };
}