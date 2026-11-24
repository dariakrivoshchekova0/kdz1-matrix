#pragma once
#include <vector>
#include "config.hpp"

class HeapMatrix {
    std::size_t n_;
    Elem* data_;

public:
    explicit HeapMatrix(std::size_t n); // размер — из конструктора
    HeapMatrix(std::size_t n, Elem fill);
    
    ~HeapMatrix(); // освобождает память

    Elem at(std::size_t r, std::size_t c) const;
    Elem& at(std::size_t r, std::size_t c);

    std::size_t size() const { return n_; }
    std::size_t bytes() const { return n_ * n_ * sizeof(Elem); }

    // --- операции, принимающие КОНСТАНТНЫЙ УКАЗАТЕЛЬ
    // возвращают владеющий указатель: вызывающий обязан сделать delete
    static HeapMatrix* addPtr(const HeapMatrix* a, const HeapMatrix* b);
    static HeapMatrix* mulPtr(const HeapMatrix* a, const HeapMatrix* b);

    // --- работа с коллекцией указателей
    static HeapMatrix* sumAll(const std::vector<const HeapMatrix*>& ms);
};
