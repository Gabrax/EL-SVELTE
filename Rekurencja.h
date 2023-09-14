#ifndef UNTITLED_REKURENCJA_H
#define UNTITLED_REKURENCJA_H

#include <iostream>
#include <string>
#include <cmath>

//Returns the sum of the first n natural numbers
int recursiveSum(int n)
{
    // stop Rekurencja when n is 0 or 1
    if(n<=1)
    {
        return n;
    }
    else
    {
        // return sum of each number
        return n + recursiveSum(n-1);
    }
}

//Returns the sum of the first n even numbers
int evenSquares(int n)
{
    if(n==0)
        return n;
        //check if n is even
    else if (n% 2 == 0)
    {
        //sum of even numbers  squares
        return n * n + evenSquares(n - 1);
    }
    else
    {
        //if number is off - do nothing and call function again
        return evenSquares(n-1);
    }
}

// returns the sum of the first even numbers' squares
int evenSquares2(int n)
{
    // stop recursion when n is 0
    if(n==0)
        return n;
        // check if n is even
    else
    {
        return pow(n+n,2) + evenSquares2(n-1);
    }
}

//return the nth Fibonacci number
int fibNumber(int n)
{
    //stop recursion when n is 0 or 1
    if(n <= 1)
    {
        return n;
    }
    else
    {
        return fibNumber(n-1) + fibNumber(n-2);
    }
}

bool linear (std::string s, char c, int l)
{
    if (l<0)
    {
        return false;
    }
    else if(s[l]==c)
    {
        return true;
    }
    else
    {
        return linear(s, c, l-1);
    }
}




#endif //UNTITLED_REKURENCJA_H
