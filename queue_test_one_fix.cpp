#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <chrono>
#include <atomic>

// 共享資源
std::queue<int> g_queue;       // 使用 std::queue 作為緩衝區
std::mutex g_mtx;              // 互斥鎖，保護 queue 的操作
std::atomic<bool> g_done(false); // 用於標記生產者是否已完成生產

// 生產者：持續地往佇列中推資料
void producer(int total_items, int produce_interval_ms)
{
    for (int i = 0; i < total_items; ++i) {
        {
            // 取得鎖後才能安全地操作 queue
            std::lock_guard<std::mutex> lock(g_mtx);
            g_queue.push(i);
            std::cout << "[Producer] Produced item: " << i << std::endl;
        }

        // 模擬生產耗時
        std::this_thread::sleep_for(std::chrono::milliseconds(produce_interval_ms));
    }

    // 標記生產完成
    g_done.store(true);
    std::cout << "[Producer] Production done." << std::endl;
}

// 消費者：非阻塞輪詢資料，若 queue 為空則暫停片刻再繼續檢查
void consumer(int consume_interval_ms)
{
    while (true) {
        int item = -1;
        bool hasItem = false;

        {
            // 先鎖定後檢查 queue
            std::lock_guard<std::mutex> lock(g_mtx);
            if (!g_queue.empty()) {
                item = g_queue.front();
                g_queue.pop();
                hasItem = true;
            }
        }

        if (hasItem) {
            // 若取到資料則進行消費
            std::cout << "[Consumer] Consumed item: " << item << std::endl;
        } else {
            // 若無資料可消費，檢查是否已經生產完且 queue 也空了
            if (g_done.load()) {
                // 當生產者已完成且 queue 為空，表示可以結束消費者
                std::cout << "[Consumer] No more items. Exiting..." << std::endl;
                break;
            }
        }

        // 非阻塞消費：短暫休息，避免佔用過多 CPU 資源
        //std::this_thread::sleep_for(std::chrono::milliseconds(consume_interval_ms));
    }
}

int main()
{
    // 要生產的總數量
    const int total_items = 10;

    // 生產者生產間隔 (毫秒)
    const int produce_interval_ms = 200;

    // 消費者檢查間隔 (毫秒)
    const int consume_interval_ms = 100;

    // 建立執行緒
    std::thread producer_thread(producer, total_items, produce_interval_ms);
    std::thread consumer_thread(consumer, consume_interval_ms);

    // 等待執行緒結束
    producer_thread.join();
    consumer_thread.join();

    std::cout << "[Main] Program finished." << std::endl;
    return 0;
}
