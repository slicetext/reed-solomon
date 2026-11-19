#include <cstdint>
#include <stdexcept>
#include <array>

// Helper Log and Antilog table generation at compile time
namespace {
    template<bool is_log>
        constexpr std::array<uint8_t, 512> generate_tables() {
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

    constexpr auto log = generate_tables<true>();
    constexpr auto antilog = generate_tables<false>();
}

class GFNumber {
    uint8_t data;


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
                return GFNumber(0);
            }
            // a * b = antilog(log(a)) * antilog(log(b)) = antilog(log(a) + log(b))
            // Because we have a double length antilog table, if the index wraps past 255 it is still correct
            return GFNumber(antilog[log[data] + log[other.data]]);
        }

        GFNumber operator/(const GFNumber& other) const {
            if(other.data == 0) {
                throw std::domain_error("Attempted to divide by Zero");
            }
            if(data == 0) {
                return GFNumber(0);
            }
            // a / b = antilog(log(a)) / antilog(log(b)) = antilog(log(a) - log(b))
            // Because we have a double length antilog table, I can just add 255
            return GFNumber(antilog[log[data] - log[other.data] + 255]);
        }
};
