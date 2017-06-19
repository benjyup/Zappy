//
//  Created by Jean-Adrien on 19/06/17
//

#include <iostream>

extern "C"
{
#include "mendatory/client.h"
}

int main(int ac, char **av) {
    t_arg arg;
    if (arg_entry(ac, av, &arg) == 1)
        return 1;
    std::cout << "Client Zappy v0.1" << std::endl;
    std::cout << "PORT    : " << arg.port << std::endl;
    std::cout << "TEAM    : " << arg.name << std::endl;
    std::cout << "MACHINE : " << arg.machine << std::endl;
    arg_free(&arg);
    return 0;
}