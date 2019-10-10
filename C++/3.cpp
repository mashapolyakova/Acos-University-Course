#include<thread>
#include<mutex>
#include<iostream>
#include<iomanip>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
std::pair<int, int> foo(int iters, unsigned int id) {
    int suited = 0;
    for (int i = 0; i < iters; ++i) {
        double x = rand_r(&id);
        double y = rand_r(&id);
        x /= RAND_MAX;
        y /= RAND_MAX;
        if (x*x + y*y <= 1) {
            suited += 1;
        }
    }
    std::pair<int, int> ans;
    ans.first = suited;
    ans.second = iters;
    return ans;
}
int main(int argc, char *argv[]) {
    int iters;
    unsigned int processes;
    sscanf(argv[1], "%u", &processes);
    sscanf(argv[2], "%d", &iters);
    int sum = 0;
    for (unsigned int i = 0; i < processes; ++i) {
        auto handle = std::async(std::launch::async, foo, iters, i);
        std::pair<int, int> ans = handle.get();
        //std::cout << ans.first << "\n";
        sum += ans.first;
    }
    double second = iters*processes;
    double first = sum;
    double pi = 4 * first/second;
    printf("%.7g\n",pi);
    
}
