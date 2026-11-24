#include "matrix/heap_matrix.hpp"
#include "matrix/stack_matrix.hpp"
#include "matrix/timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>

void testref() {
    StackMatrix a(1);
    StackMatrix b(2);

    
    for (int run = 1; run < 10; run++) {
        Timer timer;
        StackMatrix result = StackMatrix::mulRef(a, b);
        
        std::uint64_t time = timer.elapsedNs();

        std::uint64_t checksum = 0;

        checksum += result.at(0, 0);

        doNotOptimize(result);
        doNotOptimize(checksum);
        if (run >= 3) {
            csvRow("A1", "mulref", kStackN, run, time);   
        }
    }
}

void testval() {

    StackMatrix a(1);
    StackMatrix b(2);

    
    for (int run = 1; run < 10; run++) {
        Timer timer;
        StackMatrix result = StackMatrix::mulVal(a, b);

        std::uint64_t time = timer.elapsedNs();

        std::uint64_t checksum = 0;

        checksum += result.at(0, 0);

        doNotOptimize(result);
        doNotOptimize(checksum);
        if (run >= 3) {
            csvRow("A1", "mulval", kStackN, run , time);  
        }
    }
}



void StackMemory() {
    std::cout
        << "One matrix: "
        << StackMatrix::bytes()
        << " bytes\n";

    std::cout
        << "Three matrices: "
        << StackMatrix::bytes() * 3
        << " bytes\n";

    std::cout
        << "Five matrices: "
        << StackMatrix::bytes() * 5
        << " bytes\n";
}

void testone() {
    StackMatrix matrix(1);

    matrix.at(0, 0) = 123;


    std::cout
        << "Value = "
        << matrix.at(0, 0)
        << '\n';

    doNotOptimize(matrix);
}

void testthree() {
    StackMatrix a(1);
    StackMatrix b(2);
    StackMatrix result =
        StackMatrix::mulRef(a, b);

    std::cout
        << "result[0][0] = "
        << result.at(0, 0)
        << '\n';

    doNotOptimize(result);
}

void testfive() {
    StackMatrix a(1);
    StackMatrix b(2);

    StackMatrix result =
        StackMatrix::mulVal(a, b);
    std::cout
        << "result[0][0] = "
        << result.at(0, 0)
        << '\n';

    doNotOptimize(result);
}


void testHeap(std::size_t n) {
    for (int run = 1; run < 10; run++) {

        Timer timer;

        HeapMatrix matrix(n, 1);

        std::uint64_t time =
            timer.elapsedNs();

        doNotOptimize(matrix);
        if (run >= 3) {
            csvRow("A4", "heap", n, run , time);
        }
    }
}

int main() {
    testref();
    testval();
    testone();
    testthree();
    testfive();
    testHeap(1000);
    testHeap(2000);
    testHeap(4000);

    return 0;
}

