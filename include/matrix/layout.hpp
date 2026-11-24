#pragma once
#include <cstddef>
#include <cstdint>

struct Naive {
    bool a;
    std::uint64_t b;
    std::uint32_t c;
    char d;
    std::uint64_t e;
};

struct Packed {            // от больших к меньшим
    std::uint64_t b;
    std::uint64_t e;
    std::uint32_t c;
    bool a;
    char d;
};

#pragma pack(push, 1)
struct Forced {            // Naive без выравнивания
    bool a;
    std::uint64_t b;
    std::uint32_t c;
    char d;
    std::uint64_t e;
};
#pragma pack(pop)

void print_offset();

static_assert(sizeof(Naive)  == 32, "Naive");
static_assert(sizeof(Packed) == 24, "Packed");
static_assert(sizeof(Forced) == 22, "Forced");

std::uint64_t sumNaive(const Naive* p, std::size_t n);
std::uint64_t sumPacked(const Packed* p, std::size_t n);
std::uint64_t sumForced(const Forced* p, std::size_t n);