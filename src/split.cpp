#include <iostream>
#include <stdexcept>
#include <memory>

#include <openssl/rand.h>

#include "../include/define.h"
#include "../include/split.h"
#include "../uint256_t/uint256_t.h"



static uint256_t generate_x()
{
    uint8_t buffer[BYTES_PER_256_BIT] = { 0 };
    int8_t code = RAND_bytes(buffer, BYTES_PER_256_BIT);
    if (code != 1)
    {
        throw std::runtime_error("Error!\nOpenSSL function failed!");
    }

    uint256_t x;
    x.from_bytes(buffer);
    return x;
}

static uint256_t calculate_equation(const uint256_t &x, std::shared_ptr<uint256_t[]> coeffs, const uint16_t t)
{
    static const uint256_t modulo = FIELD_MODULO;

    uint256_t result;
    for (uint16_t i = 0; i < t; i++)
    {
        result += coeffs[i] * x.pow(i);
    }

    return result % modulo;
}

static std::shared_ptr<uint256_t[]> create_coeffs(const uint16_t t, const uint256_t &private_key)
{
    std::shared_ptr<uint256_t[]> coeffs(new uint256_t[t]);

    coeffs[0] = private_key;
    for (uint8_t i = 1; i < t; i++)
    {
        uint8_t buffer[BYTES_PER_256_BIT] = { 0 };
        int8_t code = RAND_bytes(buffer, BYTES_PER_256_BIT);
        if (!code)
        {
            throw std::runtime_error("Error!\nOpenSSL function failed!");
        }
        coeffs[i].from_bytes(buffer);
    }

    return coeffs;
}

void split_key(const uint256_t key, const uint16_t n, const uint16_t t)
{
    std::shared_ptr<uint256_t[]> equation_coeffs = create_coeffs(t, key);
    for (uint8_t i = 0; i < n; i++)
    {
        uint256_t x = generate_x();
        // std::cout << std::hex << "X = " << x << "\n";
        uint256_t y = calculate_equation(x, equation_coeffs, t);
        std::cout << std::hex << "(0x" << x << ", 0x" << y << ")\n";
    }
}

int16_t mode_split()
{
    uint256_t private_key;
    uint16_t n, t;

    std::cin >> private_key;
    std::cin >> n >> t;

    if (((n > 2) && (n < 100)) && ((t >= 2) && (t <= n)))
    {
        split_key(private_key, n, t);
    }
    else
    {
        throw std::invalid_argument("Error!\nInvalid N, T parameters were entered!");
        return FAILURE;
    }

    return SUCCESS;
}
