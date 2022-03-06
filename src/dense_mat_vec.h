/**
 * \file dense_mat_vec.h
 * \brief 基于std::vector<T>的稠密阵
 */
#pragma once

#include "innerproduct_vec.h"
#include "init_matrix.h"
#include "abstract_mat.h"

template <typename T>
class DenseMat : public AbstractMat<T>
{
public:
    /**
     * \brief 初始化为随机的对称矩阵
     * \param n [in] 矩阵的行数，rows
     * \param m [in] 矩阵的列数，cols
     * \param l [in] 元素个数
     */
    DenseMat(size_t const n = 0, size_t const m = 0) : AbstractMat<T>(n, m), mtx_elements_(n * m)
    {
        InitMatrixSymetric(this->GetNumberofRows(), this->GetNumberofCols(), this->mtx_elements_);
    }
    
    /**
     * \brief 矩阵左乘列向量
     */
    virtual std::vector<T> operator*(std::vector<T> const &vec) const override;

private:
    // 保存矩阵元素
    std::vector<T> mtx_elements_;
};

/**
 * \brief 矩阵左乘列向量
 * \details n×m的矩阵左乘m×1的列向量
 * \f[\vec{\beta}=A_{n\times m}\cdot \vec{\alpha} \Rightarrow b_{i} = \sum_{j=1}^{m}A_{ij}a_j \f]
 * 矩阵采用每行连续的一维方式储存，\f$A_{ij}:A[i\times\mathrm{m}+j]\f$，\f$m\f$即为cols
 */
template <typename T>
std::vector<T> DenseMat<T>::operator*(std::vector<T> const &vec) const
{
    // 断言：矩阵的列数等于列向量的行数
    assert(vec.size() == this->GetNumberofCols());
    // 初始化结果列向量
    std::vector<T> out(this->GetNumberofRows(), 0);
    //i：[0, rows_)，第i行，亦结果列向量的第i个元素
    for (size_t i = 0; i < this->GetNumberofRows(); i++)
    {
        //pos：第i行行首元素的索引/偏移，即i*cols
        size_t pos = i * this->GetNumberofCols();
        //计算vec和矩阵第i行的内积
        out[i] = std::inner_product(begin(vec), end(vec),
                                    begin(mtx_elements_) + pos, out[i]);
    }
    return out;
}
