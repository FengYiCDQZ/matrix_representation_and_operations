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

    template<typename T> 
void InitMatrixSymetric(size_t const rows, size_t const cols, std::vector<T> &arr)
{
    std::mt19937_64 mre(0); 
    std::uniform_real_distribution<double> urd(0.0, 1.0);

    for (size_t i = 0; i < rows; i++) 
        for_each_n(std::execution::seq, arr.begin()+i*cols, i+1, [&urd, &mre](auto& e){ e = urd(mre); } );  

    for (size_t i = 0; i < rows; i++) 
        for (size_t j = i; j < cols; j++) 
        { 
            arr[i*cols + j] = arr[j*cols + i];
        }
}

    template<typename T>
void InitMatrixSymetric(size_t const rows, size_t const cols, std::vector<std::complex<T>> &arr)
{
    std::mt19937_64 mre(0); 
    std::uniform_real_distribution<double> urd(0.0, 1.0);

    for (size_t i = 0; i < rows; i++) 
        for_each_n(std::execution::seq, arr.begin()+i*cols, i+1, 
                [&urd, &mre](auto& e){e = std::complex<T>(urd(mre), 0.3*urd(mre));});  

    for (size_t i = 0; i < rows; i++) 
        for (size_t j = i; j < cols; j++) 
            arr[i*cols + j] = arr[j*cols + i];    
}

    template<typename T> 
void InitSparseMatrixSymetric(size_t const rows, size_t const cols, std::vector<T> &arr, 
        std::vector<size_t> &row_pos, std::vector<size_t> &col_idx)
{
    InitMatrixSymetric(rows, cols, arr);
    size_t rowpos = 0; 
    row_pos[0] = 0;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j <cols; j++) 
        { 
            col_idx[i*cols+j] =  j; 
            rowpos ++;
        }
        row_pos[i+1] = rowpos;
    }
}

    template<typename T>
void InitSparseMatrixSymetric(size_t const rows, size_t const cols, 
        std::vector<std::complex<T>> &arr, std::vector<size_t> &row_pos,
        std::vector<size_t> &col_idx)
{
    InitMatrixSymetric(rows, cols, arr);  
    size_t rowpos = 0; 
    row_pos[0] = 0;
    for (size_t i = 0; i < rows; i++) 
    {
        for (size_t j = 0; j <cols; j++)
        { 
            col_idx[i*cols+j] =  j; 
            rowpos ++;
        }
        row_pos[i+1] = rowpos;
    }
}
