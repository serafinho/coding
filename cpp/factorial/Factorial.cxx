#include "Factorial.h"

#include <iostream>
#include <exception>

using namespace std;


unsigned long long int Factorial::fact_recursive(const unsigned long long int n) noexcept
{
    if(n==0)
    {
        return 1;
    }
    return n*fact_recursive(n-1);
}

unsigned long long int Factorial::fact_iterative(const int n) noexcept
{
    unsigned long long int result = 1;
    for(int i=1; i<=n; i++)
    {
        result *= static_cast<long long int>(i);
    }
    return result;
}

unsigned long long int Factorial::compute (const int n, const bool recursive)
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

