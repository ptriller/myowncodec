//
// Created by ptriller on 20.06.16.
//
#include <iostream>
#include <string>
int main() {
    std::string test("test");
    for(char c: test) {
        std::cout << "Char:" << (int) c << std::endl;
    }
}