#include <iostream>
#include <stdexcept>
#include <memory>

#include <assert.h>

#include <openssl/rand.h>

#include "../include/define.h"
#include "../include/recover.h"
#include "../uint256_t/uint256_t.h"




static uint256_t inverse_modulo(const uint256_t &x, const uint256_t &modulo)
{
    // Fermat's little theorem
    return x.powmod(modulo - 2, modulo);
}

static bool get_point(std::pair<uint256_t, uint256_t> &pair)
{
    std::string str_x, str_y;
    std::cin >> str_x;

    if (str_x != "stop")
    {
        std::cin >> str_y;
        uint256_t x = str_x, y = str_y;
        pair = std::make_pair(x, y);
    }
    return (str_x == "stop");
}

static uint256_t reconstruct_secret(std::vector<std::pair<uint256_t, uint256_t>> &points, const uint16_t t)
{
    const uint256_t modulo = FIELD_MODULO;

    uint256_t lagrange_polynomial = 0;
	uint256_t basis_polynomial;
    uint256_t temp, temp1;

	for (uint8_t i = 0; i < points.size(); i++)
	{
		basis_polynomial = 1;
		for (uint8_t j = 0; j < points.size(); j++)
		{
			if (j == i) continue;

            uint256_t numer = modulo - points[j].first;  // 0 - Xj
            uint256_t denom = 
                (points[i].first > points[j].first) ?
                (points[i].first - points[j].first) : modulo - (points[j].first - points[i].first);

            temp1 = inverse_modulo(denom, modulo);
            temp = numer.mulmod(temp1, modulo);
            basis_polynomial = basis_polynomial.mulmod(temp, modulo);	
		}

        temp = basis_polynomial.mulmod(points[i].second, modulo);
        lagrange_polynomial = lagrange_polynomial.addmod(temp, modulo);
	}

	return lagrange_polynomial; 
}

int16_t mode_recover()
{
    uint16_t t;
    std::cout << "T: ";
    std::cin >> t;
    std::vector<std::pair<uint256_t, uint256_t>> points_vector;

    uint16_t i = 0;
    bool input_flag = true;
    std::cout << "To stop entering type 'stop'...\n";
    while ((i < t) || input_flag)
    {
        std::pair<uint256_t, uint256_t> pair;
        bool code = get_point(pair);
        if (code && (i < t))
        {
            std::cout << "Not enough points were entered!\nContinue entering...\n";
        }
        else if (code && (i >= t))
        {
            input_flag = false;
        }
        else
        {
            points_vector.push_back(pair);
            i++;
        }
    }

    uint256_t secret = reconstruct_secret(points_vector, t);
    std::cout << std::hex << "\nSecret: 0x" << secret << "\n";

    return SUCCESS;
}
