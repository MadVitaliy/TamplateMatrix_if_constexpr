#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <type_traits>
#include <typeinfo> 



template <typename T, size_t N, size_t M>
class Matrix {
    template <typename T2, size_t N, size_t M>friend class Matrix;
    template <typename T2, size_t M, size_t M2>friend class Matrix;
    template <typename T2, size_t N2, size_t M2>friend class Matrix;
    //T2, N2, M2

private:
    class Row;

    std::array<T, N* M> m_matrix;
    std::array<Row, N> m_rows;
public:
    
    class Row
    {
    private:
        T* mp_start = nullptr;
    public:
        //explicit Row(T* ip_start) : mp_start(ip_start) {}
        //~Row() {}
        constexpr void setPointer(T* ip_start);

        constexpr T& operator[](size_t index);
    };

    Matrix() noexcept;
    ~Matrix() = default;

    //operation with scalars
    template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
    constexpr auto operator+ (const T2 add);

    template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
    constexpr auto operator- (const T2 add);

    template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
    constexpr auto operator* (const T2 add);

    template <typename T2, typename = std::enable_if_t<std::is_arithmetic_v<T2>>>
    constexpr  auto operator/ (const T2 add);

    //template <typename T2>
    //friend auto operator= (const T2 add);

    //unitary operation 
    constexpr  Matrix<T, N, M>& operator++ (); //prefix

    constexpr Matrix<T, N, M> operator++ (int); //postfix

    constexpr  Matrix<T, N, M>& operator-- (); //prefix

    constexpr Matrix<T, N, M> operator-- (int); //postfix

    //binary operation between matrix
    template <typename T2>
    auto operator+ (const Matrix<T2, N, M>& add);

    template <typename T2>
    auto operator- (const Matrix<T2, N, M>& sub);

    template<typename T2, size_t M2>
    auto operator* (const Matrix<T2, M, M2>& mult);

    //boolean
    template<typename T2, size_t N2, size_t M2>
    int operator ==(const Matrix<T2, N2, M2>& i_matrix);


    constexpr Matrix<T, N, M>& operator= (const Matrix<T, N, M>& copy);


    //mathods

    constexpr size_t Height() const;
    constexpr size_t Width() const;

    template <typename = std::enable_if_t<N == M>>
    constexpr T  Determinant() const;

    Matrix<T, M, N> Transpose();

    template <typename T0, size_t N0, size_t M0>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T0, N0, M0>& out);

    Row& operator[] (size_t row) 
    {
        return m_rows[row]; //now index can be chacked and exception can be thrown if row < N
    }

};

template <typename T, size_t N, size_t M>
constexpr void Matrix<T, N, M>::Row::setPointer(T* ip_start)
{
    mp_start = ip_start;
}

template <typename T, size_t N, size_t M>
constexpr T& Matrix<T, N, M>::Row::operator[](size_t index)
{
    return *(mp_start + index);  //now index can be chacked and exception can be thrown if index < M
}

template <typename T, size_t N, size_t M>
Matrix<T, N, M>::Matrix() noexcept
{
    m_matrix.fill(0);
    T* p_rawData = m_matrix.data();
    std::cout << "Construcor Matrix<" << typeid(T).name()
        << "," << N << "," << M << ">" << std::endl;

    for (size_t i = 0; i < N; i++)
    {
        //  m_raws = Row(p_rawData + i);
        m_rows[i].setPointer(p_rawData + i * M);
    }
};

template <typename T, size_t N, size_t M>
constexpr size_t Matrix<T, N, M>::Height() const
{
    return N;
}
template <typename T, size_t N, size_t M>
constexpr size_t Matrix<T, N, M>::Width() const
{
    return M;
}

template <typename T, size_t N, size_t M>
template <typename>
constexpr T  Matrix<T, N, M>::Determinant() const
{
    if constexpr (N == 1)
    {
        std::cout << "Determinant for N=M = 1\n";
        //return (m_matrix[0] < 0 ? (-m_matrix[0]) : m_matrix[0]);
        return  m_matrix[0];
    }
    else if constexpr (N == 2)
    {
        std::cout << "Determinant for N=M = 2\n";
        return m_matrix[0] * m_matrix[3] - m_matrix[1] * m_matrix[2];
    }
    else if constexpr (N == 3)
    {
        std::cout << "Determinant for N=M = 3\n";
        return (m_matrix[0] * m_matrix[4] * m_matrix[8] + 
            m_matrix[1] * m_matrix[5] * m_matrix[6] +
            m_matrix[2] * m_matrix[3] * m_matrix[7]) -
            (m_matrix[0] * m_matrix[5] * m_matrix[7] +
            m_matrix[1] * m_matrix[3] * m_matrix[8] +
            m_matrix[2] * m_matrix[4] * m_matrix[6]);
    }
    else
    {
        std::cout << "Determinant for N=M >= 4 (Has no realisation)\n";
        return  static_cast<T>(0);
    }
}

//operation with scalars
template <typename T, size_t N, size_t M>
template <typename T2, typename>
constexpr auto Matrix<T, N, M>::operator+ (const T2 number)
{
    using resultType = decltype(std::declval<T>() + std::declval<T2>());
    Matrix<resultType, N, M> result;
    for (int i = 0; i < N * M; ++i)
    {
        result.m_matrix[i] = this->m_matrix[i] + number;
    }

    return result;
}

template <typename T, size_t N, size_t M>
template <typename T2, typename>
constexpr auto Matrix<T, N, M>::operator- (const T2 number)
{
    using resultType = decltype(std::declval<T>() - std::declval<T2>());
    Matrix<resultType, N, M> result;
    for (int i = 0; i < N * M; ++i)
    {
        result.m_matrix[i] = this->m_matrix[i] - number;
    }

    return result;
}

