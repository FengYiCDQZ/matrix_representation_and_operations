/**
 * \file drv_spmtx_zplx.cc
 * \brief 测试矩阵抽象类
 */

#include <iostream>

#include "csr_spmtx_vec.h"
#include "dense_mat_vec.h"
#include "abs_t.h"

using namespace std;

/* 为vector<T>重载 operator -= */ 
    template<typename T>
inline vector<T>& operator -=(vector<T> &out, vector<T> const& vr) 
{
    assert (vr.size() == out.size());
    /* 另外一种实现方式是直接采用for循环：for(size_t i=0; i<out.size(); ++i) out[i] -= vr[i];*/ 
    transform(begin(out), end(out), begin(vr), begin(out), minus<>());
    return (out);
}

int main()
{
    using ZPLX = complex<double>;
    int n{20}, m{20};
    SparseMat<ZPLX > sparse_mat(n, m, n*m);
    vector<ZPLX> vec1(m) ;
    generate(begin(vec1), end(vec1), 
            [&n, i=-1]() mutable {i++; return ZPLX(0.8*(i-0.5*n), i); } );

    vector< ZPLX > vec2 = sparse_mat*vec1;
    double norm2, norm1;
    DenseMat<ZPLX > dense_mat(n, m);
    vector<ZPLX > vec4 = dense_mat*vec1; 

    for(auto&e:vec4) 
        cout<<e<<"\n";

    vec4 -= vec2;
    norm1 = 0.0;
    for_each(begin(vec4), end(vec4), 
            [&norm1](ZPLX &x){ norm1 = norm1< AbsT(x) ? AbsT(x):norm1; } );
    norm2 = norm_L2(vec4);

    cout << "Difference for the ZPLX case: L1-norm = " 
        << norm1 << ", L2-norm= " << norm2<< endl ;

    return 0;
}
