//
// Created by alice on 20/06/17.
//

#include <iostream>

int     help_function(int a)
{
    std::cout << "  help  - Display this help" << std::endl;
    std::cout << "  flush - Flush the entry stack of the client" << std::endl;
    std::cout << "  quit  - Disconnect and terminate client connection" << std::endl;
    return 0;
}

int     flush_function(int a)
{
    return 0;
}