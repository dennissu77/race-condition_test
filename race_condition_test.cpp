#include <iostream>
#include <vector>
#include <thread>

const int NUM_THREADS = 10;     // 執行緒數量
const int NUM_OPERATIONS = 1000; // 每個執行緒操作次數

std::vector<int> vec;  // 全域共享的 vector

// 生產者：不斷向 vector 寫入資料
void producer(int id) {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        vec.push_back(i);  // 沒有加鎖，產生競爭條件
    }
}

int main() {
    std::vector<std::thread> threads;

    // 創建多個執行緒
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(producer, i);
    }

    // 等待所有執行緒結束
    for (auto& th : threads) {
        th.join();
    }

    // 印出 vector 的大小（理論上應該是 NUM_THREADS * NUM_OPERATIONS）
    std::cout << "Vector size: " << vec.size() << std::endl;

    return 0;
}
