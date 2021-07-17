#include "thread_pool.hpp"

#include <iostream>

thread_pool::thread_pool()
    : is_done_ { false }
{
    try {
        for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads_.emplace_back(&thread_pool::worker, this);
        }
    }
    catch(...) {
        is_done_ = false;
        throw std::runtime_error("Thread pool init error.");
    }
}

thread_pool::~thread_pool()
{
    is_done_ = true;
    for(auto& thread : threads_) {
        if( thread.joinable() ) {
            thread.join();
        }
    }
}

void thread_pool::worker()
{
    func_t func;
    while( !is_done_ ) {
        if( mutex_.try_lock() ) {
            if( !queue_.empty() ) {
                func = queue_.front();
                queue_.pop();
                mutex_.unlock();
                func();
            }
            else {
                mutex_.unlock();
            }
        }
        else {
            std::this_thread::yield();
        }
    }
}