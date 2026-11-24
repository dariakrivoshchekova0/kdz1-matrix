#include <stdexcept>
#include <algorithm>
#include "matrix/heap_matrix.hpp"

HeapMatrix::HeapMatrix(std::size_t n)
    :n_(n),
    data_(nullptr) 
    {
    if (n==0){
        throw std::invalid_argument("Invalid argument");
        }
    data_=new Elem[n*n]();
    } // размер — из конструктора
HeapMatrix::HeapMatrix(std::size_t n, Elem fill)
    :n_(n),
    data_(nullptr) 
    {
    if (n==0){
        throw std::invalid_argument("Invalid argument");
        }
    data_=new Elem[n*n];
    std::fill(data_, data_ + n_ * n_, fill);
    }
    
HeapMatrix::~HeapMatrix(){
    delete[] data_;
} // освобождает память

Elem HeapMatrix::at(std::size_t r, std::size_t c) const {
    if (r >= n_ || c >= n_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[r * n_ + c];
}
Elem& HeapMatrix::at(std::size_t r, std::size_t c){
    if (r >= n_ || c >= n_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[r * n_ + c];
}

// --- операции, принимающие КОНСТАНТНЫЙ УКАЗАТЕЛЬ
// возвращают владеющий указатель: вызывающий обязан сделать delete
HeapMatrix* HeapMatrix::addPtr(const HeapMatrix* a, const HeapMatrix* b){
    if (!a || !b || a->n_ != b->n_){
        throw std::invalid_argument("Incorrect dimensions");
    }
    HeapMatrix* add_result=new HeapMatrix(a->n_);
    for (std::size_t i = 0; i < a->n_ * a->n_; ++i){
        add_result->data_[i] = a->data_[i] + b->data_[i];
        }
    return add_result;
}
HeapMatrix* HeapMatrix::mulPtr(const HeapMatrix* a, const HeapMatrix* b){
    if (!a || !b || a->n_ != b->n_){
        throw std::invalid_argument("Incorrect dimensions");
    }
    const std::size_t n = a->n_;
    HeapMatrix* mul_result = new HeapMatrix(n);
    for (std::size_t r = 0; r < n; ++r){
        for (std::size_t c = 0; c < n; ++c) {
            for (std::size_t k = 0; k < n; ++k){
                mul_result->data_[r*n + c] += a->data_[r * n + k] * b->data_[k * n + c];
            }
        }        
    }
    return mul_result;
}

// --- работа с коллекцией указателей
HeapMatrix* HeapMatrix::sumAll(const std::vector<const HeapMatrix*>& ms){
    if (ms.empty()){
        throw std::invalid_argument("Vector empty");
    }
    if (ms[0] == nullptr) {
        throw std::invalid_argument("null pointer");
    }
    const std::size_t n = ms[0]->n_;
    for (const HeapMatrix* m : ms)                    
        if (!m || m->n_ != n){ 
            throw std::invalid_argument("Incorrect dimensions");
        } 
    HeapMatrix* res = new HeapMatrix(n);
    for (const HeapMatrix* m : ms)
        for (std::size_t i = 0; i < n * n; ++i)
            res->data_[i] += m->data_[i];
    return res;
}


