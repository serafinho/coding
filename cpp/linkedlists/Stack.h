#ifndef __STACK_H__
#define __STACK_H__

#include "ListElement.h"

#include <iostream>

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
            auto e = new ListElement<T>(value);
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
                throw runtime_error("Stack is empty");
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
                newTail->setNext(nullptr);
            }

            // delete old tail
            delete tail;
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
        ListElement<T>* findTail() const
        {
            return findPredecessor(nullptr);
        }

        ListElement<T>* findPredecessor(const ListElement<T>* elem) const
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
                throw logic_error("Internal error: Element not in list");
            }
        }
        
        ListElement<T> *m_head;
};


#endif
