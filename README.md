

# vector版本

### 錯誤程式  
```
g++ -o race_condition_test race_condition_test.cpp -pthread -O2
```
```
./race_condition_test
```


### fix
```
g++ -o race_condition_fixed race_condition_fixed.cpp -pthread -O2
```
```
./race_condition_fixed
```


## 生產者消費者(vector)版本
### 錯誤程式
```
g++ -o producer_consumer_test producer_consumer_test.cpp -pthread -O2
```
```
./producer_consumer_test
```
<!-- 
## 令一版本比較好比較的錯誤程式
```
g++ -o race_condition_test_updated race_condition_test_updated.cpp -pthread -O2
```
```
./race_condition_test_updated
``` -->


### fix  block版本
```
g++ -std=c++11 -pthread -o producer_consumer_fix producer_consumer_fix.cpp
```
```
./producer_consumer_fix
```

### fix  nonblock版本
```
g++ -o producer_consumer_nonblock producer_consumer_nonblock.cpp -pthread -O2
```
```
./producer_consumer_nonblock
```

---


也可以調整成自適應延遲，來針對使用場景
```
void consumer() {
    int consumed = 0;
    int delay = 1;  // 初始延遲

    while (consumed < NUM_OPERATIONS) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!vec.empty()) {
            vec.pop_back();
            consumed++;
            delay = 1;  // 成功消費後重置延遲
        } else {
            std::this_thread::sleep_for(std::chrono::nanoseconds(delay));
            delay = std::min(delay * 2, 1000);  // 自適應延遲上限 1000ns
        }
    }
}
```
# queue版本
### queue版本  多個生產者多個消費者
```
g++ -o queue_test queue_test.cpp -lpthread
```
```
./queue_test
```


### queue版本 一個生產者一個消費者
```
g++ -std=c++11 -O2 -pthread -o queue_test_one queue_test_one.cpp
```
```
./queue_test_one
```

### fix的  queue版本 一個生產者一個消費者 
```
g++ -std=c++11 -pthread -o queue_test_one_fix queue_test_one_fix.cpp

```
```
./queue_test_one_fix
```



### fix的 block版本（條件變數）  queue版本 一個生產者一個消費者 
```
g++ -std=c++11 -pthread -o queue_fix_block queue_fix_block.cpp

```
```
./queue_fix_block
```