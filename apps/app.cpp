#include <Lab2/Array.hpp>

#include <iostream>

class A {
  public:
    explicit A(int i) : i_{i} {
        std::cout << "object A created from value " << i_ << std::endl;
    }

    A(const A &other) : i_{other.i_} {
        std::cout << "object A copied with value " << i_ << std::endl;
    }
    A &operator=(const A &other) {
        i_ = other.i_;
        std::cout << "object A copied with value " << i_ << std::endl;
    }

    A(A &&other) { // NOLINT(*-pro-type-member-init, *-noexcept-move-constructor)
        std::swap(i_, other.i_);
        other.i_ = 0;
        std::cout << "object A moved with value " << i_ << std::endl;
    }
    A &operator=(A &&other) { // NOLINT(*-noexcept-move-constructor)
        i_ = other.i_;
        other.i_ = 0;
        std::cout << "object A moved with value " << i_ << std::endl;
    }

    [[nodiscard]]
    int i() const { return i_; }

    ~A() {
        std::cout << "object A destroyed with value " << i_ << std::endl;
        i_ = -1;
    }

  private:
    int i_;
};

int main() {
    lab2::Array<A> array{3};
    array.emplace(1);
    array.emplace(A{3});
    array.emplace(std::move(A{4}));
    std::cout << std::endl;

    using Index = decltype(array)::SizeType;
    array.emplace(Index{1}, 2);
    std::cout << std::endl;

    array.remove(2);
    std::cout << std::endl;

    for (const auto &item : array) {
        std::cout << "Item is " << item.i() << std::endl;
    }
    std::cout << std::endl;
}
