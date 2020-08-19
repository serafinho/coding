#include <iostream>
#include <memory>
#include <typeinfo>

using namespace std;

class Visitor;

class Base 
{
public:
    /**
    * Pure virtual method for visitor pattern
    */
    virtual void accept(Visitor &v) = 0;
};

/**
* Visitor class, applies functions to Base classes
*/
class Visitor
{
public:
    void visit(Base& b)
    {
        // This could be anything...
        cout << "Visiting: " << typeid(b).name() << endl;
    }
};


class A1 : public Base
{
public:
    void accept(Visitor& v) override
    {
        v.visit(*this);
    }
};

class A2 : public Base
{
public:
    void accept(Visitor& v) override
    {
        v.visit(*this);
    }
};

/**
* Main class implementing the Factory and Singleton patterns
*/
class App1
{
public:
    static App1* instance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new App1();
        }
        return m_instance;
    }

    virtual shared_ptr<Base> createA()
    {
        return make_shared<A1>();
    }
protected:
    App1() {}

private:
    static App1* m_instance;
};

App1* App1::m_instance = nullptr;

/**
* Another main class implementing the Factory and Singleton patterns
*/
class App2
{
public:
    static App2* instance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new App2();
        }
        return m_instance;
    }

    virtual shared_ptr<Base> createA()
    {
        return make_shared<A2>();
    }

private:
    static App2* m_instance;
};
App2* App2::m_instance = nullptr;


int main()
{
    cout << "Demonstrating Design Patterns...\n";
    Visitor v;

    auto a1 = App1::instance()->createA();
    a1->accept(v);

    auto a2 = App2::instance()->createA();
    a2->accept(v);

}