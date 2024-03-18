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
    std::uniform_int_distribution<> distrib(0, 9000);

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
 * @brief 쉘 정렬을 수행합니다.
 *
 * @param inputs 입력값
 */
void shell_sort(std::vector<int> inputs)
{
    // FIXME: 구현이 정상인지 확인 필요. (속도가 느린걸 보면... 비정상인데..;)
    const auto len = inputs.size();
    int sublst_i = 1; // sub list 의 시작 index 값
    while (sublst_i < len)
    {
        sublst_i = 3 * sublst_i + 1;
    }

    for (auto i = 0; i < len; ++i)
    {
        printf("%04d ", inputs[i]);
    }
    printf("\n");

    while (sublst_i > 0)
    {
        auto value = 0;
        auto lower_i = 0;
        for (auto i = sublst_i + 1; i < len; ++i)
        {
            value = inputs[i];
            lower_i = i;
            while (lower_i && lower_i > sublst_i && inputs[lower_i - sublst_i] > value)
            {
                inputs[lower_i] = inputs[lower_i - sublst_i];

                for (auto j = 0; j < len; ++j)
                {
                    if (j == i || j == (lower_i - sublst_i))
                    {
                        printf("%04d ", inputs[j]);
                    }
                    else
                    {
                        printf("     ");
                    }
                }
                printf("\n");

                lower_i = lower_i - sublst_i;
            }

            inputs[lower_i] = value;
        }

        for (auto j = 0; j < len; ++j)
        {
            printf("-----");
        }
        printf("\n");

        sublst_i = sublst_i / 3;
    }
}

int main()
{
    stopwatch swatch;
    auto inputs = init_vec(2, 10);
    swatch.elapsed();

    swatch.reset();
    shell_sort(inputs);
    swatch.elapsed();

    getchar();
}
