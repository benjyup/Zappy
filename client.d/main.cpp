//
//  Created by Jean-Adrien on 19/06/17
//

#include <iostream>
#include "zappy.hpp"

int main(int ac, char **av) {
    try {
        zappy::Zappy project(ac, av);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}