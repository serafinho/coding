#include "LinkedList.h"

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
}