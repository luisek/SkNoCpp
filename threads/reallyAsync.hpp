#pragma once
#include <future>

namespace mpb {

template <typename F, typename ... TS>
auto reallyAsync(F&& f, TS&& ...params)
{
    return std::async(std::launch::async, std::forward<F>(f), std::forward<TS>(params)...);
}

}