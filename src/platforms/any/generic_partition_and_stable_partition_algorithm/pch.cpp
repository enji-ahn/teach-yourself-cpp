// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

// In general, ignore this file, but keep it around if you are using pre-compiled headers.

int generic_partition_and_stable_partition_algorithm()
{
    std::cout << "illustrating the generic partition and stable_partition algorithms" << std::endl;

    const auto N = 7;
    int array0[N] = {50, 30, 10, 70, 60, 40, 20};
    int array1[N];
    std::copy(std::begin(array0), std::end(array0), std::begin(array1));

    auto out = std::ostream_iterator<int>(std::cout, " ");
    std::cout<<"Original sequence : ";
    std::copy(std::begin(array1), std::end(array1), out);
    std::cout<<std::endl;

    auto partition_cond = [](int i){ return i > 40; };
    // 40 0보다 큰 수는 앞에, 40 보다 작거나 같은 수는 뒤쪽에 위치하도록 array1을 파티션 합니다.
    auto split = std::partition(std::begin(array1), std::end(array1), partition_cond);
    std::cout<<"result of (unstable) partitioning : ";
    std::copy(std::begin(array1), split, out);
    std::cout<<" | ";
    std::copy(split, std::end(array1), out);
    std::cout<<std::endl;

    // array1 의 내용을 array0 의 값들로 원상 복구 합니다.
    std::copy(std::begin(array0), std::end(array0), std::begin(array1));

    // 다시한번 40 보다 큰 수는 앞쪽에, 40 보다 작거나 같은수는 뒤쪽에 위치하도록 array1 을 파티션 하되, 각 그룹 내에서의 상대 위치는 그대로 유지하도록 합니다.
    split = std::stable_partition(std::begin(array1), std::end(array1), partition_cond);
    std::cout<<"result of stable partitioning : ";
    std::copy(std::begin(array1), split, out);
    std::cout<<" | ";
    std::copy(split, std::end(array1), out);
    std::cout<<std::endl;

    return 0;
}