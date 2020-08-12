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
    const size_t length  = input.length();
    stringstream out; 
    for(size_t i=0; i<length; i++)
    {
        out << input.at(length-i-1);
    }
    return out.str();
}


/** 
* Print a list
*/
void printList(const list<int>& l)
{
    for (auto const& elem : l)
    {
        cout << elem << ", ";
    }
    cout << endl;
}

/**
 * Remove all duplicates from a list 
 */
list<int> removeDuplicates(const list<int> &input)
{
    list<int> result = input;
    result.sort();
    result.unique();
    return result;
}


/**
* Check for correct prenthesis nesting
*/
bool parenthesisCorrect(const string& input)
{
    int counter = 0;
    for (const char& c : input)
    {
        if (c == '(')
        {
            counter++;
        }
        else if (c == ')')
        {
            counter--;
        }
        if (counter < 0)
        {
            // We should never have more closed brackets than open 
            // ones, so exit the loop if this should happen
            break;
        }
    }

    return counter == 0;
}

int main()
{

    runFizzBuzz();

    const string inputString = "HonkyDoodle";
    cout << inputString << " reversed: " << reverseString(inputString) << endl;

    list<int> input = { 1, 2, 3, 4, 1, 3, 5, 2, 2, 1, 5, 8, 1 };
    cout << "Input: ";
    printList(input);

    auto output = removeDuplicates(input);
    cout << "Output: ";
    printList(output);

    const string s1 = "(())";
    const string s2 = "()()";
    const string s3 = ")(";
    cout << "Checking " << s1 << ": " << parenthesisCorrect(s1) << endl;
    cout << "Checking " << s2 << ": " << parenthesisCorrect(s2) << endl;
    cout << "Checking " << s3 << ": " << parenthesisCorrect(s3) << endl;

    return 0;
}