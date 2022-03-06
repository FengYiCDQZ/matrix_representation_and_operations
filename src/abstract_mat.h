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
    /**
     * \brief AbstractMat构造函数
     * \param n [in] 矩阵的行数，rows
     * \param m [in] 矩阵的列数，cols
     */
    AbstractMat(size_t const n = 0, size_t const m = 0) : rows_(n), cols_(m){};

    /**
     * \brief 获取矩阵的行数（高度）
     */
    size_t GetNumberofRows() const { return rows_; };

    /**
     * \brief 获取矩阵的列数（宽度）
     */
    size_t GetNumberofCols() const { return cols_; };

    /**
     * \brief 矩阵左乘列向量
     */
    virtual std::vector<T> operator*(std::vector<T> const &vec) const = 0;

    /**
     * \brief 析构函数
     */
    virtual ~AbstractMat(){};

private:
    size_t rows_, cols_;
};
