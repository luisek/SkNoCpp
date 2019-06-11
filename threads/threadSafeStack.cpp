#include <iostream>
#include <mutex>
#include <exception>
#include <stack>
#include <memory>

struct empty_stack : std::exception
{
    const char* what() const noexcept
    {
        return "empty stack";
    }
};

template<typename T>
class threadsafe_stack
{
public:
    threadsafe_stack()
    {}
    threadsafe_stack(const threadsafe_stack& other)
    {
        //dlaczego other.m? a no dlatego aby inny wątek nie zmodyfikował w tym czasie tych danych...
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(new_value);
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if(data.empty())
        {
            throw empty_stack();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
private:
    std::stack<T> data;
    mutable std::mutex m;
};

int main(int argc, char* argv[])
{
    threadsafe_stack<int> st;
    st.push(12);
    st.push(32);

    auto val1 = st.pop();
    auto val2 = st.pop();
    std::cout <<*val1 <<std::endl;
    std::cout <<*val2 <<std::endl;
    return 0;
}
