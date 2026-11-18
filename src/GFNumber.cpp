#include <cstdint>
#include <stdexcept>
#include <array>

class GFNumber {
    uint8_t data;

    template<bool is_log>
    static constexpr std::array<uint8_t, 512> generate_tables() {
        std::array<uint8_t, 512> temp{};
        uint16_t x = 1;
        for(int i = 0; i < 255; i++) {
            if constexpr (is_log) {
                temp[x] = i;
            } else {
                temp[i] = x;
                temp[i + 255] = x; // Efficiency: never need modulo to calculate log
            }

            // Multiply by alpha, which is 0b10
            x <<= 1;
            if(x & 0x100) {
                // Wraps number back around
                x ^= 0x11d;
            }
        }
        return temp;
    }

    static constexpr auto log = generate_tables<true>();
    static constexpr auto antilog = generate_tables<false>();

    public:
        GFNumber(uint8_t data) : data(data) {}

        GFNumber operator+(const GFNumber& other) const {
            return GFNumber(data ^ other.data);
        }

        GFNumber operator-(const GFNumber& other) const {
            return GFNumber(data ^ other.data);
        }

        GFNumber operator*(const GFNumber& other) const {
            if(data == 0 || other.data == 0) {
                return 0;
            }
            // a * b = alpha^a + alpha^b = alpha ^a+b
            return GFNumber(antilog[log[data] + log[other.data]]);
        }

        GFNumber operator/(const GFNumber& other) const {
            if(data == 0) {
                return 0;
            }
            if(other.data == 0) {
                throw std::runtime_error("Attempted to divide by Zero");
            }
            // a / b = alpha^a - alpha^b = alpha^a-b
            return GFNumber(antilog[log[data] - log[other.data]]);
        }
};
