#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

std::queue<int> q;  // 共用的 std::queue

void producer() {
    for (int i = 0; i < 100000; ++i) {
        q.push(i);  // 不加鎖，直接操作 queue
    }
    std::cout << "Producer finished.\n";
}

void consumer() {
    int failed_pops = 0;  // 記錄 pop 時 queue 為空的次數
    for (int i = 0; i < 100000; ) {
        if (!q.empty()) {
            q.pop();  // 不加鎖，直接操作 queue
            ++i;
        } 
    }
    std::cout << "Consumer finished.  " << "\n";
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    std::cout << "Final queue size: " << q.size() << std::endl;

    return 0;
}
