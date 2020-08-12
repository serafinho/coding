#ifndef __FACTORIAL_H__
#define __FACTORIAL_H__


class Factorial 
{
    public:
        /**
         * Compute factorial of integer n
         * 
         *  @param n input number
         *  @param recursive select algorithm to be used (true if recursive or iterative otherwise)
         *  @exception invalid_argument if n is negative 
         */
        static unsigned long long int compute(const int n, const bool recursive);

    private:
        /**
         *  Compute factorial recursively
         */
        static unsigned long long int fact_recursive(const unsigned long long int n) noexcept;

        /**
         *  Compute factorial iteratively
         */
        static unsigned long long int fact_iterative(const int n);

};

#endif
