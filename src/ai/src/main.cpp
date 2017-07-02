//
//  Created by Jean-Adrien on 19/06/17
//

#include <iostream>
#include "zappy.hpp"
#include "server.hpp"
#include "AIClient.hpp"

int fork_process()
{
    int pid;
    if ((pid = fork()) == -1)
        return (perror("fork()"), -1);
    if (pid == 0)
        return (0);
    return (1);
}

int loop_controller(int ac, char **av)
{
    try {
        srand(getpid() * time(NULL));
        zappy::Zappy project(ac, av);
        zappy::AIClient ia(project.getArg());
        zappy::Proxy    prx(ia, project);
        zappy::RequestType  rqst = zappy::NOOP;
        int err = 0;
        while (err != 1) {
            err = project.update();
            std::string input = prx.update(rqst);
            rqst = ia.update(input);
            if (rqst == zappy::FORK)
                if (fork_process() == 0)
		  {
		    std::cout << "JE FORK UN FILS" << std::endl;
		    return 2;
		  }
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

int main(int ac, char **av) {
    int ret;
    while ((ret = loop_controller(ac, av)) == 2);
    return ret;
}