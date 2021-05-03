#ifndef __UINT256_H__
#define __UINT256_H__

#include <cstdint>
#include <string>


#define BYTES_PER_256_BIT 32
#define HEXDIGITS_PER_256_BIT 64

// class uint256_t;

// uint256_t class (minimal required functionality is implemented)
class uint256_t
{
    private:
        // uint8_t _number[BYTES_PER_256_BIT];

        uint64_t _to_uint64(const uint8_t *const buffer, const uint8_t start_idx) const;
        void _init_from_string(const char *hex_charstring);
        uint8_t _hex2uint8(const char upper, const char lower);
        uint8_t _char2uint8(const char symbol);
        std::string _uint82hex(uint8_t number) const;

    public:
        uint8_t _number[BYTES_PER_256_BIT] = { 0 };

        // Constructors
        uint256_t() = default;
        uint256_t(const uint256_t &rhs) = default;
        uint256_t(uint256_t &&rhs) = default;
        uint256_t(const uint8_t *const bytes, const uint8_t length);
        uint256_t(const char *hex_charstring);
        uint256_t(const std::string &hex_string);
        // uint256_t(const bool &rhs);

        void from_bytes(const uint8_t *const bytes, const uint8_t length);

        operator bool() const;

        // Assignment operator
        uint256_t &operator=(const uint256_t &rhs) = default;
        uint256_t &operator=(uint256_t &&rhs) = default;
        // uint256_t &operator=(const bool &rhs);

        // Logical operator
        bool operator!() const;

        // Comparison operators
        bool operator==(const uint256_t &rhs) const;
        bool operator!=(const uint256_t &rhs) const;
        bool operator>(const uint256_t &rhs) const;
        bool operator<(const uint256_t &rhs) const;
        bool operator>=(const uint256_t &rhs) const;
        bool operator<=(const uint256_t &rhs) const;

        // Arithmetic Operators
        uint256_t operator+(const uint256_t &rhs) const;
        uint256_t &operator+=(const uint256_t &rhs);

        uint256_t operator-(const uint256_t &rhs) const;
        uint256_t &operator-=(const uint256_t &rhs);

        uint256_t operator*(const uint256_t &rhs) const;
        uint256_t &operator*=(const uint256_t &rhs);

        uint256_t operator/(const uint256_t &rhs) const;
        uint256_t &operator/=(const uint256_t &rhs);

        uint256_t operator%(const uint256_t &rhs) const;
        uint256_t &operator%=(const uint256_t &rhs);

        void set_byte(const uint8_t idx, const uint8_t value);
        uint8_t get_byte(const uint8_t idx) const;

        uint256_t pow(const uint16_t power) const;

        // // Increment Operators
        // uint256_t &operator++();
        // uint256_t operator++(int);

        // // Decrement Operators
        // uint256_t &operator--();
        // uint256_t operator--(int);

        // String representation of the value
        std::string to_hexstring() const;
};


std::ostream &operator<<(std::ostream &out, const uint256_t &rhs);
std::istream &operator>>(std::istream &stream, uint256_t &rhs);



#endif