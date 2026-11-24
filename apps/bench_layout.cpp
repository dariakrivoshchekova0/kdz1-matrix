#include "matrix/layout.hpp"
#include "matrix/timer.hpp"
#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <vector>

void print_offset();

const int count = 5'000'000;

void Naive_layout(std::size_t N) {
    std::vector<Naive> naive(count);
    const int runs = 10;
    for (int i = 0; i < count; ++i) {
        naive[i].b = 1;
    }
    for (int run = 1; run < runs; run++) {
        std::uint64_t sum = 0;

        Timer timer;

        for (int i = 0; i < count; ++i) {
            sum += naive[i].b;
        }

        std::uint64_t naiveTime = timer.elapsedNs();

        doNotOptimize(sum);
        if (run >= 5) {
            csvRow("D", "Naive", N, run, naiveTime);
        }
    }
}

void Packed_layout(std::size_t N) {
    std::vector<Packed> packed(count);
    const int runs = 10;
    for (int i = 0; i < count; ++i) {
        packed[i].b = 1;
    }
    for (int run = 1; run < runs; run++) {
        std::uint64_t sum = 0;

        Timer timer;

        for (int i = 0; i < count; ++i) {
            sum += packed[i].b;
        }

        std::uint64_t packedTime = timer.elapsedNs();

        doNotOptimize(sum);
        if (run >= 5) {
            csvRow("D", "Packed", N, run , packedTime);
        }
    }
}

void Forced_layout(std::size_t N) {
    std::vector<Forced> forced(count);
    const int runs = 10;
    for (int i = 0; i < count; ++i) {
        forced[i].b = 1;
    }
    for (int run = 1; run < runs; run++) {
        std::uint64_t sum = 0;

        Timer timer;

        for (int i = 0; i < count; ++i) {
            sum += forced[i].b;
        }

        std::uint64_t forcedTime = timer.elapsedNs();

        doNotOptimize(sum);
        if (run >= 5) {
            csvRow("D", "Forced", N, run , forcedTime);
        }
    }
}

int main() {
    const std::size_t N = 5000000;
    print_offset();
    Naive_layout(N);
    Packed_layout(N);
    Forced_layout(N);
    return 0;
}

