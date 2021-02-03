#include <iostream>
#include <cassert>
#include <string>

void shortest_lambda_call()
{
    std::cout<<"Enter >> "<<__func__<<std::endl;
    [] { std::cout << "hello lamda" << std::endl; }();

    std::cout<<std::endl;
}

/**
 * 람다에서 전역변수는 그냥 접근하면 됨
 */
int g_v = 10;
void access_global_variable_with_lambda()
{
    std::cout<<"Enter >> "<<__func__<<std::endl;
    printf("(outside lamda) g_v address: %p\n", &g_v);

    [] { 
        std::cout<<"global variable : "<<g_v<<std::endl;
        printf("( inside lamda) g_v address: %p\n", &g_v);
    }();

    std::cout<<std::endl;
}

void call_by_val_captured_lambda()
{
    std::cout<<"Enter >> "<<__func__<<std::endl;
    int a = 10;

    printf("(outside lamda) a address: %p\n", &a);
    auto plus_10 = [a](int x){
        printf("( inside lamda) a address: %p\n", &a);
        return a+x;
    };

    std::cout<<"10 + 10 => "<<plus_10(10)<<std::endl;

    a = 20; // 값을 변경했지만, lamda 로 캡쳐된 변수는 영향받지 않음

    std::cout<<"10 + 10 => "<<plus_10(10)<<std::endl;

    std::cout<<std::endl;
}

void call_by_ref_captured_lambda()
{
    std::cout<<"Enter >> "<<__func__<<std::endl;
    int a = 10;

    printf("(outside lamda) a address: %p\n", &a);
    auto plus_10 = [&a](int x){
        printf("( inside lamda) a address: %p\n", &a);
        return a+x;
    };

    std::cout<<"10 + 10 => "<<plus_10(10)<<std::endl;

    a = 20; // lamda 로 참조 캡쳐된 변수의 값이 변경되었으므로, lambda 내부에서 해당 변수 사용시 영향받음

    std::cout<<"10 + 10 => "<<plus_10(10)<<std::endl;

    std::cout<<std::endl;
}

/**
 * modify variables in lambda that capture call by val
 * 
 * Note: 값 복사로 캡쳐된 변수는 lambda 함수 안에서 const 타입으로 처리됩니다. (값 변경 불가)
 */
// void modify_var_in_call_by_val_captured_lambda()
// {
//     std::cout<<"Enter >> "<<__func__<<std::endl;
//     int a = 10;

//     printf("(outside lamda) a address: %p\n", &a);
//     auto plus_10_to_a = [a](){
//         printf("( inside lamda) a address: %p\n", &a);
//         a = a+10;  // 구문 에러 : "식이 수정할 수 있는 lvalue여야 합니다."
//     };

//     std::cout<<"a => "<<a<<std::endl;
//     plus_10_to_a();
//     std::cout<<"a plus 10 => "<<a<<std::endl;

//     std::cout<<std::endl;
// }

/**
 * modify variables in lambda that capture call by ref
 */
void modify_var_in_call_by_ref_captured_lambda()
{
    std::cout<<"Enter >> "<<__func__<<std::endl;
    int a = 10;

    printf("(outside lamda) a address: %p\n", &a);
    auto plus_10_to_a = [&a](){
        printf("( inside lamda) a address: %p\n", &a);
        a = a+10;  // 구문 에러 : "식이 수정할 수 있는 lvalue여야 합니다."
    };

    std::cout<<"a => "<<a<<std::endl;
    plus_10_to_a();
    std::cout<<"a plus 10 => "<<a<<std::endl;

    std::cout<<std::endl;
}

int main()
{
    shortest_lambda_call();
    access_global_variable_with_lambda();
    call_by_val_captured_lambda();
    call_by_ref_captured_lambda();
    // modify_var_in_call_by_val_captured_lambda();
    modify_var_in_call_by_ref_captured_lambda();
    return 0;
}
