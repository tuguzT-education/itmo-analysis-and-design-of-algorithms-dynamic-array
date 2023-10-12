#ifndef LAB2_ARRAY_INL
#define LAB2_ARRAY_INL

#include <cstdlib>
#include <cassert>
#include <span>
#include <concepts>

#define assert_message(expr, msg) assert((expr) && msg)

namespace lab2 {

namespace detail {

static inline constexpr std::size_t kDefaultCapacity = 8;
static inline constexpr float kExponentialGrowthFactor = 2.0f;

static inline constexpr std::size_t EnlargeCapacity(const std::size_t old_capacity) {
    if (old_capacity == 0) {
        return detail::kDefaultCapacity;
    }
    return static_cast<std::size_t>(static_cast<float>(old_capacity) * detail::kExponentialGrowthFactor);
}

template<class T>
static inline T *MemAlloc(const std::size_t capacity) {
    if (capacity == 0) {
        return nullptr;
    }
    return static_cast<T *>(std::malloc(sizeof(T) * capacity));
}

template<class T, class... Args>
static inline T &ConstructInPlace(T *dst, Args &&... args);

template<class T>
static inline T &CopyInPlace(T *const dst, const T &src) {
    return ConstructInPlace(dst, src);
}

template<class T>
static inline std::span<T> CopyInPlace(T *const dst, const std::span<T> src) {
    for (auto it = dst; const auto &item : src) {
        CopyInPlace(it, item);
        it += 1;
    }
    return std::span{dst, src.size()};
}

template<class T>
static inline T &MoveInPlace(T *const dst, T &&src) {
    return ConstructInPlace(dst, std::forward<T>(src));
}

template<class T>
static inline std::span<T> MoveInPlace(T *const dst, const std::span<T> src) {
    for (auto it = dst; auto &item : src) {
        MoveInPlace(it, std::move(item));
        it += 1;
    }
    return std::span{dst, src.size()};
}

template<class T, class... Args>
T &ConstructInPlace(T *const dst, Args &&... args) {
    return *new(dst) T{std::forward<Args>(args)...};
}

template<class T>
static inline std::span<T> ConstructInPlace(T *const dst, const std::span<T> src) {
    return CopyInPlace(dst, src);
}

template<std::movable T>
static inline std::span<T> ConstructInPlace(T *const dst, const std::span<T> src) {
    return MoveInPlace(dst, src);
}

template<class T>
static inline T &ConstructInPlace(T *const dst, T *const src) {
    return CopyInPlace(dst, *src);
}

template<std::movable T>
static inline T &ConstructInPlace(T *const dst, T *const src) {
    return MoveInPlace(dst, std::move(*src));
}

template<class T>
static inline void DestructInPlace(T *const ptr) {
    ptr->~T();
}

template<class T>
static inline void DestructInPlace(const std::span<T> span) {
    for (auto &item : span) {
        DestructInPlace(&item);
    }
}

template<class T>
static inline void ShiftLeftInPlace(T *const src, const std::size_t count) {
    for (std::size_t i = 0; i < count - 1; ++i) {
        auto current = src + i;
        auto next = current + 1;
        ConstructInPlace(current, next);
        DestructInPlace(next);
    }
}

template<class T>
static inline void ShiftRightInPlace(T *const src, const std::size_t count) {
    for (std::size_t i = count; i > 0; --i) {
        auto current = src + i - 1;
        auto next = current + 1;
        ConstructInPlace(next, current);
        DestructInPlace(current);
    }
}

}

template<class T>
Array<T>::Array() : Array{detail::kDefaultCapacity} {} // NOLINT(*-pro-type-member-init)

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
        detail::CopyInPlace(buffer_, std::span{other.buffer_, other.size_});
        size_ = other.size_;
    }
}

template<class T>
Array<T> &Array<T>::operator=(const Array &other) {
    Array temp{other};
    swap(temp);
    return *this;
}

template<class T>
Array<T>::Array(Array &&other) noexcept : Array{nullptr} { // NOLINT(*-pro-type-member-init)
    swap(other);
}

template<class T>
Array<T> &Array<T>::operator=(Array &&other) noexcept {
    swap(Array{nullptr});
    swap(other);
    return *this;
}

template<class T>
Array<T>::SizeType Array<T>::insert(ConstReference value) {
    return emplace(value);
}

template<class T>
Array<T>::SizeType Array<T>::insert(const SizeType index, ConstReference value) {
    return emplace(index, value);
}

template<class T>
template<class... Args>
Array<T>::SizeType Array<T>::emplace(Args &&... args) {
    return emplace(size_, std::forward<Args>(args)...);
}

template<class T>
template<class... Args>
Array<T>::SizeType Array<T>::emplace(const SizeType index, Args &&... args) {
    assert_message(index <= size_, "index should not be greater than size");
    if (size_ == capacity_) [[unlikely]] {
        const SizeType capacity = detail::EnlargeCapacity(capacity_);
        reserve(capacity);
        if (size_ == capacity_) {
            return -1;
        }
    }
    if (index != size_) {
        detail::ShiftRightInPlace(buffer_ + index, size_ - index);
    }
    detail::ConstructInPlace(buffer_ + index, std::forward<Args>(args)...);
    ++size_;
    return index;
}

template<class T>
void Array<T>::remove(const SizeType index) {
    assert_message(index < size_, "index should be less than size");
    detail::DestructInPlace(buffer_ + index);
    detail::ShiftLeftInPlace(buffer_ + index, size_ - index);
    --size_;
}

template<class T>
Array<T>::ConstReference Array<T>::operator[](const SizeType index) const noexcept {
    assert_message(index < size_, "index should be less than size");
    return buffer_[index];
}

template<class T>
Array<T>::Reference Array<T>::operator[](const SizeType index) noexcept {
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
void Array<T>::reserve(const SizeType capacity) {
    if (capacity <= capacity_) {
        return;
    }
    const auto new_buffer = detail::MemAlloc<T>(capacity);
    if (new_buffer == nullptr) {
        return;
    }
    detail::ConstructInPlace(new_buffer, std::span{buffer_, size_});
    detail::DestructInPlace(this);
    buffer_ = new_buffer;
    capacity_ = capacity;
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
void Array<T>::swap(Array &other) noexcept {
    std::swap(buffer_, other.buffer_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template<class T>
constexpr Array<T>::Iterator::Iterator(const Array &array, const bool reversed, const bool end) noexcept {
    current_ = array.buffer_;
    end_ = array.buffer_ + array.size_;
    if (reversed) {
        std::swap(--current_, --end_);
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
bool Array<T>::Iterator::operator==(const Iterator &other) const {
    return current_ == other.current_;
}

template<class T>
auto Array<T>::Iterator::operator<=>(const Iterator &other) const {
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
    const Array<T>::DifferenceType direction = isReversed() ? -1 : 1;
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
        std::swap(--current_, --end_);
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
bool Array<T>::ConstIterator::operator==(const ConstIterator &other) const {
    return current_ == other.current_;
}

template<class T>
auto Array<T>::ConstIterator::operator<=>(const ConstIterator &other) const {
    return current_ <=> other.current_;
}

template<class T>
Array<T>::ConstReference Array<T>::ConstIterator::operator*() const noexcept {
    return *current_;
}

template<class T>
typename Array<T>::ConstIterator &Array<T>::ConstIterator::operator++() noexcept {
    const Array<T>::DifferenceType direction = isReversed() ? -1 : 1;
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
