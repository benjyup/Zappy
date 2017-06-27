//
//  Created by Jean-Adrien on 19/06/17
//

#include <iostream>
#include "zappy.hpp"
#include "server.hpp"
#include "AIClient.hpp"

int main(int ac, char **av) {
    try {
        zappy::Zappy project(ac, av);
        zappy::AIClient ia(project.getArg());
        zappy::Proxy    prx(ia, project);
        zappy::RequestType  rqst = zappy::NOOP;
        int err = 0;
        while (err != 1) {
            err = project.update();
            prx.update(rqst);
            rqst = ia.updade();
            //srv_write("coucou\r\n");
            //project.console();
        }
        std::cout << "Connection with the remote Host has been loose." << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}