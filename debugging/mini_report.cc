#include <iostream>

int foo(int a, int b) {
    #if ENABLE_MULTIPLICATION
        return a * b;
    #else 
        return a + b;
    #endif

} 



int main(void) {
    int temp = foo(30, 40);
    std::cout << temp << std::endl;
    return 0;
} 