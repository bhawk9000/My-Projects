#ifndef RATIONAL_HPP_INCLUDED
#define RATIONAL_HPP_INCLUDED

// COPYRIGHT (C) 2017 Ben Hawk (bih9@zips.uakron.edu) All rights reserved.
// rational.hpp: Definition of rational class and its interace.

#include <cstdlib>
#include <iosfwd>
#include <iostream>
#include <stdlib.h>

// Mathematical helper functions.
//
// NOTE: These are defined in rational.cpp.
int gcd(int, int);
int lcm(int, int);

// Represents a rational number. The rational numbers are the set of
// numbers that can be represented as the quotient of two integers.
class Rational
{
  // TODO: Define the following:
  // 1. A default constructor
  // 2. A constructor that takes an integer value
  // 3. A constructor that takes a pair of values

  public:
      // Default Constructor
      Rational(){numerator = 0, denominator = 0;}

      // Constructor that takes an integer value
      Rational(int number) {numerator = number, denominator = 1;}

      // Constructor that takes a pair of values
      Rational(int num, int denom);

      // Returns the numerator.
      int num() const {return numerator;}

      // Returns the denominator
      int den() const {return denominator;}

      // overloaded == operator for Rational class
      bool operator == (const Rational& right) const;

      // overloaded == operator for int on left, and rational class on right
      friend bool operator == (int left, Rational& right);

      // overloaded != operator for Rational class
      bool operator != (const Rational& right) const;

      // overloaded != operator for int on left and Rational class on right
      friend bool operator != (int left, Rational& right);

      // overloaded < operator for rational class
      bool operator < (const Rational& right) const;

      // overloaded < operator for int on left and rational class on right
      friend bool operator < (int left, Rational& right);

      // overloaded > operator for rational class
      bool operator > (const Rational& right) const;

      // overloaded > operator for int on left and rational class on right
      friend bool operator > (int left, Rational& right);

      // overloaded <= operator for rational class
      bool operator <= (const Rational& right) const;

      // overloaded <= operator for int on left and rational class on right
      friend bool operator <= (int left, Rational& right);

      // overloaded >= operator for rational class
      bool operator >= (const Rational& right) const;

      // overloaded >= operator for int on left and rational class on right
      friend bool operator >= (int left, Rational& right);

      // overloaded << operator for Rational class
      friend std::ostream& operator<<(std::ostream&, Rational);

      // overloaded >> operator for Rational class
      friend std::istream& operator>>(std::istream&, Rational&);

      // overloaded + operator for rational class
      Rational operator + (const Rational& right) const;

      // overloaded + operator for int on left and rational class on right
      friend double operator + (int left, Rational& right);

      // overloaded + operator for int on right and rational class on left
      friend double operator + (Rational& left, int right);

      // overloaded - operator for rational class
      Rational operator - (const Rational& right) const;

      // overloaded - operator for int on left and rational class on right
      friend double operator - (int left, Rational& right);

      // overloaded - operator for int on right and rational class on left
      friend double operator - (Rational& left, int right);

      // overloaded * operator for rational class
      Rational operator * (const Rational& right) const;

      // overloaded * operator for int on left and rational class on right
      friend double operator * (int left, Rational& right);

      // overloaded * operator for int on right and rational class on left
      friend double operator * (Rational& left, int right);

      // overloaded / operator for rational class
      Rational operator / (const Rational& right) const;

      // overloaded / operator for int on left and rational class on right
      friend double operator / (int left, Rational& right);

      // overloaded / operator for int on right and rational class on left
      friend double operator / (Rational& left, int right);

  private:
      // private members
    int numerator;
    int denominator;

};




// TODO: Implement support for
// 1. Comparing two rational numbers for equality:
//    - r1 == t2
//    - r1 != r2
// 2. Ordering rational numbers
//    - r1 < r2
//    - r1 > r2
//    - r1 <= r2
//    - r1 >= r2
// 3. The standard arithmetic operators
//    - r1 + r2
//    - r1 - r2
//    - r1 * r2
//    - r1 / r2

// These are provided for you.
//
// NOTE: They are defined in rational.cpp.



#endif // RATIONAL_HPP_INCLUDED
