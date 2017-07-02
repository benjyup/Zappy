//
// Created by alice on 20/06/17.
//

#ifndef CLIENT_D_SERVER_HPP
#define CLIENT_D_SERVER_HPP

extern "C"
{
int  srv_write(const char *s);
char *srv_read(void);
};

#endif //CLIENT_D_SERVER_HPP
