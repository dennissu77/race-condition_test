#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

const int NUM_OPERATIONS = 100000;

std::vector<int> vec;
std::mutex mtx;
std::condition_variable cv;  // 條件變數

// 生產者：不斷 push_back
void producer() {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        vec.push_back(i);
        cv.notify_one();  // 通知消費者有資料可用
    }
}

// 消費者：不斷 pop_back
void consumer() {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !vec.empty(); });  // 等待有資料
        vec.pop_back();
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
