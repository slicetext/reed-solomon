#pragma once

#include "GFNumber.h"
#include <array>
#include <span>

template<int size>
class Polynomial {
    std::array<GFNumber, size> data;

    public:
        Polynomial(std::array<GFNumber, size> data) : data(data) {}

        Polynomial<size> operator*(GFNumber &scalar) const {
            std::array<GFNumber, size> temp = data;
            for(int i = 0; i < size; i++) {
                temp[i] *= scalar;
            }
            return Polynomial(temp);
        }

        Polynomial<size> operator*(std::span<const GFNumber> &other) {
            std::array<GFNumber, size> temp;
        }
};
