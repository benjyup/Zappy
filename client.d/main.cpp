//
//  Created by Jean-Adrien on 19/06/17
//

#include <iostream>
#include "zappy.hpp"
#include "server.hpp"

int main(int ac, char **av) {
    try {
        zappy::Zappy project(ac, av);
        int err = 0;
        while (err != 1) {
            err = project.update();
            //srv_write("coucou\r\n");
            project.console();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}