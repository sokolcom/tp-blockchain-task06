#include <iostream>
#include <cstring>
#include <stdexcept>



#include "../include/define.h"
#include "../include/uint256.h"
#include "../include/split.h"



// static std::shared_ptr<uint256_t[]> create_coeffs(const uint8_t t, const uint256_t &private_key)
// {
//     std::shared_ptr<uint256_t[]> coeffs(new uint256_t[t]);

//     coeffs[0] = private_key;
//     for (uint8_t i = 1; i < t; i++)
//     {
//         uint8_t buffer[BYTES_PER_256_BIT] = { 0 };
//         int8_t code = RAND_bytes(buffer, BYTES_PER_256_BIT);
//         if (!code)
//         {
//             throw std::runtime_error("Error!\nOpenSSL function failed!");
//         }
//         coeffs[i].from_bytes(buffer, BYTES_PER_256_BIT);
//     }

//     return coeffs;
// }

// std::string to_hex(uint8_t number)
// {
//     char digits[] = "0123456789ABCDEF";
//     std::string hexstring = "";

//     // uint8_t i = 0;
//     while (number)
//     {
//         hexstring = digits[number % 16] + hexstring;
//         number /= 16;
//         // i++;
//     }

//     return hexstring;
// }


int main(int argc, char *argv[])
{
    // std::cout << to_hex(18);
    std::cout << "Leeeet's gooooo!\n";

    // uint8_t a = 0b11010011, b = 0b10100110;
    // uint16_t c = a + b;

    // uint8_t aa = 0b1000, bb = 0b1;
    // uint8_t cc = aa + bb + 1;

    // std::cout << std::to_string(c) << "\n";
    // std::cout << std::to_string(cc) << "\n";
    // std::cout << std::to_string((uint8_t)(-1)) << "\n";

    // uint256_t aaa = "0xFF";
    // uint256_t bbb = "0xFF";
    // uint256_t sum = aaa + bbb;
    // // std::cout << aaa << "\n" << bbb << "\n" << sum << "\n";
    // std::cout << sum << "\n";


    // for (int i = 0; i < 32; i++)
    // {
    //     std::cout << std::to_string(sum._number[i]) << "  ";
    // }


    // uint256_t a;
    // std::cin >> a;

    // printf("A: ");
    // for (int i = 0; i < 32; i++)
    // {
    //     printf("%d ", a._number[i] / 2); 
    // }
    // printf("\n");

    // std::shared_ptr<uint256_t[]> coeffs = create_coeffs(3, a);
    // printf("COEFFS:\n");
    // for (int i = 0; i < 3; i++)
    // {
    //     printf("x^%d: ", i);
    //     for (int j = 0; j < 32; j++)
    //     {
    //         printf("%d ", coeffs[i]._number[j]); 
    //     }
    //     printf("\n");
    // }

    // std::string s = "Hello world!";
    // s += (char*)"M\n";
    // std::cout << s;

    // int idx = 32;
    // uint8_t buffer[32] = { 0 };
    // buffer[1] = 1;
    // while (!buffer[--idx]);
    // printf("IDX: %d\n", idx);


    // int8_t code = RAND_bytes(buffer, 32);
    // printf("Buffer: ");
    // for (int i = 0; i < 32; i++)
    // {
    //     printf("%d ", buffer[i]); 
    // }
    // printf("\n");

    // uint256_t b;
    // b.from_bytes(buffer, 32);
    // printf("B: ");
    // for (int i = 0; i < 32; i++)
    // {
    //     printf("%d ", b._number[i]); 
    // }
    // printf("\n");
    

    if (argc != 2)
    {
        throw std::invalid_argument("Error!\nInvalid amount of the options!");
        return FAILURE;
    }
    else
    {
        if (!strcmp(argv[1], "split"))
        {
            mode_split();
        }
        else if (!strcmp(argv[1], "recover"))
        {
            /* code */
        }
        else
        {
            throw std::invalid_argument("Error!\nUnknown option!");
            return FAILURE;
        }
    }

    return SUCCESS;
}
