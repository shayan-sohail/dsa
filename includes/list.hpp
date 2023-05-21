#include <iostream>
#include <optional>
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
    Node<T>* m_tail; /*Last Element*/

public:
    ListBase() : m_size(0), m_head(nullptr), m_tail(nullptr) {}

    virtual void add_front(T value) = 0;
    virtual void add_at(size_t index, T value) = 0;
    virtual void add_back(T value) = 0;

    virtual std::optional<T> remove_front() = 0;
    virtual std::optional<T> remove_at(size_t index) = 0;
    virtual std::optional<T> remove_back() = 0;

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

        if (this->m_size == 1) this->m_tail = this->m_head;
    }

    void add_at(size_t index, T value) override
    {
        if (index > this->m_size && index < 0) return;

        if (index == 0) add_front(value);
        else if (index == this->m_size) add_back(value);
        else
        {
            this->m_size++;
            auto itr = this->m_head;
            for (int i = 1; i < index; i++) itr = itr->next;

            Node<T>* temp = new Node<T>(value);
            temp->next = itr->next;
            itr->next = temp;
        }
    }

    void add_back(T value) override 
    {
        this->m_size++;
        Node<T>* temp = new Node<T>(value);
        this->m_tail->next = temp;
        this->m_tail = temp;
    }

    std::optional<T> remove_front() override 
    {
        if (this->m_size == 0) return std::nullopt;

        this->m_size--;
        Node<T>* temp = this->m_head;
        T val = temp->data;
        this->m_head = temp->next;
        delete temp;
        return val;
    }

    std::optional<T> remove_at(size_t index) override 
    {
        if (index > this->m_size-1 || this->m_size == 0) return std::nullopt;


        if (index == 0) return remove_front();
        else if (index == this->m_size - 1) return remove_back();
        else
        {
            this->m_size--;
            auto itr = this->m_head;
            for (int i = 1; i < index; i++) itr = itr->next;
            Node<T>* temp = itr->next;
            itr->next = temp->next;
            T val = temp->data;
            delete temp;
            return val;
        }
    }
    std::optional<T> remove_back() override 
    {
        if (this->m_size == 0) return std::nullopt;

        this->m_size--;
        Node<T>* temp = this->m_head;
        while (temp->next != this->m_tail) temp = temp->next;

        T val = this->m_tail->data;
        this->m_tail = temp;
        this->m_tail->next = nullptr;
        delete temp->next;
        return val;
    }

    void print()
    {
        std::cout << "Size is " << this->m_size << std::endl;
        Node<T>* it = this->m_head;
        while (it != nullptr)
        {
            std::cout << it->data << std::endl;
            it = it->next;
        }
    }

    void clear() override
    {
        Node<T>* it = this->m_head;
        while (it != nullptr)
        {
            Node<T>* temp = it;
            it = it->next;
            delete temp;
            this->m_size--;
        }
        this->m_head = nullptr;
        std::cout << "Linked List Cleared\n";
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
    m_List.add_back(6);
    m_List.add_back(7);
    m_List.print();
    
    m_List.add_at(4, 50);
    m_List.add_back(51);
    m_List.print();

    std::cout << "Removal\n";
    std::cout << "Remove Front -> " << *m_List.remove_front() << std::endl;
    m_List.print();

    std::cout << "Remove back -> " << *m_List.remove_back() << std::endl;
    m_List.print();

    std::cout << "Remove at 2 -> " << *m_List.remove_at(2) << std::endl;
    m_List.print();

    std::cout << "Remove at 0 -> " << *m_List.remove_at(0) << std::endl;
    m_List.print();

    std::cout << "Remove at 3 -> " << *m_List.remove_at(3) << std::endl;
    m_List.print();

    auto x = m_List.remove_at(5);
    if (x) std::cout << "Remove at 5 -> " << *x << std::endl;
    else {std::cout << "Out of Bound\n";}
    m_List.print();
}
