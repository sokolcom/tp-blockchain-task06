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
    // bool a = x.powmod(modulo - 2, modulo) == (x.powmod(modulo - 2, modulo) % modulo);
    // std::cout << a << "\n";
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
    // std::vector<std::vector<uint256_t>> vandermonde_a(points.size(), std::vector<uint256_t>(t));
    // std::vector<uint256_t> y_values(points.size());
    // // std::vector<std::vector<uint256_t>> result_coeffs (t, std::vector<uint256_t>(1));
    // std::vector<uint256_t> result_coeffs(points.size());

    // init_vandermonde(vandermonde_a, points);
    // std::cout << "VANDERMONDE MATRIX:\n";
    // for (uint i = 0; i < vandermonde_a.size(); i++)
    // {
    //     for (uint j = 0; j < vandermonde_a[0].size(); j++)
    //     {
    //         std::cout << std::hex << vandermonde_a[i][j] << "  ";
    //     }
    //     std::cout << "\n";
    // }

    // init_yvector(y_values, points);
    // std::cout << "Y_VALUES MATRIX:\n";
    // for (uint i = 0; i < y_values.size(); i++)
    // {
    //     std::cout << std::hex << y_values[i] << "\n";
    // }

    // // inverse_matrix(vandermonde_a);

    // gauss_method(result_coeffs, vandermonde_a, y_values);

    // // matrix_mult(result_coeffs, vandermonde_a, y_values);

    // std::cout << "SECRET:\n";
    // for (uint i = 0; i < result_coeffs.size(); i++)
    // {
    //     std::cout << std::hex << result_coeffs[i] << "  ";
    //     std::cout << "\n";
    // }

    // return (uint256_t)0;



    static const uint256_t modulo = FIELD_MODULO;

    uint256_t lagrange_polynomial = 0;
	uint256_t basis_polynomial;
    uint256_t temp, temp1;

	for (uint i = 0; i < points.size(); i++)
	{
		basis_polynomial = 1;
		for (uint j = 0; j < points.size(); j++)
		{
			if (j == i) continue;

            uint256_t numer = modulo - points[j].first;  // 0 - Xj
            uint256_t denom = 
                (points[i].first > points[j].first) ?
                (points[i].first - points[j].first) : modulo - (points[j].first - points[i].first);

            // std::cout << "OK DENOM\n";
            temp1 = inverse_modulo(denom, modulo);
            temp = numer.mulmod(temp1, modulo);
            basis_polynomial = basis_polynomial.mulmod(temp, modulo);
			// basis_polynomial *= (numer * inverse_modulo(denom, modulo)) % modulo;	
            // std::cout << "OK INVERSE OOPS\n";
            // basis_polynomial %= modulo;	
		}
        temp = basis_polynomial.mulmod(points[i].second, modulo);
        lagrange_polynomial = lagrange_polynomial.addmod(temp, modulo);
		// lagrange_polynomial += (basis_polynomial * points[i].second) % modulo;
        // lagrange_polynomial %= modulo;
	}
	return lagrange_polynomial; 
}

int16_t mode_recover()
{
    uint16_t t;
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
            // std::cout << std::hex << "X: " << points_vector[points_vector.size() - 1].first << "\tY: " << points_vector[points_vector.size() - 1].second << "\n";
            i++;
        }
    }

    uint256_t secret = reconstruct_secret(points_vector, t);
    std::cout << std::hex << "SECRET: 0x" << secret << "\n" << "\n";

    return SUCCESS;
}




// void init_vandermonde(
//     std::vector<std::vector<uint256_t>> &vandermonde, 
//     std::vector<std::pair<uint256_t, uint256_t>> &src)
// {
//     const uint16_t t = vandermonde[0].size();

//     for (uint16_t i = 0; i < vandermonde.size(); i++)
//     {
//         for (uint16_t j = 0; j < t; j++)
//         {
//             vandermonde[i][j] = src[i].first.pow(t - j - 1);
//         }
//     }
// }

