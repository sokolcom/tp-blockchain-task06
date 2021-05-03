#include <iostream>
#include <cstring>
#include <stdexcept>

#include "../include/define.h"
#include "../include/split.h"
#include "../include/recover.h"



int main(int argc, char *argv[])
{
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
            mode_recover();
        }
        else
        {
            throw std::invalid_argument("Error!\nUnknown option!");
            return FAILURE;
        }
    }

    return SUCCESS;
}
