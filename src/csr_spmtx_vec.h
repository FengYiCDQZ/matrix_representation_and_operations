/**
 * \file csr_spmtx_vec.h
 * \brief 基于std::vector<T>实现系数矩阵的行压缩格式存储
 */
#pragma once
#include "innerproduct_vec.h"
#include "init_matrix.h"
#include "abstract_mat.h"

template <typename T>
class SparseMat : public AbstractMat<T>
{
public:
    /**
     * \brief 初始化为随机的对称矩阵
     * \param n [in] 矩阵的行数，rows
     * \param m [in] 矩阵的列数，cols
     * \param l [in] 元素个数
     */
    SparseMat(size_t const n = 0, size_t const m = 0, size_t const l = 0)
        : AbstractMat<T>(n, m), col_indices_(l), row_position_(n + 1), mtx_elements_(l)
    {
        InitSparseMatrixSymetric(this->GetNumberofRows(), this->GetNumberofCols(), this->mtx_elements_,
                                 this->row_position_, this->col_indices_);
    }

    /**
     * \brief 矩阵左乘列向量
     */
    virtual std::vector<T> operator*(std::vector<T> const &in) const override;

private:
    std::vector<size_t> col_indices_;  // 非零元素的列索引
    std::vector<size_t> row_position_; // 各行首元素在列索引数组的位置
    std::vector<T> mtx_elements_;      // 非零元素值
};

/**
 * \brief 矩阵左乘列向量
 * \details m×n的矩阵左乘n×1的列向量
 * 这里的矩阵为稀疏矩阵，采用行压缩方式储存
 * \f[\vec{\beta}=A_{n\times m}\cdot \vec{\alpha} \Rightarrow b[i] = \sum_{j=\mathrm{row\_position}[i]}^{\mathrm{row\_position}[i+1]}A[j]a[\mathrm{col\_indices}[j]] \f]
 * 其中A[j]为矩阵的第j个非零元
 */
template <typename T>
std::vector<T> SparseMat<T>::operator*(std::vector<T> const &vec) const
{
    // 断言：矩阵的列数等于列向量的行数
    assert(vec.size() == this->GetNumberofCols());
    // 初始化结果列向量
    std::vector<T> tm(this->GetNumberofRows(), 0);
    //i：[0, rows_)，第i行，亦结果列向量的第i个元素
    for (size_t i = 0; i < this->GetNumberofRows(); i++)
    {
        //j：[row_position_[i], row_position_[i+1])，矩阵当前第i行首非零元素索引
        for (size_t j = row_position_[i]; j < row_position_[i + 1]; j++)
        {
            //mtx_elements_[j]：第j个元素，即公式中的a_ik
            //col_indices_[j]：第j个元素所在列，即公式中的k
            tm[i] += mtx_elements_[j] * vec[col_indices_[j]];
        }
    }
    return tm;
}
