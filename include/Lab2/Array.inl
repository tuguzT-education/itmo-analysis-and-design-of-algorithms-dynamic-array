#ifndef LAB2_ARRAY_INL
#define LAB2_ARRAY_INL

#include <cstdlib>

namespace lab2 {

namespace detail {

template<class T>
constexpr Array<T>::SizeType kDefaultCapacity = 8;

}

template<class T>
Array<T>::Array(): Array(detail::kDefaultCapacity<T>) {} // NOLINT(*-pro-type-member-init)

template<class T>
Array<T>::Array(SizeType capacity): size_{0}, capacity_{0} {
    buffer_ = static_cast<Pointer>(std::malloc(sizeof(T) * capacity));
    if (buffer_ != nullptr) {
        capacity_ = capacity;
    }
}

template<class T>
Array<T>::~Array() {
    std::free(buffer_);
}

}

#endif //LAB2_ARRAY_INL
