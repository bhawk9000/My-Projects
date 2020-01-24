// COPYRIGHT (C) 2017 Ben Hawk (bih9@zips.uakron.edu) All rights reserved.
// rational.hpp: Definition of rational class and its interace.

#include "rational.hpp"
#include <iostream>

// -------------------------------------------------------------------------- //
// Helper functions

// Compute the GCD of two integer values using Euclid's algorithm.
int
gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}


// Compute the LCM of two integer values.
int
lcm(int a, int b)
{
    return (std::abs(a) / gcd(a, b)) * std::abs(b);
}


// -------------------------------------------------------------------------- //
// Rational implementation

// Default Constructor Definition
Rational::Rational(int num, int denom)
{
    if (num != 0 && denom == 0)
    {
        std::cout << "The number entered does not exist." << std::endl;
        exit(1);
    }
    if (num == 0)
    {
        denom = 0;
    }
    if (num > 0 && denom < 0)
    {
        num = -num;
        denom = abs(denom);
    }
    if (num < 0 && denom < 0)
    {
        num = abs(num);
        denom = abs(denom);
    }
    if ((num < denom) && (denom % num == 0))
    {
        denom = denom / num;
        num = num / num;
    }
    if ((num > denom) && (num % denom == 0))
    {
        num = num / denom;
        denom = 1;
    }
    if ((num > denom) && (num % denom != 0))
    {
        int leastcm = lcm(num, denom);
        int oldNumer = num;
        int newNumer = (leastcm / denom);
        denom = (leastcm / oldNumer);
        num = newNumer;
    }
    if (num != 0 && denom != 0 && num == denom)
    {
        num = 1;
        denom = 1;
    }
    numerator = num;
    denominator = denom;
}
// Pre- Nothing
// Post- Overloads the == operator for the rational class
bool Rational::operator == (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;

    if ((tempLeftDenom == 0 && tempRightDenom == 0) || (tempLeftNumer == 0 && tempRightNumer == 0)
            || (tempLeftDenom == 0 && tempRightNumer == 0) || (tempLeftNumer == 0 && tempRightDenom == 0))
    {
        return (true);
    }

    else if (tempLeftDenom != tempRightDenom)
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom);
        tempRightNumer = (commonDenom / tempRightDenom);

        return (tempLeftNumer == tempRightNumer);
    }
    else
    {
        return (tempLeftNumer == tempRightNumer);
    }
}
// Pre- Nothing
// Post- Overloads the == operator for ints on the LHS and the Rational class on the RHS
bool operator == (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left == rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (left == rightint);
    }
    return (left == (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the != operator for the rational class
bool Rational::operator != (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;

    if ((tempLeftDenom == 0 && tempRightDenom == 0) || (tempLeftNumer == 0 && tempRightNumer == 0)
            || (tempLeftDenom == 0 && tempRightNumer == 0) || (tempLeftNumer == 0 && tempRightDenom == 0))
    {
        return (false);
    }

    else if (tempLeftDenom != tempRightDenom)
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom);
        tempRightNumer = (commonDenom / tempRightDenom);

        return (tempLeftNumer != tempRightNumer);
    }
    else
    {
        return (tempLeftNumer != tempRightNumer);
    }
}
// Pre- Nothing
// Post- Overloads the == operator for ints on the LHS and the Rational class on the RHS
bool operator != (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left != rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (left != rightint);
    }
    return (left != (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the < operator for the rational class
bool Rational::operator < (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;

    if ((tempLeftDenom == 0 && tempRightDenom == 0) || (tempLeftNumer == 0 && tempRightNumer == 0)
            || (tempLeftDenom == 0 && tempRightNumer == 0) || (tempLeftNumer == 0 && tempRightDenom == 0))
    {
        return (false);
    }

    else if (tempLeftDenom != tempRightDenom)
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom);
        tempRightNumer = (commonDenom / tempRightDenom);

        return (tempLeftNumer < tempRightNumer);
    }
    else
    {
        return (tempLeftNumer < tempRightNumer);
    }
}
// Pre- Nothing
// Post- Overloads the < operator for ints on the LHS and the Rational class on the RHS
bool operator < (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left < rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (left < rightint);
    }
    return (left < (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the > operator for the rational class
bool Rational::operator > (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;

    if ((tempLeftDenom == 0 && tempRightDenom == 0) || (tempLeftNumer == 0 && tempRightNumer == 0)
            || (tempLeftDenom == 0 && tempRightNumer == 0) || (tempLeftNumer == 0 && tempRightDenom == 0))
    {
        return (false);
    }

    else if (tempLeftDenom != tempRightDenom)
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom);
        tempRightNumer = (commonDenom / tempRightDenom);

        return (tempLeftNumer > tempRightNumer);
    }
    else
    {
        return (tempLeftNumer > tempRightNumer);
    }
}
// Pre- Nothing
// Post- Overloads the > operator for ints on the LHS and the Rational class on the RHS
bool operator > (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left > rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (left > rightint);
    }
    return (left > (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the <= operator for the rational class
bool Rational::operator <= (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;

    if ((tempLeftDenom == 0 && tempRightDenom == 0) || (tempLeftNumer == 0 && tempRightNumer == 0)
            || (tempLeftDenom == 0 && tempRightNumer == 0) || (tempLeftNumer == 0 && tempRightDenom == 0))
    {
        return (true);
    }

    else if (tempLeftDenom != tempRightDenom)
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom);
        tempRightNumer = (commonDenom / tempRightDenom);

        return (tempLeftNumer <= tempRightNumer);
    }
    else
    {
        return (tempLeftNumer <= tempRightNumer);
    }
}
// Pre- Nothing
// Post- Overloads the <= operator for ints on the LHS and the Rational class on the RHS
bool operator <= (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left <= rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (left <= rightint);
    }
    return (left <= (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the >= operator for the rational class
bool Rational::operator >= (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;

    if ((tempLeftDenom == 0 && tempRightDenom == 0) || (tempLeftNumer == 0 && tempRightNumer == 0)
            || (tempLeftDenom == 0 && tempRightNumer == 0) || (tempLeftNumer == 0 && tempRightDenom == 0))
    {
        return (true);
    }

    else if (tempLeftDenom != tempRightDenom)
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom);
        tempRightNumer = (commonDenom / tempRightDenom);

        return (tempLeftNumer >= tempRightNumer);
    }
    else
    {
        return (tempLeftNumer >= tempRightNumer);
    }
}
// Pre- Nothing
// Post- Overloads the >= operator for ints on the LHS and the Rational class on the RHS
bool operator >= (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left >= rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (left >= rightint);
    }
    return (left >= (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the + operator for the rational class
Rational Rational::operator + (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;
    if (tempLeftNumer == 0 && tempRightNumer == 0)
    {
        return Rational(0,0);
    }
    if (tempLeftDenom == 1 && tempRightDenom == 1 && tempLeftNumer != 0 && tempRightNumer != 0)
    {
        int num = tempLeftNumer + tempRightNumer;
        return Rational (num, 1);
    }
    if (tempLeftNumer > tempLeftDenom || tempRightNumer > tempRightDenom)
    {
        if (tempLeftNumer < 0 && tempRightNumer < 0)
        {
            int commonDenom = lcm(tempLeftDenom, tempRightDenom);
            tempLeftNumer = (commonDenom / tempLeftDenom) * tempLeftNumer;
            tempRightNumer = (commonDenom / tempRightDenom) * tempRightNumer;
            int newNumer = -tempLeftNumer + -tempRightNumer;
            return Rational(newNumer, commonDenom);
        }
        else
        {
            int commonDenom = lcm(tempLeftDenom, tempRightDenom);
            tempLeftNumer = (commonDenom / tempLeftDenom) * tempLeftNumer;
            tempRightNumer = (commonDenom / tempRightDenom) * tempRightNumer;
            int newNumer = tempLeftNumer + tempRightNumer;
            return Rational(newNumer, commonDenom);
        }
    }
    if (tempLeftNumer < 0 && tempRightNumer < 0)
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom) * tempLeftNumer;
        tempRightNumer = (commonDenom / tempRightDenom) * tempRightNumer;
        int newNumer = -tempLeftNumer - tempRightNumer;
        int newDenom = commonDenom;
        int newCommonDenom = gcd(newNumer, newDenom);
        newNumer = newNumer / newCommonDenom;
        newDenom = newDenom / newCommonDenom;
        return Rational(-newNumer, newDenom);
    }
    if (tempLeftNumer == 0 || tempRightNumer == 0)
    {
        if (tempLeftNumer == 0)
        {
            return Rational(tempRightNumer, tempRightDenom);
        }
        if (tempRightNumer == 0)
        {
            return Rational(tempLeftNumer, tempLeftDenom);
        }
    }
    else
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom) * tempLeftNumer;
        tempRightNumer = (commonDenom / tempRightDenom) * tempRightNumer;
        int newNumer = tempLeftNumer + tempRightNumer;
        int newDenom = commonDenom;
        int newCommonDenom = gcd(newNumer, newDenom);
        newNumer = newNumer / newCommonDenom;
        newDenom = newDenom / newCommonDenom;
        return Rational(newNumer, newDenom);
    }
}
// Pre- Nothing
// Post- Overloads the + operator for ints on the LHS and the Rational class on the RHS
double operator + (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left + rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (left + rightint);
    }
    return (left + (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the + operator for ints on the RHS and the Rational class on the LHS
double operator + (Rational& left, int right)
{
    int leftint = 0;
    int templeftDenom = left.denominator;
    int templeftNumer = left.numerator;
    if (templeftDenom == 1 && templeftNumer != 0)
    {
        leftint = templeftNumer;
        return (leftint + right);
    }
    if (templeftDenom == 0 || templeftNumer == 0)
    {
        leftint = 0;
        return (leftint + right);
    }
    return ((static_cast<double>(templeftNumer) / templeftDenom) + right);
}
// Pre- Nothing
// Post- Overloads the - operator for the rational class
Rational Rational::operator - (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;
    if (tempLeftNumer == 0 && tempRightNumer == 0)
    {
        return Rational(0,0);
    }
    if (tempLeftNumer == 0 || tempRightNumer == 0)
    {
        if (tempLeftNumer == 0)
        {
            return Rational(-tempRightNumer, tempRightDenom);
        }
        if (tempRightNumer == 0)
        {
            return Rational(tempLeftNumer, tempLeftDenom);
        }
    }
    if (tempLeftDenom == 1 && tempRightDenom == 1)
    {
        int num = tempLeftNumer - tempRightNumer;
        return Rational (num, 1);
    }
    if (tempLeftNumer > tempLeftDenom || tempRightNumer > tempRightDenom)
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom) * tempLeftNumer;
        tempRightNumer = (commonDenom / tempRightDenom) * tempRightNumer;
        int newNumer = tempLeftNumer - tempRightNumer;

        return Rational(newNumer, commonDenom);
    }
    else
    {
        int commonDenom = lcm(tempLeftDenom, tempRightDenom);
        tempLeftNumer = (commonDenom / tempLeftDenom) * tempLeftNumer;
        tempRightNumer = (commonDenom / tempRightDenom) * tempRightNumer;
        int newNumer = tempLeftNumer - tempRightNumer;
        int newDenom = commonDenom;
        int newCommonDenom = gcd(newNumer, newDenom);
        newNumer = newNumer / newCommonDenom;
        newDenom = newDenom / newCommonDenom;

        return Rational(newNumer, newDenom);
    }
}
// Pre- Nothing
// Post- Overloads the - operator for ints on the LHS and the Rational class on the RHS
double operator - (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left - rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (left - rightint);
    }
    return (left - (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the - operator for ints on the RHS and the Rational class on the LHS
double operator - (Rational& left, int right)
{
    int leftint = 0;
    int templeftDenom = left.denominator;
    int templeftNumer = left.numerator;
    if (templeftDenom == 1 && templeftNumer != 0)
    {
        leftint = templeftNumer;
        return (leftint - right);
    }
    if (templeftDenom == 0 || templeftNumer == 0)
    {
        leftint = 0;
        return (leftint - right);
    }
    return ((static_cast<double>(templeftNumer) / templeftDenom) - right);
}
// Pre- Nothing
// Post- Overloads the * operator for the rational class
Rational Rational::operator * (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;

    if (tempLeftNumer == 0 || tempRightNumer == 0)
    {
        return Rational(0 , 0);
    }
    else
    {
    int newNumer = tempLeftNumer * tempRightNumer;
    int newDenom = tempLeftDenom * tempRightDenom;
    int newCommonDenom = gcd(newNumer, newDenom);
    newNumer = newNumer / newCommonDenom;
    newDenom = newDenom / newCommonDenom;
    return Rational(newNumer, newDenom);
    }
}
// Pre- Nothing
// Post- Overloads the * operator for ints on the LHS and the Rational class on the RHS
double operator * (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left * rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (left * rightint);
    }
    return (left * (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the * operator for ints on the RHS and the Rational class on the LHS
double operator * (Rational& left, int right)
{
    int leftint = 0;
    int templeftDenom = left.denominator;
    int templeftNumer = left.numerator;
    if (templeftDenom == 1 && templeftNumer != 0)
    {
        leftint = templeftNumer;
        return (leftint * right);
    }
    if (templeftDenom == 0 || templeftNumer == 0)
    {
        leftint = 0;
        return (leftint * right);
    }
    return ((static_cast<double>(templeftNumer) / templeftDenom) * right);
}
// Pre- Nothing
// Post- Overloads the / operator for the rational class
Rational Rational::operator / (const Rational& right) const
{
    int tempLeftDenom = denominator;
    int tempRightDenom = right.denominator;
    int tempLeftNumer = numerator;
    int tempRightNumer = right.numerator;

    if (tempLeftNumer == 0 && tempRightNumer == 0)
    {
        std::cout << "Error, Divisible by zero!" << std::endl;
    }

    if (tempLeftNumer == 0 || tempRightNumer == 0)
    {
        if (tempLeftNumer == 0)
        {
            return Rational (0, 0);
        }
        if (tempRightNumer == 0)
        {
            std::cout << "Error, Divisible by zero!" << std::endl;
        }
    }
    else
    {
    int newNumer = tempLeftNumer * tempRightDenom;
    int newDenom = tempLeftDenom * tempRightNumer;
    int newCommonDenom = gcd(newNumer, newDenom);
    newNumer = newNumer / newCommonDenom;
    newDenom = newDenom / newCommonDenom;
    if (newDenom < 0)
    {
        newDenom = abs(newDenom);
        newNumer = -newNumer;
    }
    return Rational(newNumer,newDenom);
    }
}
// Pre- Nothing
// Post- Overloads the / operator for ints on the LHS and the Rational class on the RHS
double operator / (int left, Rational& right)
{
    int rightint = 0;
    int tempRightDenom = right.denominator;
    int tempRightNumer = right.numerator;
    if (tempRightDenom == 1 && tempRightNumer != 0)
    {
        rightint = tempRightNumer;
        return (left / rightint);
    }
    if (tempRightDenom == 0 || tempRightNumer == 0)
    {
        rightint = 0;
        return (rightint);
    }
    return (left / (static_cast<double>(tempRightNumer) / tempRightDenom));
}
// Pre- Nothing
// Post- Overloads the / operator for ints on the RHS and the Rational class on the LHS
double operator / (Rational& left, int right)
{
    int leftint = 0;
    int templeftDenom = left.denominator;
    int templeftNumer = left.numerator;
    if (templeftDenom == 1 && templeftNumer != 0)
    {
        leftint = templeftNumer;
        return (leftint / right);
    }
    if (templeftDenom == 0 || templeftNumer == 0)
    {
        leftint = 0;
        return (leftint);
    }
    return ((static_cast<double>(templeftNumer) / templeftDenom) / right);
}

// TODO: Make this print integers when the denominator is 1.
std::ostream&
operator<<(std::ostream& os, Rational r)
{
    if (r.den()== 1)
    {
        int numerator = r.num();
        return os << numerator;
    }
    if (r.den() == 0 || r.num() == 0)
    {
        return os << 0;
    }

    else
        return os << r.num() << '/' << r.den();
}


// TODO: Make this read integer values if no '/' is given as a separator.
// You may assume that there is no space between the numerator and the
// slash. Hint, find and read the reference documentation for istream::peek().
std::istream&
operator>>(std::istream& is, Rational& r)
{

    int p, q;
    char c;
    c = std::cin.peek();
    is >> p >> c >> q;
    if (!is)
        return is;

    // Require that the divider to be a '/'.
    if (c != '/')
    {
        return is;
    }
    // Make sure that we didn't read p/0.
    if (q == 0)
    {
        is.setstate(std::ios::failbit);
        return is;
    }
    r = Rational(p, q);
    return is;
}
