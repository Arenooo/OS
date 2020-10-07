#pragma once

struct complex 
{
	int a, b;

	complex(int a, int b);

	complex();

	int abs();

	complex& operator+(complex& operand);

	complex& operator-(complex& operand);

	complex& operator*(int constant);
};
