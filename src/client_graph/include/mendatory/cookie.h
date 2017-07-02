//
// Created by Jean-Adrien on 19/06/17.
//

#ifndef COOKIE_H_
# define COOKIE_H_

# include <netinet/in.h>

typedef struct          e_cookie
{
    int                 fd;
    struct sockaddr_in  addr;
}               t_cookie;

int cookie_setup(t_cookie *cook);
int cookie_connect(t_cookie *cook, t_arg *arg);
int cookie_disconnect(t_cookie *cook);

#endif /* !COOKIE_H_ */
