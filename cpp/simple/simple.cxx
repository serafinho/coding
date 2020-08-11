#include <iostream>
#include <string>
#include <sstream>
#include <exception>

using namespace std;


/**
 *  Returns the factorial of a number
 */
unsigned long long int fact_recursive(const int n)
{
    if(n==0)
    {
        return 1;
    }
    return n*fact_recursive(n-1);
}

/**
 *  Returns the factorial of a number
 */
unsigned long long int fact_iterative(const int n)
{
    int result = 1;
    for(int i=0; i<n; i++)
    {
        result *= i+1;
    }
    return result;
}

unsigned long long int fact(const int n, const bool recursive)
{
    if(n<0)
    {
        throw invalid_argument("Factorial for negative numbers are not defined...");
    }

    if(recursive)
    {
        return fact_recursive(n);
    }
    else
    {
        return fact_iterative(n);
    }
}

/**
 * Print fizzbuzz numbers from children's game 
 */
void runFizzBuzz()
{
    for(int i=0; i<100; i++)
    {
        bool div3 = (i%3==0);
        bool div5 = (i%5==0);
        
        string result = to_string(i);
        if(div3 && div5)
        {
            result = "FizzBuzz";
        }
        else if(div3)
        {
            result = "Fizz";
        }
        else if(div5)
        {
            result = "Buzz";
        }
        cout << result << endl;
    }
}

/**
 * Returns a reversed string
 */
string reverseString(const string& input)
{
    const int length  = input.length();
    stringstream out; 
    for(int i=0; i<length; i++)
    {
        out << input.at(length-i-1);
    }
    return out.str();
}

int main()
{
    cout << "Running simple tests...\n";
    const int input = 5; 
    cout << input << "! = " << fact(input, true) << endl;
    cout << input << "! = " << fact(input, false) << endl;

    try 
    {
        fact(-123, true);
    }
    catch(const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }


    runFizzBuzz();

    const string inputString = "HonkyDoodle";
    cout << inputString << " reversed: " << reverseString(inputString) << endl;

    return 0;
}