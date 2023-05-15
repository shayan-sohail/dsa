#include <iostream>
#include <list>

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

/*List Interface*/
template <typename T>
class ListBase {

protected:
    size_t m_size;

public:
    ListBase() : m_size(0) {}

    virtual void add_front(T value) = 0;
    virtual void add_at(T value, size_t index) = 0;
    virtual void add_back(T value) = 0;

    virtual void remove_front(T value) = 0;
    virtual void remove_at(T value, size_t index) = 0;
    virtual void remove_back(T value) = 0;

    virtual ListIterator<T> begin() const = 0;
    virtual ListIterator<T> end() const = 0;

    using value_type = T;
    using iterator = ListIterator<T>;
    using const_iterator = ListIterator<const T>;
};

/*Generic Class with enum templated argument*/
template <typename T, ListType LT = ListType::Single>
class List : public ListBase<T> {

public:
    List() {
        std::cout << "Creating List of type " << static_cast<int>(LT) << std::endl;
    }

    void add_front(T value) override { std::cout << "Generic add_front" << std::endl; }
    void add_at(T value, size_t index) override {}
    void add_back(T value) override {}

    void remove_front(T value) override {}
    void remove_at(T value, size_t index) override {}
    void remove_back(T value) override {}

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
class List<T, ListType::Double>
{
public:
    void add_back(const T& value)
    {
        std::cout << "Adding " << value << " to Double List" << std::endl;
    }
};

template <typename T>
class List<T, ListType::Circular>
{
public:
    void add_back(const T& value)
    {
        std::cout << "Adding " << value << " to Circular List" << std::endl;
    }
};

int main()
{
    List<int> m_List;
    m_List.add_back(5);
}