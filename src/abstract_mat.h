/**
 * \file abstract_mat.h
 * \brief 基于C++ std::vector的矩阵抽象类
 */
#pragma once
#include <vector>

template <typename T>
class AbstractMat
{
public:
    AbstractMat(size_t const n = 0, size_t const m = 0) : rows_(n), cols_(m){};

    size_t GetNumberofRows() const { return rows_; };
    size_t GetNumberofCols() const { return cols_; };

    virtual std::vector<T> operator*(std::vector<T> const &vec) const = 0;
    virtual ~AbstractMat(){};

private:
    size_t rows_, cols_;
};
