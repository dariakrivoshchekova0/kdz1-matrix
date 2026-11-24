#include <stdexcept>
#include "matrix/stack_matrix.hpp"

StackMatrix::StackMatrix() : data_{} {} // нули

StackMatrix::StackMatrix(Elem fill){
    data_.fill(fill);
}
    
Elem StackMatrix::at(std::size_t r, std::size_t c) const {
    if (r >= kStackN || c >= kStackN) {
        throw std::out_of_range("Index out of range");
    }
    return data_[r * kStackN + c];
}
Elem& StackMatrix::at(std::size_t r, std::size_t c){
    if (r >= kStackN || c >= kStackN) {
        throw std::out_of_range("Index out of range");
    }
    return data_[r * kStackN + c];
}
    
// --- операции, принимающие по ССЫЛКЕ
StackMatrix StackMatrix::addRef(const StackMatrix& a, const StackMatrix& b){
    StackMatrix add_result;
    for (std::size_t i = 0; i < kStackN * kStackN; ++i){
        add_result.data_[i] = a.data_[i] + b.data_[i];
    }
    return add_result;      
}
StackMatrix StackMatrix::mulRef(const StackMatrix& a, const StackMatrix& b){
    StackMatrix mul_result;
    for (std::size_t r = 0; r < kStackN; ++r) {
        for (std::size_t c = 0; c < kStackN; ++c) {
            for (std::size_t k = 0; k < kStackN; ++k) {
                mul_result.data_[r * kStackN + c] += a.data_[r * kStackN + k] * b.data_[k * kStackN + c];
            }
        }
    }
    return mul_result;   
}
    
// --- те же операции, принимающие по ЗНАЧЕНИЮ
StackMatrix StackMatrix::addVal(StackMatrix a, StackMatrix b){
    StackMatrix add_result;
    for (std::size_t i = 0; i < kStackN * kStackN; ++i){
        add_result.data_[i] = a.data_[i] + b.data_[i];
    }
    return add_result;  
}
StackMatrix StackMatrix::mulVal(StackMatrix a, StackMatrix b){
    StackMatrix mul_result;
    for (std::size_t r = 0; r < kStackN; ++r) {
        for (std::size_t c = 0; c < kStackN; ++c) {
            for (std::size_t k = 0; k < kStackN; ++k) {
                mul_result.data_[r * kStackN + c] += a.data_[r * kStackN + k] * b.data_[k * kStackN + c];
                }
            }
        }
    return mul_result;   
}

// --- работа с коллекцией
StackMatrix StackMatrix::sumAll(const std::vector<StackMatrix>& ms){
    StackMatrix res;
    for (const StackMatrix& m : ms){
        for (std::size_t i = 0; i < kStackN * kStackN; ++i){
            res.data_[i] += m.data_[i];
        }
    }
    return res;
}