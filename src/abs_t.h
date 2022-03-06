/**
 * \file abs_t.h
 * \brief 重载函数absT()
 */
#pragma once
#include <cstdlib>
#include <complex>

/**
 * \brief 一般的绝对值函数
 */
template <typename T>
inline T AbsT(T const &a)
{
    return std::abs(a);
}

/**
 * \brief 复数的绝对值函数
 */
template <typename T>
inline T AbsT(std::complex<T> const &a)
{
    return std::abs(a);
}

/**
 * \brief 双精度浮点数（duoble）的绝对值函数
 */
template <>
inline double AbsT(double const &a)
{
    return std::fabs(a);
}
