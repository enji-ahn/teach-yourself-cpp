// BitOrder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <future>
#include <algorithm>
#include <chrono>
#include <random>
#include <stopwatch.hpp>

std::vector<int> init_vec(int loops, int count)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 900000);

    auto inputs = std::vector<int>();
    inputs.reserve(loops * count);

    std::vector<std::future<std::vector<int>>>
        vec;
    for (auto i = 0; i < loops; ++i)
    {
        vec.push_back(
            std::async(
                [&distrib, &gen, &count]() {
                    auto v = std::vector<int>();
                    v.reserve(count);
                    for (auto i = 0; i < count; ++i)
                        v.push_back(distrib(gen));
                    return v;
                }));
    }

    for (auto &v : vec)
    {
        auto part = v.get();
        std::move(part.begin(), part.end(), std::back_inserter(inputs));
    }

    return inputs;
}

/**
 * @brief 삽입 정렬을 수행합니다.
 *
 * @param inputs 입력값
 */
void insertion_sort(std::vector<int> inputs)
{
    const auto len = inputs.size();
    auto value = 0;
    auto lower_i = 0;
    for (auto i = 2; i < len; ++i)
    {
        value = inputs[i];
        lower_i = i;
        while (lower_i && inputs[lower_i - 1] > value)
        {
            inputs[i] = inputs[lower_i - 1];
            lower_i--;
        }

        inputs[lower_i] = value;
    }
}

int main()
{
    stopwatch swatch;
    auto inputs = init_vec(98, 100000);
    swatch.elapsed();

    swatch.reset();
    insertion_sort(inputs);
    swatch.elapsed();

    getchar();
}
