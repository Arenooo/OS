#pragma once

struct complex
{
        double a, b;

        complex(double a, double b);

        complex();

        double abs();

        complex& operator+(complex& operand);

        complex& operator-(complex& operand);

        complex& operator*(int constant);
};
