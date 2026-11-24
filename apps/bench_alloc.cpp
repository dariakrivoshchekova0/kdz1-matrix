#include "matrix/heap_matrix.hpp"
#include "matrix/stack_matrix.hpp"
#include "matrix/timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

void Alloc_Stack(long long K) {
    const int runs = 10;

    for (int run = 1; run <= runs; ++run) {

        Timer timer;

        for (int i = 0; i < K; ++i) {
            StackMatrix matrix(1);

            doNotOptimize(matrix.at(0, 0));
        }

        std::uint64_t time =
            timer.elapsedNs() / K;

        if (run >= 3) {
            csvRow("B", "stack", kStackN, run , time);   
    }
}
}

void Alloc_Heap(std::size_t n, long long K) {

    const int runs = 10;

    for (int run = 1; run <= runs; ++run) {

        Timer timer;

        for (int i = 0; i < K; ++i) {
            HeapMatrix matrix(n, 1);

            doNotOptimize(matrix.at(0, 0));
        }

        std::uint64_t time =
            timer.elapsedNs()/K;

        if (run >= 3) {
            csvRow("B", "heap", n, run , time);   
        }
    }
}

int main() {
    Alloc_Stack(20000);

    Alloc_Heap(50,   2000000);
    Alloc_Heap(100,  300000);
    Alloc_Heap(250,  50000);
    Alloc_Heap(500,  15000);
    Alloc_Heap(1000, 3000);
    Alloc_Heap(2000, 1000);

    return 0;
}

