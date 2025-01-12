#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

const int NUM_THREADS = 10;
const int NUM_OPERATIONS = 1000;

std::vector<int> vec;
std::mutex mtx;  // 加入互斥鎖

void producer(int id) {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        std::lock_guard<std::mutex> lock(mtx);  // 加鎖保護 vector
        vec.push_back(i);
    }
}

int main() {
    std::vector<std::thread> threads;

    // 創建多個執行緒
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(producer, i);
    }

    // 等待所有執行緒完成
    for (auto& th : threads) {
        th.join();
    }

    std::cout << "Vector size: " << vec.size() << std::endl;

    return 0;
}
