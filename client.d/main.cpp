//
//  Created by Jean-Adrien on 19/06/17
//

#include <iostream>
#include "zappy.hpp"
#include "server.hpp"

int main(int ac, char **av) {
    try {
        zappy::Zappy project(ac, av);
        project.run();
/*        srv_write("coucou\r\n");
        srv_write("this is a test\r\n");
        srv_write("jean-Adrien\r\n");
        char *s;
        while(!(s = srv_read()));
        printf("%s\n", s);  */
        project.console();
        project.stop();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}