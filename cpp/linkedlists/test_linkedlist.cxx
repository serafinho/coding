#include "ListElement.h"
#include "Stack.h"

#include <iostream>

using namespace std;


int main()
{
    cout << "Testing linked list...\n";
    ListElement<int> head(1);

    ListElement<int> e1(2);
    head.setNext(&e1);

    ListElement<int> e2(3);
    e1.setNext(&e2);

    cout << head << endl;

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
    catch (runtime_error e)
    {
        cout << "Trying to pop from empty stack: " << e.what() << endl;
    }

}