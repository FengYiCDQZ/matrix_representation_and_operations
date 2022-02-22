/**
 * \file dense_mat_vec.h
 * \brief 基于std::vector<T>的稠密阵
 */
#pragma once 

#include "innerproduct_vec.h"
#include "init_matrix.h"
#include "abstract_mat.h"

template<typename T> 
class DenseMat: public AbstractMat<T>
{
    public:
        DenseMat(size_t const n=0, size_t const m=0): 
            AbstractMat<T>(n, m),mtx_elements_(n*m)
    {
        InitMatrixSymetric(this->GetNumberofRows(), this->GetNumberofCols(), this->mtx_elements_);
    }
        virtual std::vector<T> operator*(std::vector<T> const & vec) const override; 

    private:
        // 保存矩阵元素
        std::vector<T> mtx_elements_; 

};

template<typename T> 
std::vector<T> DenseMat<T>::operator*(std::vector<T> const& vec) const 
{
    assert(vec.size() == this->GetNumberofCols() );
    std::vector<T> out(this->GetNumberofRows(), 0);

    for (size_t i = 0; i < this->GetNumberofRows(); i++) 
    {
        size_t pos = i*this->GetNumberofCols();
        out[i] = std::inner_product(begin(vec), end(vec),
                begin(mtx_elements_)+pos, out[i]);
    }
    return out;
}
