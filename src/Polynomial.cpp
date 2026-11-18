#include <cstdint>
#include <stdexcept>

class Polynomial {
    uint8_t data;
    uint8_t log[256];
    uint8_t antilog[512];

    public:
        Polynomial(uint8_t data) : data(data) {
            uint16_t x = 1;
            for(int i = 0; i < 256; i++) {
                log[i] = x;
                antilog[x] = i;

                // Multiply by alpha, which is 0b10
                x <<= 1;
                if(x & 0x100) {
                    // Wraps number back around
                    x ^= 0x11d;
                }
            }
        }

        Polynomial operator+(const Polynomial& other) const {
            return data ^ other.data;
        }

        Polynomial operator-(const Polynomial& other) const {
            return data ^ other.data;
        }

        Polynomial operator*(const Polynomial& other) const {
            if(data == 0 || other.data == 0) {
                return 0;
            }
            // a * b = alpha^a + alpha^b = alpha ^a+b
            return antilog[log[data] + log[other.data]];
        }

        Polynomial operator/(const Polynomial& other) const {
            if(data == 0) {
                return 0;
            }
            if(other.data == 0) {
                throw std::runtime_error("Attempted to divide by Zero");
            }
            // a / b = alpha^a - alpha^b = alpha^a-b
            return antilog[log[data] - log[other.data]];
        }
};
