//
// Created by Jean-Adrien on 19/06/17.
//

#ifndef CONNECTION_MANAGER_H
# define CONNECTION_MANAGER_H

#include "client.h"
#include <zconf.h>

typedef struct  e_fd_manager
{
    fd_set      read_fd;
    fd_set      write_fd;
}               t_fd_manager;

typedef struct      e_thread_data
{
    t_fd_manager    *fd_manager;
    t_cookie        *cook;
    pthread_t       network_relay;
    int             flag;
}                   t_thread_data;

int init_relay_connector(t_cookie *cook, t_fd_manager *fd_manager);
int relay_manager_start(t_cookie *cook, t_fd_manager *fd, t_thread_data *relay_manager);
int relay_manager_stop(t_thread_data *relay_manager);
int server_upload_data(int fd);
int server_download_data(int fd);

#endif /* !CONNECTION_MANAGER_H */
