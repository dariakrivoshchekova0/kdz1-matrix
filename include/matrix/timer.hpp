#pragma once
#include <chrono>
#include <cstddef>
#include <iostream>
#include <cstdio>


class Timer {
    using Clock = std::chrono::steady_clock;
    Clock::time_point start_;
public:
    Timer() : start_(Clock::now()) {}
    void reset() { start_ = Clock::now(); }
    std::int64_t elapsedNs() const {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start_).count();
    }
};  

template <typename T>
inline void doNotOptimize(T const& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

inline const char* buildType() {
#ifdef NDEBUG
    return "Release";
#else
    return "Debug";
#endif
}

inline void csvRow(const char* experiment, const char* impl, std::size_t n,
                   int run, long long ns) {
    std::cout << experiment << ',' << impl << ',' << n  << ',' << buildType() << ',' << run << ',' << ns << '\n';
}


