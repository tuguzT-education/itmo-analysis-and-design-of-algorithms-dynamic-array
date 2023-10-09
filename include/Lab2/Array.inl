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
    return cdata();
}

template<class T>
Array<T>::ConstPointer Array<T>::cdata() const noexcept {
    return buffer_;
}

template<class T>
Array<T>::Iterator Array<T>::begin() noexcept {
    return Iterator{*this, false, false};
}

template<class T>
Array<T>::ConstIterator Array<T>::begin() const noexcept {
    return cbegin();
}

template<class T>
Array<T>::ConstIterator Array<T>::cbegin() const noexcept {
    return ConstIterator{*this, false, false};
}

template<class T>
Array<T>::Iterator Array<T>::end() noexcept {
    return Iterator{*this, false, true};
}

template<class T>
Array<T>::ConstIterator Array<T>::end() const noexcept {
    return cend();
}

template<class T>
Array<T>::ConstIterator Array<T>::cend() const noexcept {
    return ConstIterator{*this, false, true};
}

template<class T>
Array<T>::ReverseIterator Array<T>::rbegin() noexcept {
    return ReverseIterator{*this, true, false};
}

template<class T>
Array<T>::ConstReverseIterator Array<T>::rbegin() const noexcept {
    return rcbegin();
}

template<class T>
Array<T>::ConstReverseIterator Array<T>::rcbegin() const noexcept {
    return ConstReverseIterator{*this, true, false};
}

template<class T>
Array<T>::ReverseIterator Array<T>::rend() noexcept {
    return ReverseIterator{*this, true, true};
}

template<class T>
Array<T>::ConstReverseIterator Array<T>::rend() const noexcept {
    return rcend();
}

template<class T>
Array<T>::ConstReverseIterator Array<T>::rcend() const noexcept {
    return ConstReverseIterator{*this, true, true};
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

template<class T>
constexpr Array<T>::Iterator::Iterator(const Array &array, const bool reversed, const bool end) noexcept {
    current_ = array.buffer_;
    end_ = array.buffer_ + array.size_;
    if (reversed) {
        std::swap(current_, end_);
    }
    if (end) {
        current_ = end_;
    }
}

template<class T>
Array<T>::ConstReference Array<T>::Iterator::get() const noexcept {
    return *current_;
}

template<class T>
void Array<T>::Iterator::set(ConstReference value) {
    *current_ = value;
}

template<class T>
void Array<T>::Iterator::next() noexcept {
    operator++();
}

template<class T>
bool Array<T>::Iterator::hasNext() const noexcept {
    return current_ != end_;
}

template<class T>
bool Array<T>::Iterator::isReversed() const noexcept {
    return current_ > end_;
}

template<class T>
bool Array<T>::Iterator::operator==(const Array<T>::Iterator &other) const {
    return current_ == other.current_;
}

template<class T>
auto Array<T>::Iterator::operator<=>(const Array<T>::Iterator &other) const {
    return current_ <=> other.current_;
}

template<class T>
Array<T>::Reference Array<T>::Iterator::operator*() noexcept {
    return *current_;
}

template<class T>
Array<T>::ConstReference Array<T>::Iterator::operator*() const noexcept {
    return *current_;
}

template<class T>
typename Array<T>::Iterator &Array<T>::Iterator::operator++() noexcept {
    const auto direction = isReversed() ? -1 : 1;
    current_ += direction;
    return *this;
}

template<class T>
const typename Array<T>::Iterator Array<T>::Iterator::operator++(int) noexcept { // NOLINT(*-const-return-type)
    Iterator old{*this};
    operator++();
    return old;
}

template<class T>
constexpr Array<T>::ConstIterator::ConstIterator(const Array &array, const bool reversed, const bool end) noexcept {
    current_ = array.buffer_;
    end_ = array.buffer_ + array.size_;
    if (reversed) {
        std::swap(current_, end_);
    }
    if (end) {
        current_ = end_;
    }
}

template<class T>
Array<T>::ConstReference Array<T>::ConstIterator::get() const noexcept {
    return *current_;
}

template<class T>
void Array<T>::ConstIterator::next() noexcept {
    operator++();
}

template<class T>
bool Array<T>::ConstIterator::hasNext() const noexcept {
    return current_ != end_;
}

template<class T>
bool Array<T>::ConstIterator::isReversed() const noexcept {
    return current_ > end_;
}

template<class T>
bool Array<T>::ConstIterator::operator==(const Array<T>::ConstIterator &other) const {
    return current_ == other.current_;
}

template<class T>
auto Array<T>::ConstIterator::operator<=>(const Array<T>::ConstIterator &other) const {
    return current_ <=> other.current_;
}

template<class T>
Array<T>::ConstReference Array<T>::ConstIterator::operator*() const noexcept {
    return *current_;
}

template<class T>
typename Array<T>::ConstIterator &Array<T>::ConstIterator::operator++() noexcept {
    const auto direction = isReversed() ? -1 : 1;
    current_ += direction;
    return *this;
}

template<class T>
const typename Array<T>::ConstIterator Array<T>::ConstIterator::operator++(int) noexcept { // NOLINT(*-const-return-type)
    Iterator old{*this};
    operator++();
    return old;
}

}

#undef assert_message

#endif //LAB2_ARRAY_INL
