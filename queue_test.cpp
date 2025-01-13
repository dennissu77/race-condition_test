#include <iostream>
#include <queue>
#include <thread>

std::queue<int> q;  // 共用的 std::queue

void producer(int id) {
    for (int i = 0; i < 1000; ++i) {
        q.push(i);  // 不加鎖，直接存取 queue
    }
    std::cout << "Producer " << id << " finished.\n";
}

void consumer(int id) {
    for (int i = 0; i < 1000; ++i) {
        if (!q.empty()) {
            q.pop();  // 不加鎖，直接存取 queue
        }
    }
    std::cout << "Consumer " << id << " finished.\n";
}

int main() {
    std::thread producers[5];
    std::thread consumers[5];

    // 啟動多個生產者執行緒
    for (int i = 0; i < 5; ++i) {
        producers[i] = std::thread(producer, i);
    }

    // 啟動多個消費者執行緒
    for (int i = 0; i < 5; ++i) {
        consumers[i] = std::thread(consumer, i);
    }

    // 等待所有生產者結束
    for (int i = 0; i < 5; ++i) {
        producers[i].join();
    }

    // 等待所有消費者結束
    for (int i = 0; i < 5; ++i) {
        consumers[i].join();
    }

    std::cout << "Final queue size: " << q.size() << std::endl;

    return 0;
}
