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
    SparseMat(size_t const n = 0, size_t const m = 0, size_t const l = 0)
        : AbstractMat<T>(n, m), col_indices_(l), row_position_(n + 1), mtx_elements_(l)
    {
        InitSparseMatrixSymetric(this->GetNumberofRows(), this->GetNumberofCols(), this->mtx_elements_,
                                 this->row_position_, this->col_indices_);
    }
    virtual std::vector<T> operator*(std::vector<T> const &in) const override;

private:
    std::vector<size_t> col_indices_;  // 非零元素的列索引
    std::vector<size_t> row_position_; // 各行首元素在列索引数组的位置
    std::vector<T> mtx_elements_;      // 非零元素值
};

template <typename T>
std::vector<T> SparseMat<T>::operator*(std::vector<T> const &vec) const
{
    assert(vec.size() == this->GetNumberofCols());
    std::vector<T> tm(this->GetNumberofRows(), 0);

    for (size_t i = 0; i < this->GetNumberofRows(); i++)
    {
        for (size_t j = row_position_[i]; j < row_position_[i + 1]; j++)
        {
            tm[i] += mtx_elements_[j] * vec[col_indices_[j]];
        }
    }
    return tm;
}
