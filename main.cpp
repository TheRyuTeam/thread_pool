#include <iostream>
#include "thread_pool.hpp"

static int i = 0;

void func()
{
    std::cout << i++ << '\n';
}

int main()
{
    thread_pool tp;
    std::cout << "TC:\t" << std::thread::hardware_concurrency() << '\n';
    for(size_t j = 0; j < 8; ++j)
        tp.submit(func);
    for(int k = 0; k < 100000000; ++k)
        ;
    return 0;
}
