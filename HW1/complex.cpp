#include "complex.h"
#include <iostream>
#include <cmath>
#include <algorithm>

complex::complex(double  a, double b)
{
        this->a = a;
        this->b = b;
}

complex::complex()
{
        this->a = 0;
        this->b = 0;
}

double complex::abs()
{
        return sqrt(a * a + b * b);
}

complex& complex::operator+(complex& operand)
{
        this->a += operand.a;
        this->b += operand.b;

        return *this;
}

complex& complex::operator-(complex& operand)
{
        this->a -= operand.a;
        this->b -= operand.b;

        return *this;
}

complex& complex::operator*(int constant)
{
        this->a *= constant;
        this->b *= constant;

        return *this;
}
