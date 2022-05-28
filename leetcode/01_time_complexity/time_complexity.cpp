/*
 * @Author: sky wcf0118@gmail.com
 * @Date: 2022-05-14 17:15:06
 * @LastEditors: sky wcf0118@gmail.com
 * @LastEditTime: 2022-05-14 17:44:34
 * @FilePath: /comm/leetcode/01_time_complexity/time_complexity.cpp
 * @Description: 以加法指令为例，比较 O(n)、O(n^2) 和 O(nlogn) 时间复杂度，在1s内分别能执行多少次指令
 */
#include <iostream>
#include <chrono>
#include <thread>
#include <map>
using namespace std;
using namespace chrono;

// O(n)
void function1(long long n) {
    long long k = 0;
    for (long long i = 0; i < n; i++) {
        k++;
    }
}

// O(n^2)
void function2(long long n) {
    long long k = 0;
    for (long long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            k++;
        }
    }

}
// O(nlogn)
void function3(long long n) {
    long long k = 0;
    for (long long i = 0; i < n; i++) {
        for (long long j = 1; j < n; j = j*2) { // 注意这里j=1
            k++;
        }
    }
}

int main(int argc, char const *argv[]) {
    long long n; // 数据规模
    int o;//时间复杂度
    while (1) {
        cout << "输入时间复杂度：1-O(n) 2-O(nlogn)3-O(n^2)";
        cin >> o;
        cout << "输入n：";
        cin >> n;
        milliseconds start_time = duration_cast<milliseconds >(
            system_clock::now().time_since_epoch()
        );

        switch(o) {
            case 1:
            {
                function1(n);
                break;
            }
            case 2: 
            {
                function2(n);
                break;
            }
            case 3:
            {
                function3(n);
                break;
            }
            default:
                break;
        }
        // function1(n);
        // function2(n);
        // function3(n);
        
        milliseconds end_time = duration_cast<milliseconds >(
            system_clock::now().time_since_epoch()
        );
        cout << "耗时:" << milliseconds(end_time).count() - milliseconds(start_time).count()
            <<" ms"<< endl;
    }

    return 0;
}
