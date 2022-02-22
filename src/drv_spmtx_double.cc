/**
 * \file drv_spmtx_double.cc
 * \brief driver program to test the matrix class based on C++ vector
 */
#include <iostream>
#include "csr_spmtx_vec.h"
#include "dense_mat_vec.h"
#include "abs_t.h"

using namespace std;

/* overload operator -= for vector<T> */
template <typename T>
inline vector<T> &operator-=(vector<T> &out, vector<T> const &vr)
{
    if (vr.size() != out.size())
        cout << "sizes of the vectors are not equal.\n";
    /* for(size_t i=0; i<out.size(); ++i) out[i] -= vr[i]; */
    transform(begin(out), end(out), begin(vr), begin(out), minus<>());
    return (out);
}

int main()
{
    int n{20}, m{20};
    SparseMat<double> sparse_mat(n, m, n * m);
    vector<double> vec1(m);
    generate(begin(vec1), end(vec1),
             [&n, i = -1]() mutable
             {i++; return (0.8*(i-0.5*n)); });

    vector<double> vec2 = sparse_mat * vec1;

    double norm2{0.0}, norm1{0.0};
    DenseMat<double> dense_mat(n, m);
    vector<double> vec4 = dense_mat * vec1;

    for (auto &e : vec4)
        cout << e << "\n";

    vec4 -= vec2;
    for_each(begin(vec4), end(vec4),
             [&norm1](double &x)
             { norm1 = norm1 < AbsT(x) ? AbsT(x) : norm1; });
    norm2 = norm_L2(vec4);
    cout << "Difference for the double case: L1-norm = "
         << norm1 << ", L2-norm= " << norm2 << endl;

    return 0;
}
