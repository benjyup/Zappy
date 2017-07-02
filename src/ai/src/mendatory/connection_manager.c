/*
** connection_manager.c for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai/src/mendatory
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Sun Jul  2 20:50:02 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 20:59:03 2017 vincent.mesquita@epitech.eu
*/

#include <stdio.h>
#include <mendatory/connection_manager.h>
#include <pthread.h>

static int	reset_fdset(t_cookie *cook,
			    t_fd_manager *fd_manager)
{
  if (cook->fd == -1)
    return (printf("Could not init relay_connector, bad FileDescriptor."),
	    1);
  FD_ZERO(&fd_manager->read_fd);
  FD_ZERO(&fd_manager->write_fd);
  FD_SET(cook->fd, &fd_manager->read_fd);
  FD_SET(cook->fd, &fd_manager->write_fd);
  return (0);
}

int		connection_handler(t_cookie *cook,
				   t_fd_manager *fd_manager)
{
  int		err;

  reset_fdset(cook, fd_manager);
  err = select(cook->fd + 1, &fd_manager->read_fd,
	       &fd_manager->write_fd, NULL, NULL);
  if (err == -1)
    {
      perror("select()");
      return (1);
    }
  err = 0;
  if (FD_ISSET(cook->fd, &fd_manager->write_fd))
    err = server_upload_data(cook->fd);
  if (FD_ISSET(cook->fd, &fd_manager->read_fd))
    err = server_download_data(cook->fd);
  return (err);
}
