#ifndef LAB2_ARRAY
#define LAB2_ARRAY

#include <cstddef>

namespace lab2 {

template<class T>
class Array final {
  public:
    using ValueType = T;
    using SizeType = std::size_t;
    using DifferenceType = std::ptrdiff_t;
    using Reference = ValueType &;
    using ConstReference = const ValueType &;
    using ForwardingReference = ValueType &&;
    using ConstForwardingReference = const ValueType &&;
    using Pointer = ValueType *;
    using ConstPointer = const ValueType *;
    class Iterator;
    class ConstIterator;
    using ReverseIterator = Iterator;
    using ConstReverseIterator = ConstIterator;

    explicit Array();
    explicit Array(std::nullptr_t);
    explicit Array(SizeType capacity);

    Array(const Array &other);
    Array &operator=(const Array &other);

    Array(Array &&other) noexcept;
    Array &operator=(Array &&other) noexcept;

    SizeType insert(ConstReference value);
    SizeType insert(SizeType index, ConstReference value);

    template<class... Args>
    SizeType emplace(Args &&... args);

    template<class... Args>
    SizeType emplace(SizeType index, Args &&... args);

    void remove(SizeType index);

    ConstReference operator[](SizeType index) const noexcept;
    Reference operator[](SizeType index) noexcept;

    SizeType size() const noexcept; // NOLINT(*-use-nodiscard)
    SizeType capacity() const noexcept; // NOLINT(*-use-nodiscard)

    void reserve(SizeType capacity);

    Pointer data() noexcept;
    ConstPointer data() const noexcept;
    ConstPointer cdata() const noexcept;

    Iterator begin() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator cbegin() const noexcept;

    Iterator end() noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cend() const noexcept;

    ReverseIterator rbegin() noexcept;
    ConstReverseIterator rbegin() const noexcept;
    ConstReverseIterator rcbegin() const noexcept;

    ReverseIterator rend() noexcept;
    ConstReverseIterator rend() const noexcept;
    ConstReverseIterator rcend() const noexcept;

    ~Array();

  private:
    void swap(Array &other) noexcept;

    Pointer buffer_;
    SizeType size_;
    SizeType capacity_;
};

template<class T>
class Array<T>::Iterator final {
  public:
    constexpr explicit Iterator(const Array &array, bool reversed, bool end) noexcept;

    ConstReference get() const noexcept;
    void set(ConstReference value);

    void next() noexcept;
    bool hasNext() const noexcept; // NOLINT(*-use-nodiscard)
    bool isReversed() const noexcept; // NOLINT(*-use-nodiscard)

    bool operator==(const Iterator &other) const;
    auto operator<=>(const Iterator &other) const;

    Reference operator*() noexcept;
    ConstReference operator*() const noexcept;

    Iterator &operator++() noexcept;
    const Iterator operator++(int) noexcept;

  private:
    Pointer current_;
    Pointer end_;
};

template<class T>
class Array<T>::ConstIterator final {
  public:
    constexpr explicit ConstIterator(const Array &array, bool reversed, bool end) noexcept;

    ConstReference get() const noexcept;

    void next() noexcept;
    bool hasNext() const noexcept; // NOLINT(*-use-nodiscard)
    bool isReversed() const noexcept; // NOLINT(*-use-nodiscard)

    bool operator==(const ConstIterator &other) const;
    auto operator<=>(const ConstIterator &other) const;

    ConstReference operator*() const noexcept;

    ConstIterator &operator++() noexcept;
    const ConstIterator operator++(int) noexcept;

  private:
    Pointer current_;
    Pointer end_;
};

}

#include "Array.inl"

#endif //LAB2_ARRAY
