// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

// In general, ignore this file, but keep it around if you are using pre-compiled headers.

int generic_transform_algorithm()
{
    std::cout<<"illustrating the generic transform algorithm"<<std::endl;

    auto array1 = std::array<int, 5>{0, 1, 2, 3, 4};
    auto array2 = std::array<int, 5>{6, 7, 8, 9, 10};

    std::ostream_iterator<int> out(std::cout, " ");

    std::cout<<"Original sequence (array1) : ";
    std::copy(std::begin(array1), std::end(array1), out);
    std::cout<<std::endl;
    std::cout<<"Original sequence (array2) : ";
    std::copy(std::begin(array2), std::end(array2), out);
    std::cout<<std::endl;


    // array1  의 원소 하나와 array2 의 원소 하나를 차례로 더해서 출력 스트림으로 내보낸다
    std::cout<<"Transformed sequence : ";
    std::transform(std::begin(array1), std::end(array1), std::begin(array2), out, [](int a, int b) { return a + b;});
    std::cout<<std::endl;

    return 0;
}