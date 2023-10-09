#include <Lab2/Array.hpp>

#include <iostream>

int main() {
    lab2::Array<int> array{};
    array.insert(1);
    array.insert(2);

    for (auto item : array) {
        std::cout << item << std::endl;
    }
}
