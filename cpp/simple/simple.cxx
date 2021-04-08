#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <list>
#include <vector>
#include <stack>

using namespace std;

/**
 * Print fizzbuzz numbers from children's game 
 */
void runFizzBuzz()
{
    for(int i=1; i<100; i++)
    {
        auto div3 = (i%3==0);
        auto div5 = (i%5==0);
        
        stringstream result;
        if(div3)
        {
            result << "Fizz";
        }
        if(div5)
        {
            result << "Buzz";
        }
        if(!div3 && !div5)
        {
            result << i;
        }
        cout << result.str() << endl;
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
template<class T>
void printList(const T& l)
{
    stringstream s;
    
    s << "[";
    for (const auto &e: l)
    {
        s << e << ", ";
    }
    s.seekp(-2, ios_base::end);
    s << "]";
    cout << s.str() << endl;
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
* Check for correct parentheses nesting
*/
bool parenthesesCorrect(const string& input)
{
    int counter = 0;
    for (auto c : input)
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

void vectorError()
{
    vector<int> v {1, 2, 3, 4};
    auto size = v.size();
    for(int i=0; i<size; i++)
    {
        v.push_back(v[i]*v[i]);
    }
    printList(v);
}

int main()
{

    vectorError();
    
    runFizzBuzz();

    const string inputString = "HonkyDoodle";
    cout << inputString << " reversed: " << reverseString(inputString) << endl;

    list<int> input { 1, 2, 3, 4, 1, 3, 5, 2, 2, 1, 5, 8, 1 };
    cout << "Input: ";
    printList(input);

    auto output = removeDuplicates(input);
    cout << "Output: ";
    printList(output);

    const string s1 = "(())";
    const string s2 = "()()";
    const string s3 = ")(";
    cout << "Checking " << s1 << ": " << parenthesesCorrect(s1) << endl;
    cout << "Checking " << s2 << ": " << parenthesesCorrect(s2) << endl;
    cout << "Checking " << s3 << ": " << parenthesesCorrect(s3) << endl;
 
}
