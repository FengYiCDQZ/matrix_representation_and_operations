/**
 * \file init_matrix.h
 * \brief 初始化基于std::vector<T>的矩阵
 */
#pragma once

#include <vector>
#include <algorithm>
#include <execution>
#include <random>
#include <complex>

/**
 * \brief 构造随机对称实矩阵
 * \param rows [in] 矩阵行数
 * \param cols [in] 矩阵列数
 * \param arr [out] 输出vector，大小rows*cols
 */
template <typename T>
void InitMatrixSymetric(size_t const rows, size_t const cols, std::vector<T> &arr)
{
    //std::mt19937_64：一种随机数生成算法/器，Mersenne Twister 19937 generator (64 bit)
    //A Mersenne Twister pseudo-random generator of 64-bit numbers with a state size of 19937 bits.
    //种子seed设为0
    std::mt19937_64 mre(0);
    //产生(0,1)连续均匀分布，重载小括号运算符，接收随机数生成器，返回随机数
    std::uniform_real_distribution<double> urd(0.0, 1.0);

    //生成矩阵的左下角（包含对角线），第i行生成i+1个
    //std::execution::seq：并行策略-不并行
    //arr.begin() + i * cols：第i行行首的迭代器 
    for (size_t i = 0; i < rows; i++)
        for_each_n(std::execution::seq, arr.begin() + i * cols, i + 1, [&urd, &mre](auto &e)
                   { e = urd(mre); });

    //将左下角复制到右上角
    for (size_t i = 0; i < rows; i++)
        for (size_t j = i; j < cols; j++)
        {
            arr[i * cols + j] = arr[j * cols + i];
        }
}

/**
 * \brief 构造随机对称复矩阵
 * \param rows [in] 矩阵行数
 * \param cols [in] 矩阵列数
 * \param arr [out] 输出vector，大小rows*cols
 */
template <typename T>
void InitMatrixSymetric(size_t const rows, size_t const cols, std::vector<std::complex<T>> &arr)
{
    std::mt19937_64 mre(0);
    std::uniform_real_distribution<double> urd(0.0, 1.0);

    for (size_t i = 0; i < rows; i++)
        for_each_n(std::execution::seq, arr.begin() + i * cols, i + 1,
                   [&urd, &mre](auto &e)
                   { e = std::complex<T>(urd(mre), 0.3 * urd(mre)); });

    for (size_t i = 0; i < rows; i++)
        for (size_t j = i; j < cols; j++)
            arr[i * cols + j] = arr[j * cols + i];
}

/**
 * \brief 构造随机行压缩的实矩阵
 * \param rows [in] 矩阵行数
 * \param cols [in] 矩阵列数
 * \param arr [out] 输出vector，大小rows*cols
 * \param row_pos [out] 各行首元素索引
 * \param col_idx [out] 索引元素所在列
 * \details 构造的矩阵按照行压缩的稀疏矩阵格式进行储存，但实际上为满的随机矩阵，并不“稀疏”
 */
template <typename T>
void InitSparseMatrixSymetric(size_t const rows, size_t const cols, std::vector<T> &arr,
                              std::vector<size_t> &row_pos, std::vector<size_t> &col_idx)
{
    //生成随机矩阵arr
    InitMatrixSymetric(rows, cols, arr);
    //当前索引
    size_t rowpos = 0;
    //第0行首非零元素索引一定是0
    row_pos[0] = 0;

    //i：[0,rows)，对于每一个第i行
    for (size_t i = 0; i < rows; i++)
    {
        //j：[0, cols)，对于第i行的每一个第j列
        for (size_t j = 0; j < cols; j++)
        {
            //由于记录了矩阵所有元素，则元素(i,j)索引为i*cols+j，所在列为j
            col_idx[i * cols + j] = j;
            //索引增加1，增加为下一个元素的索引
            rowpos++;
        }
        //下一行的首非零元素索引
        row_pos[i + 1] = rowpos;
    }
}

/**
 * \brief 构造随机行压缩的复矩阵
 * \param rows [in] 矩阵行数
 * \param cols [in] 矩阵列数
 * \param arr [out] 输出vector，大小rows*cols
 * \param row_pos [out] 各行首元素索引
 * \param col_idx [out] 索引元素所在列
 * \details 构造的矩阵按照行压缩的稀疏矩阵格式进行储存，但实际上为满的随机矩阵，并不“稀疏”
 */
template <typename T>
void InitSparseMatrixSymetric(size_t const rows, size_t const cols,
                              std::vector<std::complex<T>> &arr, std::vector<size_t> &row_pos,
                              std::vector<size_t> &col_idx)
{
    InitMatrixSymetric(rows, cols, arr);
    size_t rowpos = 0;
    row_pos[0] = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            col_idx[i * cols + j] = j;
            rowpos++;
        }
        row_pos[i + 1] = rowpos;
    }
}
