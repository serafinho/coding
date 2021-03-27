#include <memory>
#include <iostream>
#include <numeric> // for accumulate


using namespace std;

/*!
* Move Semantics
*/
void moveSematics()
{
    unique_ptr<int> p1 = make_unique<int>(1);

    // error -- cannot copy unique pointers
    // unique_ptr<int> p2 = p1; 
    unique_ptr<int> p3 = move(p1); // move `p1` into `p3`
                                   // now unsafe to dereference object held by `p1`

    cout << "Moved pointer: " << *p3.get() << endl;
    // Bad access:
    // cout << "Original pointer: " << *p1.get() << endl;
}

/*!
* Variadic Templates
*/
template <typename First, typename... Args>
auto sum(const First first, const Args... args) -> decltype(first) 
{
  const auto values = {first, args...};

  // this is a C++20 feature...
  return accumulate(values.begin(), values.end(), First{0});
}

void variadicTemplates()
{
    cout << "Int: " << sum(1, 2, 3, 4, 5) << endl; // 15
    cout << "Double: "<< sum(1.5, 2.0, 3.7) << endl; // 7.2
    // unable to deduce due to inconsistent initializer list
    // cout << "Double: " << sum(1.0, 2, 3, 4, 5) << endl; // 15.0
}

int main()
{
    moveSematics();
    variadicTemplates();
}