#pragma once
# include <cstdint>

class GFNumber {
    uint8_t data;
    uint8_t log[256];
    uint8_t antilog[512];

    public:
        GFNumber(uint8_t data);

        GFNumber operator+(const GFNumber& other) const;
        GFNumber operator-(const GFNumber& other) const;
        GFNumber operator*(const GFNumber& other) const;
        GFNumber operator/(const GFNumber& other) const;
};
