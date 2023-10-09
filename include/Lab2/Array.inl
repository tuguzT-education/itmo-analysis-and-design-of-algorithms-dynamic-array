#ifndef LAB2_ARRAY_INL
#define LAB2_ARRAY_INL

#include <cstdlib>
#include <cassert>
#include <span>

#define assert_message(expr, msg) assert((expr) && msg)

namespace lab2 {

namespace detail {

template<class T>
static inline constexpr Array<T>::SizeType kDefaultCapacity = 8;

template<class T>
static inline T *MemAlloc(const std::size_t capacity) {
    if (capacity == 0) {
        return nullptr;
    }
    return static_cast<T *>(std::malloc(sizeof(T) * capacity));
}

template<class T>
static inline void CopyInPlace(const T &src, T *dst) {
    new(dst) T{src};
}

template<class T>
static inline void CopyInPlace(const std::span<T> src, T *dst) {
    for (const auto &item : src) {
        CopyInPlace(item, dst);
        ++dst;
    }
}

template<class T>
static inline void DestructInPlace(const T *ptr) {
    ptr->~T();
}

template<class T>
static inline void DestructInPlace(const std::span<T> span) {
    for (auto &item : span) {
        DestructInPlace(&item);
    }
}

}

template<class T>
Array<T>::Array() : Array{detail::kDefaultCapacity<T>} {} // NOLINT(*-pro-type-member-init)

template<class T>
Array<T>::Array(std::nullptr_t) : Array{std::size_t{0}} {} // NOLINT(*-pro-type-member-init)

template<class T>
Array<T>::Array(const SizeType capacity) : size_{0}, capacity_{0} {
    buffer_ = detail::MemAlloc<T>(capacity);
    if (buffer_ != nullptr) {
        capacity_ = capacity;
    }
}

template<class T>
Array<T>::Array(const Array &other) : Array{other.capacity_} { // NOLINT(*-pro-type-member-init)
    if (buffer_ != nullptr) {
        detail::CopyInPlace(std::span{other.buffer_, other.size_}, buffer_);
        size_ = other.size_;
    }
}

template<class T>
Array<T> &Array<T>::operator=(const Array &other) {
    Array temp{other};
    SwapMembers(temp);
    return *this;
}

template<class T>
Array<T>::Array(Array &&other) noexcept : Array{nullptr} { // NOLINT(*-pro-type-member-init)
    SwapMembers(other);
}

template<class T>
Array<T> &Array<T>::operator=(Array &&other) noexcept {
    SwapMembers(Array{nullptr});
    SwapMembers(other);
    return *this;
}

template<class T>
Array<T>::ConstReference Array<T>::operator[](const Array::SizeType index) const noexcept {
    assert_message(index < size_, "index should be less than size");
    return buffer_[index];
}

template<class T>
Array<T>::Reference Array<T>::operator[](const Array::SizeType index) noexcept {
    assert_message(index < size_, "index should be less than size");
    return buffer_[index];
}

template<class T>
Array<T>::SizeType Array<T>::size() const noexcept {
    return size_;
}

template<class T>
Array<T>::SizeType Array<T>::capacity() const noexcept {
    return capacity_;
}

template<class T>
Array<T>::Pointer Array<T>::data() noexcept {
    return buffer_;
}

template<class T>
Array<T>::ConstPointer Array<T>::data() const noexcept {
    return buffer_;
}

template<class T>
Array<T>::ConstPointer Array<T>::cdata() const noexcept {
    return buffer_;
}

template<class T>
Array<T>::~Array() {
    detail::DestructInPlace(std::span{buffer_, size_});
    std::free(buffer_);
}

template<class T>
void Array<T>::SwapMembers(Array &other) noexcept {
    std::swap(buffer_, other.buffer_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

}

#undef assert_message

#endif //LAB2_ARRAY_INL
