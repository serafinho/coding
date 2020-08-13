#include "ListElement.h"
#include "Stack.h"

#include <iostream>

using namespace std;


int main()
{
    cout << "Testing linked list...\n";
    auto head = std::make_shared<ListElement<int>>(1);

    auto e1 = std::make_shared<ListElement<int>>(2);
    head->setNext(e1);

    auto e2 = std::make_shared<ListElement<int>>(3);
    e1->setNext(e2);

    cout << *head << endl;

    Stack<int> stack;
    stack.push(1);
    stack.push(3);
    cout << "Stack: " << stack << endl;
    int v = stack.pop();
    cout << "Popped: " << v << endl;
    cout << "Stack: " << stack << endl;

    stack.push(4);
    cout << "Stack: " << stack << endl;

    v = stack.pop();
    cout << "Popped: " << v << endl;
    cout << "Stack: " << stack << endl;

    v = stack.pop();
    cout << "Popped: " << v << endl;
    cout << "Stack: " << stack << endl;

    try
    {
        v = stack.pop();
    }
    catch (exception e)
    {
        cout << "Trying to pop from empty stack: " << e.what() << endl;
    }

}