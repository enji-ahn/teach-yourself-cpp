#include <iostream>
#include "stack1.hpp"
#include <string>

int main(void)
{
    try {
        Stack<int> intStack;
        Stack<std::string> stringStack;

        intStack.push(7);
        std::cout<<intStack.top()<<std::endl;

        stringStack.push("hello");
        std::cout<<stringStack.top()<<std::endl;
        stringStack.pop();
        stringStack.pop();
    } catch (std::exception const& e) {
        std::cerr<<"Exception: "<<e.what()<<std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
