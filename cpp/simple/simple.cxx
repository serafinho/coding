#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <list>

using namespace std;

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


/**
 * Remove all duplicates from a list 
 */
list<int> removeDuplicates(const list<int> &input)
{
    
}

int main()
{

    runFizzBuzz();

    const string inputString = "HonkyDoodle";
    cout << inputString << " reversed: " << reverseString(inputString) << endl;

    return 0;
}