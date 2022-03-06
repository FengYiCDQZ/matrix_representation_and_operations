/**
 * \file utilities_sc.h
 */
#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <execution>

/**
 * \brief 计时类
 */
class Timer
{
private:
    ///上一次调用时的时刻
    std::chrono::steady_clock::time_point last;

public:
    /**
     * \brief Construct a new Timer object
     * \details 设置last为当前时刻，便于第一次调用时能够正确计算间隔
     */
    Timer() : last{std::chrono::steady_clock::now()} {}
    /**
     * \brief 打印距上一次调用此函数的时间间隔（ms）
     * \param msg [in] 前缀消息，默认为“Timer diff: ”
     * \return double 距上一次调用此函数的时间间隔（ms）
     */
    double printDiff(const std::string &msg = "Timer diff: ")
    {
        //获取当前时刻
        auto now{std::chrono::steady_clock::now()};
        //计算当前时刻与上一时刻（last）的差值
        std::chrono::duration<double, std::milli> diff{now - last};
        //向stdout输出间隔时间
        std::cout << msg << std::fixed << std::setprecision(2) << diff.count() << " ms\n";
        //重新获取当前时刻，作为下一次调用时的“上一时刻”
        last = std::chrono::steady_clock::now();
        //返回时间间隔，与输出值相同
        return diff.count();
    }
};

/**
 * \brief 将字符串数组转换成std::vector<std::string>
 * \param argc 参数个数
 * \param argv 字符串参数数组
 * \return std::vector<std::string>
 * \details 将字符串逐个push_back进vector中
 */
inline std::vector<std::string> Arguments(int argc, char *argv[])
{
    std::vector<std::string> res;
    for (int i = 0; i != argc; ++i)
        res.push_back(argv[i]);
    return res;
}

// 输出进度条
inline void ProgressBar(int n)
{
    if (n == 0)
        return;
    else if (n == 1)
    {
        std::cout << "\n ";
    }
    else if (n < 11)
    {
        std::cout << "\b\b\b";
    }
    else
    {
        std::cout << "\b\b\b\b";
    }
    std::cout << "> " << n << "%";

    std::cout.flush();
}
