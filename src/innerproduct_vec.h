/**
 * \file innerproduct_vec.h
 * \brief 定义一些std::vector<T>没有定义的操作
 */
#pragma once
#include <vector>
#include <complex>
#include <numeric>
#include <cassert>

/**
 * \brief 计算两实向量（std::vector）的内积
 * \param v1 [in] 向量1
 * \param v2 [in] 向量2
 * \return T v1·v2内积的结果
 * \details 要求两向量长度相同
 * \f[\vec{\alpha}\cdot\vec{\beta}=\sum_{i=1}^{n}a_ib_i\f]
 */
template <typename T>
inline T dot(std::vector<T> const &v1, std::vector<T> const &v2)
{
    //断言：两向量长度相等
    assert(v1.size() == v2.size());
    T result{0};
    // std::inner_product：计算内积
    result = std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), result);
    return result;
}

/**
 * \brief 计算两复向量（std::vector）的内积
 * \param v1 [in] 向量1
 * \param v2 [in] 向量2
 * \return T v1·v2内积的结果
 * \details 要求两向量长度相同，复数内积计算时，其中一个向量应取共轭
 * \f[\vec{\alpha}\cdot\vec{\beta}=\sum_{i=1}^{n}a_i\bar{b_i}\f]
 */
template <typename T>
inline std::complex<T> dot(std::vector<std::complex<T>> const &v1,
                           std::vector<std::complex<T>> const &v2)
{
    assert(v1.size() == v2.size());
    std::complex<T> result{std::complex<T>(0, 0)};

    for (size_t i = 0; i < v1.size(); ++i)
        //复数计算内积时，为第一个数乘上第二个数的共轭
        result += v1[i] * conj(v2[i]);
    return result;
}

/**
 * \brief 计算实向量的L2范数（到原点距离）
 * \param vr [in] 待计算L2范数的向量
 * \return T 向量vr的L2范数
 */
template <typename T>
inline T norm_L2(std::vector<T> const &vr)
{
    return (sqrt(dot(vr, vr)));
}

/**
 * \brief 计算复向量的L2范数（到原点距离）
 * \param vr [in] 待计算L2范数的向量
 * \return T 向量vr的L2范数
 */
template <typename T>
inline T norm_L2(std::vector<std::complex<T>> const &vr)
{
    //对于复向量vr，dot(vr, vr)返回结果为一复数，理论上该复数为一实数（虚部为0）
    return (sqrt(real(dot(vr, vr))));
}
