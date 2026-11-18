#pragma once
# include <cstdint>

class Polynomial {
    uint8_t data;
    uint8_t log[256];
    uint8_t antilog[512];

    public:
        Polynomial(uint8_t data);

        Polynomial operator+(const Polynomial& other) const;
        Polynomial operator-(const Polynomial& other) const;
        Polynomial operator*(const Polynomial& other) const;
        Polynomial operator/(const Polynomial& other) const;
};
