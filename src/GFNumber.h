#pragma once
# include <cstdint>

class GFNumber {
    uint8_t data;

    public:
        GFNumber(uint8_t data);

        GFNumber operator+(const GFNumber& other) const;
        GFNumber operator-(const GFNumber& other) const;
        GFNumber operator*(const GFNumber& other) const;
        GFNumber operator/(const GFNumber& other) const;
};
