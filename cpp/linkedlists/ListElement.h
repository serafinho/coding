#ifndef _LINKEDLIST_H__
#define _LINKEDLIST_H__

#include <iostream>
#include <memory>

/**
* This class manages a linked list element
*/
template <class T>
class ListElement
{
    public:
        ListElement(const T& value) : m_value(value), m_next(nullptr)
        {
        }

        ~ListElement()
        {
        }

        void setNext(std::shared_ptr<ListElement> next)
        {
            m_next = next;
        }
           
        std::shared_ptr<ListElement> getNext() const
        {
            return m_next;
        }
        
        void setValue(const T &value)
        {
            m_value = value;
        }

        const T& value() const
        {
            return m_value;
        }

    private:
        std::shared_ptr<ListElement> m_next;
        T m_value;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const ListElement<T>& e)
{
    auto current = e;
    while(current.getNext()!=nullptr)
    {
        os << current.value() << ", ";
        current = *current.getNext();
    }
    os << current.value();

    return os;
}

#endif