// void init_yvector(
//     std::vector<uint256_t> &y_vector, 
//     std::vector<std::pair<uint256_t, uint256_t>> &src)
// {

//     for (uint16_t i = 0; i < y_vector.size(); i++)
//     {
//         y_vector[i] = src[i].second;
//     }
// }

// // void inverse_matrix(std::vector<std::vector<uint256_t>> &A)
// // {
// //     const uint16_t size = A.size();
 
// //     // uint256_t **E = new uint256_t *[size];
// //     // for (int i = 0; i < size; i++)
// //     // {
// //     //     E[i] = new uint256_t[size];
// //     // }

// //     std::vector<std::vector<uint256_t>> E(size, std::vector<uint256_t>(size));
// //     for (uint16_t i = 0; i < size; i++)
// //     {
// //         E[i][i] = 0x1;
// //     }
 
// //     uint256_t temp;
// //     for (uint16_t k = 0; k < size; k++)
// //     {
// //         temp = A[k][k];
// //         for (uint8_t j = 0; j < size; j++)
// //         {
// //             A[k][j] /= temp;
// //             E[k][j] /= temp;
// //         }
 
// //         for (uint16_t i = k + 1; i < size; i++)
// //         {
// //             temp = A[i][k];
// //             for (uint16_t j = 0; j < size; j++)
// //             {
// //                 A[i][j] -= A[k][j] * temp;
// //                 E[i][j] -= E[k][j] * temp;
// //             }
// //         }
// //     }
 
// //     for (int16_t k = size - 1; k > 0; k--)
// //     {
// //         for (int16_t i = k - 1; i >= 0; i--)
// //         {
// //             temp = A[i][k];
// //             for (uint16_t j = 0; j < size; j++)
// //             {
// //                 A[i][j] -= A[k][j] * temp;
// //                 E[i][j] -= E[k][j] * temp;
// //             }
// //         }
// //     }
 
// //     for (uint16_t i = 0; i < size; i++)
// //         for (uint16_t j = 0; j < size; j++)
// //             A[i][j] = E[i][j];
 
// //     // for (int i = 0; i < size; i++)
// //     //     delete [] E[i];
// //     // delete [] E;
// // }


// // void matrix_mult(
// //     std::vector<std::vector<uint256_t>> &result, 
// //     std::vector<std::vector<uint256_t>> &A, std::vector<std::vector<uint256_t>> &B)
// // {
// //     for (uint16_t i = 0; i < A.size(); i++)
// //     {
// //         for (uint16_t j = 0; j < B[0].size(); j++)
// //         {
// //             for (uint16_t k = 0; k < A.size(); k++)
// //             {
// //                 result[i][j] += A[i][k] * B[k][j];
// //             }
// //         }
// //     }
// // }


// void gauss_method(
//     std::vector<uint256_t> &result, 
//     std::vector<std::vector<uint256_t>> &a, std::vector<uint256_t> &b)
// {
//     const uint256_t modulo = FIELD_MODULO;

//     for (uint k = 0; k < a.size(); k++) // прямой ход
//     {
//         for (uint j = k + 1; j < a.size(); j++)
//         {
//            uint256_t  d = a[j][k] / a[k][k]; // формула (1)
//             for (uint i = k; i < a.size(); i++)
//             {
//                 a[j][i] = (a[j][i] - d * a[k][i]) % modulo; // формула (2)
//             }

//             b[j] = (b[j] - d * b[k]) % modulo; // формула (3)
//         }
//     }

//     for (int k = a.size() - 1; k >= 0; k--) // обратный ход
//     {
//         uint256_t d = 0;
//         for (uint j = k + 1; j < a.size(); j++)
//         {
//             uint256_t s = (a[k][j] * result[j]) % modulo; // формула (4)
//             d = (d + s) % modulo; // формула (4)
//         }

//         result[k] = ((b[k] - d) / a[k][k]) % modulo; // формула (4)
//     }
// }

