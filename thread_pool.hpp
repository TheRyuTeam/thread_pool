#pragma once
#include <atomic>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>

class thread_pool
{
public:
    using func_t = std::function<void()>;
private:
    std::mutex mutex_;
    std::atomic_bool is_done_;
    std::queue<func_t> queue_;
    std::vector<std::thread> threads_;

public:
    thread_pool();

    ~thread_pool();

    void worker();

    template<typename _Func_t>
    void submit(_Func_t&& _func);

};

template<typename _Func_t>
void thread_pool::submit(_Func_t&& _func)
{
    queue_.push(func_t(_func));
}