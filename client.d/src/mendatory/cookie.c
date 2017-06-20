//
// Created by Jean-Adrien on 19/06/17.
//

#include <mendatory/argument.h>
#include <mendatory/cookie.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <zconf.h>

static void print_ip(struct hostent *hostinfo, char *host)
{
    struct in_addr **addr_list;
    int i;

    i = 0;
    addr_list = (struct in_addr **)hostinfo->h_addr_list;
    printf("%s: %s IP's is ", name, host);
    while (addr_list[i] != NULL)
    {
        printf("%s", inet_ntoa(*addr_list[i]));
        i += 1;
    }
    printf("\n");
}

int cookie_connect(t_cookie *cook, t_arg *arg)
{
    struct hostent *hostinfo;


    hostinfo = gethostbyname(arg->host);
    if (hostinfo == NULL)
        return (perror("gethostbyname()"), 1);
    print_ip(hostinfo, arg->host);
    cook->addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)hostinfo->h_addr));
    cook->addr.sin_port = htons(arg->port);
    cook->addr.sin_family = AF_INET;
    if (connect(cook->fd,
                (const struct sockaddr *)&cook->addr,
                sizeof(cook->addr)) == -1)
        return (perror("connect()"), 1);
    return (0);
}

int cookie_disconnect(t_cookie *cook)
{
    if (cook->fd != -1)
        if (close(cook->fd) == -1)
            return (perror("close()"), 1);
    return(0);
}

int cookie_setup(t_cookie *cook)
{
    struct protoent   *pe;

    if (!(pe = getprotobyname("TCP")))
        return (perror("getprotobyname():"), 1);
    cook->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    if (cook->fd == -1)
        return (perror("socket()"), 1);
    return (0);
}