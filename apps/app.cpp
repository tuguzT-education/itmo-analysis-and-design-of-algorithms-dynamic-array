#include <Lab2/Array.hpp>

#include <iostream>

int main() {
    lab2::Array<int> array{};
    for (auto item : array) {
        std::cout << item << std::endl;
    }
}
