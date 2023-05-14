#include <iostream>

enum class ListType { Single, Double, Circular };

template <typename T>
class ListIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    ListIterator(T* ptr) : m_ptr(ptr) {}
    ListIterator(const ListIterator& other) : m_ptr(other.m_ptr) {}

    ListIterator& operator++()
    {
        m_ptr++;
        return *this;
    }

    ListIterator operator++(int) {
        ListIterator tmp(*this);
        operator++();
        return tmp;
    }

    bool operator==(const ListIterator& other) const {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const ListIterator& other) const {
        return m_ptr != other.m_ptr;
    }

    reference operator*() const {
        return *m_ptr;
    }

    pointer operator->() const {
        return m_ptr;
    }

private:
    T* m_ptr;
};

template <typename T>
class ListBase {
public:
    virtual void add(T value) = 0;
    virtual void remove(T value) = 0;
    virtual void print() const = 0;
    virtual ListIterator<T> begin() const = 0;
    virtual ListIterator<T> end() const = 0;

    using value_type = T;
    using iterator = ListIterator<T>;
    using const_iterator = ListIterator<const T>;
};

template <typename T, ListType LT = ListType::Single>
class List : public ListBase<T> {
public:
    List() {
        std::cout << "Creating List of type " << static_cast<int>(LT) << std::endl;
    }

    void add(T value) override {
        // Add value to the list
    }

    void remove(T value) override {
        // Remove value from the list
    }

    void print() const override {
        // Print the contents of the list
    }

    ListIterator<T> begin() const override {
        // Return an iterator to the beginning of the list
        return ListIterator<T>(nullptr);
    }

    ListIterator<T> end() const override {
        // Return an iterator to the end of the list
        return ListIterator<T>(nullptr);
    }
};

template <typename T>
class List<T, ListType::Single> : public ListBase<T> {
public:
    List() {
        std::cout << "Creating Single List" << std::endl;
    }

    void add(T value) override {
        // Add value to the single-linked list
    }

    void remove(T value) override {
        // Remove value from the single-linked list
    }

    void print() const override {
        // Print the contents of the single-linked list
    }

    ListIterator<T> begin() const override {
        // Return an iterator to the beginning of the single-linked list
        return ListIterator<T>(nullptr);
    }

    ListIterator<T> end() const override {
        // Return an iterator to the end of the single-linked list
        return ListIterator<T>(nullptr);
    }
};

template <typename T>
class List<T, ListType::Double> : public ListBase<T> {
public:
    List() {
        std::cout << "Creating Double List" << std::endl;
    }

    void add(T value) override {
        // Add value to the double-linked list
    }

    void remove(T value) override {
        // Remove value from the double-linked list
    }

    void print() const override {
        // Print the contents of the double-linked list
    }

    ListIterator<T> begin() const override {
        // Return an iterator to the beginning of the double-linked list
        return ListIterator<T>(nullptr);
    }

    ListIterator<T> end() const override {
        // Return an iterator to the end of the double-linked list
        return ListIterator<T>(nullptr);
    }
};

template <typename T>
class List<T, ListType::Circular> : public ListBase<T> {
public:
    List() {
        std::cout << "Creating Circular List" << std::endl;
    }

    void add(T value) override {
        // Add value to the circular-linked list
    }

    void remove(T value) override {
        // Remove value from the circular-linked list
    }

    void print() const override {
        // Print the contents of the circular-linked list
    }

    ListIterator<T> begin() const override {
        // Return an iterator to the beginning of the circular-linked list
        return ListIterator<T>(nullptr);
    }

    ListIterator<T> end() const override {
        // Return an iterator to the end of the circular-linked list
        return ListIterator<T>(nullptr);
    }
};
