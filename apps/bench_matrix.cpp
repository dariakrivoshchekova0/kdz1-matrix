#include "matrix/heap_matrix.hpp"
#include "matrix/stack_matrix.hpp"
#include "matrix/timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>


static constexpr std::size_t N = 500;

std::uint64_t checksum = 0;

void addReff() {
    const int runs = 10;
    StackMatrix a(1);
    StackMatrix b(2);

    for (int run = 1; run <= runs; ++run) {

        Timer timer;

        StackMatrix result = StackMatrix::addRef(a, b);
        std::uint64_t time = timer.elapsedNs();

        checksum += result.at(0, 0);

        doNotOptimize(result);
        if (run >= 3) {
            csvRow("C", "addRef", N, run, time);
        }
    }
}

void addVall() {
    const int runs = 10;
    StackMatrix a(1);
    StackMatrix b(2);
    for (int run = 1; run <= runs; ++run) {

        Timer timer;

        StackMatrix result =
            StackMatrix::addVal(a, b);

        std::uint64_t time =
            timer.elapsedNs();

        checksum += result.at(0, 0);

        doNotOptimize(result);
        if (run >= 3) {
            csvRow("C", "addVal", N, run, time);
        }
    }
}

void mulReff() {
    const int runs = 10;
    StackMatrix a(1);
    StackMatrix b(2);
    for (int run = 1; run <= runs; ++run) {

        Timer timer;

        StackMatrix result =
            StackMatrix::mulRef(a, b);

        std::uint64_t time =
            timer.elapsedNs();

        checksum += result.at(0, 0);

        doNotOptimize(result);
        if (run >= 3) {
            csvRow("C", "mulRef", N, run , time);
        }
    }
}

void mulVall() {
    const int runs = 10;
    StackMatrix a(1);
    StackMatrix b(2);
    for (int run = 1; run <= runs; ++run) {

        Timer timer;

        StackMatrix result =
            StackMatrix::mulVal(a, b);

        std::uint64_t time =
            timer.elapsedNs();

        checksum += result.at(0, 0);

        doNotOptimize(result);
        if (run >= 3) {
            csvRow("C", "mulVall", N, run , time);
        }
    }
}

void addPtrr(std::size_t n) {     
    const int runs = 10;
    HeapMatrix ha(n, 1);
    HeapMatrix hb(n, 2);

    for (int run = 1; run <= runs; ++run) {

        Timer timer;

        HeapMatrix* result =
            HeapMatrix::addPtr(&ha, &hb);

        std::uint64_t time =
            timer.elapsedNs();

        checksum += result->at(0, 0);

        doNotOptimize(result);

        delete result;
        if (run >= 3) {
            csvRow("C", "addPtrr", N, run , time);   
        }
    }
}

void mulPtrr(std::size_t n) {    
    const int runs = 10;
    for (int run = 1; run <= runs; ++run) {
        HeapMatrix ha(n, 1);
        HeapMatrix hb(n, 2);
        Timer timer;

        HeapMatrix* result =
            HeapMatrix::mulPtr(&ha, &hb);

        std::uint64_t time =
            timer.elapsedNs();

        checksum += result->at(0, 0);

        doNotOptimize(result);

        delete result;
        if (run >= 3) {
            csvRow("C", "mulPtr", N, run , time);    
        }
    }
}

void sumStack() {
    std::vector<StackMatrix> stackMatrices;

    for (int i = 0; i < 20; ++i) {
        stackMatrices.push_back(
            StackMatrix(1)
        );
    }

    const int runs = 10;
    for (int run = 1; run <= runs; ++run) {

        Timer timer;

        StackMatrix result =
            StackMatrix::sumAll(stackMatrices);

        std::uint64_t time =
            timer.elapsedNs();

        checksum += result.at(0, 0);

        doNotOptimize(result);
        if (run >= 3) {
            csvRow("C", "sumStack", kStackN, run , time);   
        }
    }
}

void sumHeap() {
    std::vector<const HeapMatrix*> heapMatrices;
    HeapMatrix ha(N, 1);                                   
    for (int i = 0; i < 20; ++i) {
        heapMatrices.push_back(&ha);
    }

    const int runs = 10;
    for (int run = 1; run <= runs; ++run) {

        Timer timer;

        HeapMatrix* result =
            HeapMatrix::sumAll(heapMatrices);

        std::uint64_t time =
            timer.elapsedNs();

        checksum += result->at(0, 0);

        doNotOptimize(result);

        delete result;
        if (run >= 3) {
            csvRow("C", "sumHeap", N, run, time);      
        }
    }
}

int main() {
    addReff();
    addVall();
    addPtrr(500);
    mulReff();
    mulVall();
    mulPtrr(500);
    sumStack();
    sumHeap();

    addPtrr(1000);
    addPtrr(2000);
    mulPtrr(1000);
    return 0;
}


