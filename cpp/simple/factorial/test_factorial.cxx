#include "Factorial.h"

#include <iostream>
#include <exception>

using namespace std;


int main()
{
    cout << "Compute factorials...\n";
    const int input = 5; 
    cout << input << "! = " << Factorial::compute(input, true) << endl;
    cout << input << "! = " << Factorial::compute(input, false) << endl;

    try 
    {
        Factorial::compute(-123, true);
    }
    catch(const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}