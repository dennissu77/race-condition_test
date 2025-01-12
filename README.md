


## 錯誤程式
```
g++ -o race_condition_test race_condition_test.cpp -pthread -O2
```
```
./race_condition_test
```


# fix
```
g++ -o race_condition_fixed race_condition_fixed.cpp -pthread -O2
```
```
./race_condition_fixed
```


# 生產者消費者======================================
## 錯誤程式
```
g++ -o producer_consumer_test producer_consumer_test.cpp -pthread -O2
```
```
./producer_consumer_test
```


# fix  block版本
```
g++ -std=c++11 -pthread -o producer_consumer_fix producer_consumer_fix.cpp
```
```
./producer_consumer_fix
```

# fix  nonblock版本
```
g++ -o producer_consumer_nonblock producer_consumer_nonblock.cpp -pthread -O2
```
```
./producer_consumer_nonblock
```