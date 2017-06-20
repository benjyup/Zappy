//
// Created by Jean-Adrien on 19/06/17.
//

#include <stdio.h>
#include <mendatory/connection_manager.h>
#include <pthread.h>

int init_relay_connector(t_cookie *cook, t_fd_manager *fd_manager)
{
    if (cook->fd == -1)
        return (printf("Could not init relay_connector, bad FileDescriptor."), 1);
    FD_ZERO(&fd_manager->read_fd);
    FD_ZERO(&fd_manager->write_fd);
    FD_SET(cook->fd, &fd_manager->read_fd);
    FD_SET(cook->fd, &fd_manager->write_fd);
}

static void reset_fdset(t_cookie *cook, t_fd_manager *fd_manager)
{
    FD_ZERO(&fd_manager->read_fd);
    FD_ZERO(&fd_manager->write_fd);
    FD_SET(cook->fd, &fd_manager->read_fd);
    FD_SET(cook->fd, &fd_manager->write_fd);
}

void *relay_loop(void *data)
{
    t_cookie *cook;
    t_fd_manager *fd_manager;
    int err;

    err = 0;
    cook = ((t_thread_data*)data)->cook;
    fd_manager = ((t_thread_data*)data)->fd_manager;
    while (err != -1)
    {
        err = select(cook->fd + 1, &fd_manager->read_fd, &fd_manager->write_fd, NULL, NULL);
        if (err == -1)
            perror("select()");
        if (FD_ISSET(cook->fd, &fd_manager->write_fd))
            server_upload_data(cook->fd);
        if (FD_ISSET(cook->fd, &fd_manager->read_fd))
            server_download_data(cook->fd);
        if (((t_thread_data*)data)->flag == -1)
            err = -1;
        reset_fdset(cook, fd_manager);
    }
    pthread_exit(NULL);
}

int relay_manager_start(t_cookie *cook, t_fd_manager *fd_manager, t_thread_data *relay_manager)
{
    relay_manager->cook = cook;
    relay_manager->fd_manager = fd_manager;
    relay_manager->flag = 0;
    if (pthread_create(&relay_manager->network_relay, NULL, relay_loop, relay_manager) != 0)
        return (perror("pthread_create()"), 1);
    return (0);
}

int relay_manager_stop(t_thread_data *relay_manager)
{
    relay_manager->flag = -1;
    if (pthread_join(relay_manager->network_relay, NULL) != 0)
        return (perror("pthread_join()"), 1);
    return (0);
}