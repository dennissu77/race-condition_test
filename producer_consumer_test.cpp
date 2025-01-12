#include <iostream>
#include <vector>
#include <thread>

const int NUM_OPERATIONS = 100000;

std::vector<int> vec;

// 生產者：不斷地 push_back
void producer() {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        vec.push_back(i);  // 沒有加鎖，可能發生競爭條件
    }
}

// 消費者：不斷地 pop_back
void consumer() {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        if (!vec.empty()) {
            vec.pop_back();  // 沒有加鎖，可能發生競爭條件
        }
    }
}

int main() {
    std::thread prod(producer);  // 一個生產者
    std::thread cons(consumer);  // 一個消費者

    prod.join();
    cons.join();

    std::cout << "最終 Vector 大小: " << vec.size() << std::endl;

    return 0;
}
