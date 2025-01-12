#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

const int NUM_OPERATIONS = 100000;

std::vector<int> vec;
std::mutex mtx;

// 生產者：不斷 push_back
void producer() {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        vec.push_back(i);
    }
}

// 消費者：不斷 pop_back（非阻塞版本）
void consumer() {
    int consumed = 0;
    while (consumed < NUM_OPERATIONS) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!vec.empty()) {
            vec.pop_back();
            consumed++;
        }
        // 防止忙等待過度消耗 CPU，稍微休息一下
        //std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();

    std::cout << "最終 Vector 大小: " << vec.size() << std::endl;

    return 0;
}
