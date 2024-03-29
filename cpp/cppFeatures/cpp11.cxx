#include <memory>
#include <iostream>
#include <numeric> // for accumulate
#include <vector>
#include <exception>

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
 Variadic Templates: For arbitrary number of args.
 Could use initializer lists instead
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


/*!
 * Rvalue references: Good for what?
 */
int x = 5;   // `x` is an lvalue of type `int`
int& xl = x; // `xl` is an lvalue of type `int&`
//    int&& xr = x; // compiler error -- `x` is an lvalue
int&& xr2 = 0; // `xr2` is an lvalue of type `int&&` -- binds to the rvalue temporary, `0`

void f(int& x)
{
    cout << "One: " << x << endl;
}

void f(int&& x)
{
    cout << "Two: " << x << endl;
}

void rValueReferences()
{
    f(x);  // calls f(int&)
    f(xl); // calls f(int&)
    f(3);  // calls f(int&&)
    f(move(x)); // calls f(int&&)

    f(xr2);      // calls f(int&)
    f(move(xr2));// calls f(int&& x)
}

/*!
 * Forwarding references: Good for what?
 */
template <typename T>
void fRef(T&& t) {
    cout << "fRef: " << t << endl;
}

void forwardReferences()
{
    int xRef = 3;
    fRef(1); // T is int, deduces as f(int &&) => f(int&&)
    fRef(xRef); // T is int&, deduces as f(int& &&) => f(int&)

    int& yRef = xRef;
    fRef(yRef); // T is int&, deduces as f(int& &&) => f(int&)

    int&& zRef = 4;   // NOTE: `z` is an lvalue with type `int&&`.
    fRef(zRef);       // T is int&, deduces as f(int& &&) => f(int&)
    fRef(move(zRef)); // T is int, deduces as f(int &&) => f(int&&)
}

/*!
 * Initializer lists: Simple replacement for vectors
 */
int sum(const initializer_list<int>& list)
{
  int total = 0;
  for (auto& e : list)
  {
    total += e;
  }

  return total;
}

void initializerLists()
{
    auto list = {1, 2, 3};
    cout << "Result: " << sum(list) << endl; // == 6
    cout << "Result: " << sum({1, 2, 3}) << endl; // == 6
    cout << "Result: " << sum({}) << endl; // == 0
}

/*!
  Static assertions: Good for what?
 */
constexpr int x_ass = 0;
constexpr int y_ass = 1;
static_assert(x_ass != y_ass);

/*!
 Auto
 */
template <typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y) {
  return x + y;
}

void autoDecl()
{
    cout << "Auto: " << add(1, 2) << endl; // == 3
    auto r = add(1, 2.0); // double
    cout << "Auto: " << r << endl; // == 3.0
    cout << "Auto: " << add(1.2, 1.8) << endl; // == 3.0
}

/*!
 Lambda: Unnamed function objects
 */
void lambdaFunctions()
{
    int x = 4;

    auto getX = [=] { return x; };
    cout << "X: " << getX() << endl;

    auto addX = [=](int y) { return x + y; };
    cout << "Sum: " << addX(1) << endl;
    
    auto getXRef = [&]() -> int& { return x; };
    cout << "XRef: " << getXRef() << endl; // int& to `x`
    
    auto f1 = [&x] { x = 999; }; // OK: x is a reference and modifies the original
    f1();
    cout << "Modified: " << x << endl;
}

/*
 decltype: declared type of expression
 */
class A
{
};

class B :public A
{
};

void decltypes()
{
    int x = 123;
    decltype(x) y = 1.23;
    
    cout << "y = " << y << endl;
    
    auto a = new A();
    decltype(a) b = new B();
    cout << b << endl;
}

/*!
 Type Aliases: Similar to typedef
 */
void txpeAliases()
{
    using IntVec = vector<int>;
    IntVec v; // std::vector<int>
    v.push_back(123);
    
    using String = std::string;
    String s {"foo"};
}

/*!
 nullptr: New type that cannot be converted to integral types except bool
 */
void foo(int x)
{
    cout << "Wham" << endl;
}
void foo(char* x)
{
    if(!x)
    {
        cout << "Bim!" << endl;
    }
    else
    {
        cout << "Bam!" << endl;
    }
}

void nullptrType()
{
    // ambiguous
    // foo(NULL);
    foo(nullptr);
    foo('a');
    foo((char*)'a');
}

void stronglyTypedEnums()
{
    // Specifying underlying type as `unsigned int`
    enum class Color : unsigned int { Red = 0xff0000, Green = 0xff00, Blue = 0xff };
    // `Red`/`Green` in `Alert` don't conflict with `Color`
    enum class Alert : bool { Red, Green };
    Color c = Color::Red;
    cout << "C: " << (unsigned int)c << endl;
}

// `noreturn` attribute indicates `f` doesn't return.
[[ noreturn ]] void attributes() {
  throw runtime_error("error");
}

struct Complex {
  constexpr Complex(double r, double i) : re{r}, im{i} { }
  constexpr double real() { return re; }
  constexpr double imag() { return im; }

  double re;
  double im;
};

void constantExpressions()
{
    constexpr Complex I(123, 1);
    cout << "Complex: " << I.re << endl;
}

struct Foo {
  int foo;
  Foo(int foo) : foo{foo} {}
  Foo() : Foo(123) {}
};

void delegationConstructors()
{
    Foo foo;
    cout << "Foo: " << foo.foo << endl;
}

int main()
{
    moveSematics();
    variadicTemplates();
    rValueReferences();
    forwardReferences();
    initializerLists();
    autoDecl();
    lambdaFunctions();
    decltypes();
    nullptrType();
    stronglyTypedEnums();
    try {
        attributes();
    }
    catch(exception &e)
    {
        cout << "Caught: " << e.what() << endl;
    }
    
    constantExpressions();
    delegationConstructors();
}
