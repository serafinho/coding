#ifndef __STACK_H__
#define __STACK_H__

#include "ListElement.h"

#include <iostream>
#include <memory>
#include <stdexcept>

/**
* This class manages a stack
*/
template <class T>
class Stack
{
    public:
        Stack() : m_head(nullptr)
        {

        }

        ~Stack()
        {
        }

        void push(const T& value)
        {
            auto e = std::make_shared<ListElement<T>>(value);
            if (isEmpty())
            {
                m_head = e;
            }
            else
            {
                auto last = findTail();
                last->setNext(e);
            }
        }

        T pop()
        {
            if (isEmpty())
            {
                throw std::runtime_error("Stack is empty");
            }
            // find tail and get its value to be returned
            auto tail = findTail();
            T result = tail->value();
               
            if (tail == m_head)
            {
                // if this is the last element on the stack
                // set head to nullptr
                m_head = nullptr;
            }
            else
            {
                // set new tail
                auto newTail = findPredecessor(tail);
                // drop reference to old tail
                newTail->setNext(nullptr);
            }

            return result;
        }

        bool isEmpty() const
        {
            return m_head == nullptr;
        }

        friend std::ostream& operator<<(std::ostream& os, const Stack<T>& s)
        {
            if (s.isEmpty())
            {
                os << "<empty>";
            }
            else
            {
                auto e = s.m_head;
                while (e->getNext() != nullptr)
                {
                    os << e->value() << ", ";
                    e = e->getNext();
                }
                os << e->value();
            }

            return os;
        }

    private:
        std::shared_ptr<ListElement<T>> findTail() const
        {
            return findPredecessor(nullptr);
        }

        std::shared_ptr<ListElement<T>> findPredecessor(std::shared_ptr<ListElement<T>> elem) const
        {
            auto e = m_head;
            while (e->getNext() != elem && e->getNext()!=nullptr)
            {
                e = e->getNext();
            }
            if (e->getNext() == elem)
            {
                return e;
            }
            else
            {
                throw std::logic_error("Internal error: Element not in list");
            }
        }
        
        std::shared_ptr<ListElement<T>> m_head;
};


#endif