template <typename T, size_t N, size_t M>
template <typename T2, typename>
constexpr auto Matrix<T, N, M>::operator* (const T2 number)
{
    using resultType = decltype(std::declval<T>()* std::declval<T2>());;
    Matrix<resultType, N, M> result;
    for (int i = 0; i < N * M; ++i)
    {
        result.m_matrix[i] = this->m_matrix[i] * number;
    }

    return result;
}

template <typename T, size_t N, size_t M>
template <typename T2, typename>
constexpr auto Matrix<T, N, M>::operator/ (const T2 number)
{
    using resultType = decltype(std::declval<T>() / std::declval<T2>());
    Matrix<resultType, N, M> result;
    for (int i = 0; i < N * M; ++i)
    {
        result.m_matrix[i] = this->m_matrix[i] / number;
    }

    return result;
}

//template <typename T2>
//auto operator= (const T2 number);


//unitary operation 
template <typename T, size_t N, size_t M>
constexpr Matrix<T, N, M>& Matrix<T, N, M>::operator++ () ////prefix
{
    for (int i = 0; i < N * M; ++i)
    {
        this->m_matrix[i]++;
    }

    return *this;
}

template <typename T, size_t N, size_t M>
constexpr Matrix<T, N, M> Matrix<T, N, M>::operator++ (int) //postfix
{
    Matrix<T, N, M> temp = *this;
    for (int i = 0; i < N * M; ++i)
    {
        this->m_matrix[i]++;
    }

    return temp;
}

template <typename T, size_t N, size_t M>
constexpr Matrix<T, N, M>& Matrix<T, N, M>::operator-- () //prefix
{
    for (int i = 0; i < N * M; ++i)
    {
        this->m_matrix[i]--;
    }

    return *this;
}

template <typename T, size_t N, size_t M>
constexpr Matrix<T, N, M> Matrix<T, N, M>::operator-- (int) //postfix
{
    Matrix<T, N, M> temp = *this;
    for (int i = 0; i < N * M; ++i)
    {
        this->m_matrix[i]--;
    }

    return temp;
}

//binary operation between matrix
template <typename T, size_t N, size_t M>
template <typename T2>
auto Matrix<T, N, M>::operator+ (const Matrix<T2, N, M>& add)
{
    using resultType = decltype(std::declval<T>() + std::declval<T2>());
    Matrix<resultType, N, M> result;

    for (int i = 0; i < N * M; ++i)
        result.m_matrix[i] = this->m_matrix[i] + add.m_matrix[i];

    return result;
}

template <typename T, size_t N, size_t M>
template <typename T2>
auto Matrix<T, N, M>::operator- (const Matrix<T2, N, M>& sub)
{
    using resultType = decltype(std::declval<T>() - std::declval<T2>());
    Matrix<resultType, N, M> result;

    for (int i = 0; i < N * M; ++i)
        result.m_matrix[i] = this->m_matrix[i] - sub.m_matrix[i];

    return result;
}


template<typename T, size_t N, size_t M>
template<typename T2, size_t M2>
auto Matrix<T, N, M>::operator*(const Matrix<T2, M, M2>& mult)
{
    using resultType = decltype(std::declval<T>()* std::declval<T2>());;

    Matrix<resultType, N, M2> result;

    resultType temp;
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M2; j++)
        {
            temp = 0;
            for (size_t k = 0; k < M; k++)
            {
                temp += this->m_matrix[i * M + k] * mult.m_matrix[k * M2 + j];
            }
            result.m_matrix[i * M2 + j] = temp;
        }
    }
    return result;
}

template <typename T, size_t N, size_t M>
constexpr Matrix<T, N, M>& Matrix<T, N, M>::operator= (const Matrix<T, N, M>& copy)
{
    this->m_matrix = copy.m_matrix;
    return *this;
}

template <typename T, size_t N, size_t M>
template<typename T2, size_t N2, size_t M2>
int Matrix<T, N, M>::operator ==(const Matrix<T2, N2, M2>& i_matrix)
{
    if constexpr (N != N2 || M != M2)
    {
        return 0;
    }
    else
    {
        for (size_t i = 0; i < N*M; i++)
        {
            if (this->m_matrix[i] != i_matrix.m_matrix[i])
                return 0;

        }
        return 1;
    }
}

template <typename T, size_t N, size_t M>
Matrix<T, M, N> Matrix<T, N, M>::Transpose()
{
    if constexpr (N == 1 || M == 1)
    {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < M*N; i++)
            result.m_matrix[i] = this->m_matrix[i];
        
        return result.m_matrix;
    }
    else
    {
        Matrix<T, M, N> result;
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < M; j++)
                result.m_matrix[j * N + i] = this->m_matrix[i * M + j];
            
        return result;
    }
}


template <typename T0, size_t N0, size_t M0>
std::ostream& operator<<(std::ostream& os, const Matrix<T0, N0, M0>& out)
{
    if constexpr (N0 == 1)
    {
        os << "Output for N = 1\n";
        for (size_t j = 0; j < M0; j++)
            os << out.m_matrix[j] << ' ';
        os << '\n';
        return os;
    }
    else if constexpr (M0 == 1)
    {
        os << "Output for M = 1\n";
        for (size_t i = 0; i < N0; i++)
            os << out.m_matrix[i] << '\n';
        return os;
    }
    else
    {
        //  os << "Output for else\n";
        for (size_t i = 0; i < N0; i++)
        {
            for (size_t j = 0; j < M0; j++)
            {
                //auto temp = out.m_matrix[i];
                os << out.m_matrix[i * M0 + j] << ' ';

            }
            os << '\n';
        }
        return os;
    }
}
