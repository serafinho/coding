#include <iostream>
#include <memory>
#include <typeinfo>

using namespace std;

class Visitor;

class Base 
{
public:
    virtual ~Base() {}
    /**
    * Pure virtual method for visitor pattern
    */
    virtual void accept(Visitor &v) = 0;

    virtual void decorated() = 0;
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

    void decorated() override
    {
        cout << "Normal function call on class A1...\n";
    }
};

class A2 : public Base
{
public:
    void accept(Visitor& v) override
    {
        v.visit(*this);
    }

    void decorated() override
    {
        cout << "Normal function call on class A2...\n";
    }
};

class Decorator : public Base
{
public:
    Decorator(shared_ptr<Base> base) : m_base(base)
    {
    }

    /**
    * Decorator also implement Visitor pattern
    */
    void accept(Visitor& v) override
    {
        v.visit(*this);
    }

    void decorated() override 
    {
        m_base->decorated();
        cout << "This is some decoration...\n";
    }

private:
    shared_ptr<Base> m_base;
};

class Factory
{
public:
    enum Type {Type_A1, Type_A2};
    std::shared_ptr<Base> create(Type t)
    {
        switch(t) {
            case Type_A1:
                return std::make_shared<A1>();
            case Type_A2:
                return std::make_shared<A2>();
            default:
                throw runtime_error("Invalid enum in factory call");
        }
    }
};

/**
* Main class implementing  and Singleton patterns
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

protected:
    App1() {}

private:
    static App1* m_instance;
};

App1* App1::m_instance = nullptr;

/**
* Another main class implementing the  Singleton pattern
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

private:
    static App2* m_instance;
};
App2* App2::m_instance = nullptr;


int main()
{
    cout << "Demonstrating Design Patterns...\n";
    Visitor v;

    // Factory
    Factory f;
    auto a1 = f.create(Factory::Type_A1);
    // Visitor
    a1->accept(v);

    // Factory
    auto a2 = f.create(Factory::Type_A2);
    // Visitor
    a2->accept(v);

    // Decorator
    auto decorator = new Decorator(a1);
    decorator->decorated();
    
    // Visitor
    decorator->accept(v);

}
