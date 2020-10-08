#include <iostream>
#include <vector>
#include "complex.h"

void bubble_sort(std::vector<complex>& vec)
{
        for (int i = 0; i < vec.size() - 1; ++i)
        {
                for (int j = 0; j < vec.size() - i - 1; ++j)
                {
                        if (vec[j].abs() > vec[j + 1].abs())
                                std::swap(vec[j], vec[j + 1]);
                }
        }
}

int main()
{
        int n;

        std::cin >> n;

        std::vector<complex> vec(n);

        for (int i = 0; i < n; ++i)
                std::cin >> vec[i].a >> vec[i].b;

        bubble_sort(vec);

        for (int i = 0; i < n; ++i)
                std::cout << vec[i].a << " + " << vec[i].b << "i\n";


        return 0;
}
