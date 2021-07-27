#include "Matrix.h"

#include <iostream>
#include <type_traits>


int main()
{
    constexpr int n = 2;
    constexpr int m = 3;

    Matrix<int, n, m> a;
    Matrix<float, n, m> b;
    Matrix<double, m, n> c;


    auto aa = a[0][0];

    std::cout << "----------------------------" << std::endl
        << "a =\n" << a << std::endl
        << "aa = a[0][0] =\n" << aa << std::endl;

    for (size_t i = 0; i < a.Height(); i++)
        for (size_t j = 0; j < a.Width(); j++)
            a[i][j] = 1;
 
    for (size_t i = 0; i < b.Height(); i++)
        for (size_t j = 0; j < b.Width(); j++)
            b[i][j] = static_cast<float>(1.f * ((i + 1) + (j + 5)) / ((i % (j+1)) + 1));

    for (size_t i = 0; i < c.Height(); i++)
        for (size_t j = 0; j < c.Width(); j++)
            c[i][j] = static_cast<double>((i + 1) % (j + 3));

    std::cout << "----------------------------" << std::endl
        << "a =\n" << a << std::endl
        << "b =\n" << b << std::endl
        << "c =\n" << c << std::endl;

    std::cout << "----------------------------" << std::endl
             << "a =\n" << a << std::endl
             << "a++ =\n" << a++ << std::endl
             << "++a =\n" << ++a << std::endl
             << "a + 0.5f =\n" << a+0.5f << std::endl
             << "a - 0.1f =\n" << a - 0.1f << std::endl
             << "a * 2 =\n" << a * 2 << std::endl
             << "a / 2.f =\n" << a / 2.f << std::endl;

    auto temp = a.Transpose();
    std::cout << "----------------------------" << std::endl
        << "a =\n" << a << std::endl
        << "transpose a =\n" << a.Transpose() << std::endl;

    std::cout << "----------------------------" << std::endl
            << "a =\n" << a << std::endl
            << "b =\n" << b << std::endl
            << "a + b =\n" << a + b << std::endl
            << "a - b =\n" << a - b << std::endl;


    for (size_t i = 0; i < a.Height(); i++)
        for (size_t j = 0; j < a.Width(); j++)
            a[i][j] = static_cast<int>((j+i) % (i + 6));

    auto d = c * a;
    std::cout << "----------------------------" << std::endl
           << "a =\n" << a << std::endl
           << "c =\n" << c << std::endl
           << "d = c*a =\n" << d << std::endl;

    std::cout << "----------------------------" << std::endl
        << "Determinant of d: \n" << d.Determinant() << std::endl;
    return 0;
}
