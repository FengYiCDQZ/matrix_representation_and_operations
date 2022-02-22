/**
 * \file abs_t.h
 * \brief 重载函数absT()
 */
#pragma once
#include <cstdlib>
#include <complex>

    template<typename T> 
inline T AbsT(T const & a)
{
    return std::abs(a);
}

    template<typename T> 
inline T AbsT(std::complex<T> const& a)
{
    return std::abs(a);
}

    template< > 
inline double AbsT(double const & a)
{
    return std::fabs(a);
}
