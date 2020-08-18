#ifndef __STOPWATCH_HPP__
#define __STOPWATCH_HPP__

#include <chrono>
#include <iostream>

class stopwatch
{
public:
    stopwatch();
    ~stopwatch();
    void elapsed();
    void reset();

private:
    stopwatch(const stopwatch &) = delete;
    stopwatch &operator=(const stopwatch &) = delete;

private:
    std::chrono::steady_clock::time_point _start;
};

inline stopwatch::stopwatch()
{
    _start = std::chrono::high_resolution_clock::now();
}

inline void stopwatch::elapsed()
{
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = stop - _start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
}

inline void stopwatch::reset()
{
    _start = std::chrono::high_resolution_clock::now();
}

inline stopwatch::~stopwatch()
{
}

#endif