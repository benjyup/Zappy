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
    t_cookie cook;
    if (arg_entry(ac, av, &arg) == 1)
        return 1;
    std::cout << "Client Zappy v0.1" << std::endl;
    std::cout << "PORT    : " << arg.port << std::endl;
    std::cout << "TEAM    : " << arg.team << std::endl;
    std::cout << "MACHINE : " << arg.host << std::endl;
    std::cout << name << ": settingUp cookie for connection to " << arg.host << std::endl;
    if (cookie_setup(&cook) == 1)
        return 1;
    if (cookie_connect(&cook, &arg) == 1)
        return 1;
    dprintf(cook.fd, "coucou\r\n");
    if (cookie_disconnect(&cook) == 1)
        return 1;
    arg_free(&arg);
    return 0;
}