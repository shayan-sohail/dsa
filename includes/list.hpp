#include <iostream>
#include <list>

enum class ListType { Single, Double, Circular };

template<typename T>
class Node
{
public:
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};


/*List Interface*/
template <typename T>
class ListBase
{
protected:
    size_t m_size;
    Node<T>* m_head;
    Node<T>* m_tail; /*One past the last element*/

public:
    ListBase() : m_size(0), m_head(nullptr), m_tail(nullptr) {}

    virtual void add_front(T value) = 0;
    virtual void add_at(T value, size_t index) = 0;
    virtual void add_back(T value) = 0;

    virtual void remove_front(T value) = 0;
    virtual void remove_at(T value, size_t index) = 0;
    virtual void remove_back(T value) = 0;

    virtual void clear() = 0;
};

/*Generic Class with enum templated argument*/
template <typename T, ListType LT = ListType::Single>
class List : public ListBase<T> {

public:
    List()
    {
        std::cout << "Creating List of type " << static_cast<int>(LT) << std::endl;
    }
    ~List()
    {
        this->clear();
    }

    void add_front(T value) override
    {
        this->m_size++;
        Node<T>* temp = new Node<T>(value);
        temp->next = this->m_head;
        this->m_head = temp;
    }

    void add_at(T value, size_t index) override {}
    void add_back(T value) override {}

    void remove_front(T value) override {}
    void remove_at(T value, size_t index) override {}
    void remove_back(T value) override {}

    void print()
    {
        std::cout << "Size is " << this->m_size << std::endl;
        Node<T>* it = this->m_head;
        while (it != this->m_tail)
        {
            std::cout << it->data << std::endl;
            it = it->next;
        }
    }
    void clear() override
    {
        Node<T>* it = this->m_head;
        while (it != this->m_tail)
        {
            Node<T>* temp = it;
            it = it->next;
            delete temp;
            this->m_size--;
        }
        this->m_head = nullptr;
    }
};

/*
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
*/
int main()
{
    List<int> m_List;
    m_List.add_front(5);
    m_List.add_front(4);
    m_List.add_front(3);
    m_List.add_front(2);
    m_List.add_front(1);
    m_List.print();
    m_List.clear();
    m_List.print();

}