# kdz1-matrix
## Сборка

cmake -S . -B build-debug   -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_CXX_FLAGS="-Wall -Wextra" && cmake --build build-debug   -j
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Wall -Wextra" && cmake --build build-release -j


## Запуск

```
./build-debug/apps/bench_limits      # эксперимент A
./build-debug/apps/bench_alloc       # эксперимент B
./build-debug/apps/bench_matrix      # эксперимент C
./build-debug/apps/bench_layout      # эксперимент D
```
# kdz1-matrix
