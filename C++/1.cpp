#include<thread>
#include<mutex>
#include<iostream>
#include<iomanip>
constexpr int COUNT = 1000000;
constexpr int SIZE = 3;
std:: mutex m;
double data[SIZE];
void func(int index1, double value1, int index2, double value2) {
    for (int i = COUNT; i > 0; --i) {
        std::lock_guard<std::mutex>lock(m);
        data[index1] += value1;
        data[index2] += value2;
    }
}
int main() {
    std::thread tho(func, 0, 80, 1, -90);
    std::thread th1(func, 1, 100, 2, -110);
    std::thread th2(func, 2, 120, 0, -130);
    tho.join();
    th1.join();
    th2.join();
    for (int i = 0; i < SIZE; ++i) {
        std::cout << std::setprecision(10) << data[i] << std::endl;
    }
}

