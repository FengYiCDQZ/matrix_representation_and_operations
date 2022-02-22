/**
 * \file innerproduct_vec.h
 * \brief 定义一些std::vector<T>没有定义的操作
 */
#pragma once
#include <vector>
#include <complex>
#include <numeric>
#include <cassert>

template <typename T>
inline T dot(std::vector<T> const &v1, std::vector<T> const &v2)
{
    assert(v1.size() == v2.size());
    T result{0};
    result = std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), result);
    return result;
}

template <typename T>
inline std::complex<T> dot(std::vector<std::complex<T>> const &v1,
                           std::vector<std::complex<T>> const &v2)
{
    assert(v1.size() == v2.size());
    std::complex<T> result{std::complex<T>(0, 0)};

    for (size_t i = 0; i < v1.size(); ++i)
        result += v1[i] * conj(v2[i]);
    return result;
}

template <typename T>
inline T norm_L2(std::vector<T> const &vr)
{
    return (sqrt(dot(vr, vr)));
}

template <typename T>
inline T norm_L2(std::vector<std::complex<T>> const &vr)
{
    return (sqrt(real(dot(vr, vr))));
}
