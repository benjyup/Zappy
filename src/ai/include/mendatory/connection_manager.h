/*
** connection_manager.h for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai/include/mendatory
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Sun Jul  2 21:10:06 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 21:10:07 2017 vincent.mesquita@epitech.eu
*/

#ifndef CONNECTION_MANAGER_H
# define CONNECTION_MANAGER_H

#include "client.h"
#include <zconf.h>

typedef struct  e_fd_manager
{
    fd_set      read_fd;
    fd_set      write_fd;
}               t_fd_manager;

int connection_handler(t_cookie *cook, t_fd_manager *fd_manager);
int server_upload_data(int fd);
int server_download_data(int fd);

#endif /* !CONNECTION_MANAGER_H */
