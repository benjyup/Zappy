/*
** my_linked_list.c for  in /home/vincent/rendu/MyIRC/PSU_2016_myirc/serv
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Mon Jun  5 18:03:52 2017 vincent.mesquita@epitech.eu
** Last update Mon Jun 19 18:43:34 2017 vincent.mesquita@epitech.eu
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

t_list			*my_init_list(void)
{
  t_list		*list;

  if (!(list = malloc(sizeof(t_list))))
    {
      perror(MALLOC);
      exit(ERROR);
    }
  list->next = list;
  list->prev = list;
  list->data = NULL;
  return (list);
}

t_bool			my_add_to_end(t_list *root,
				      void *data)
{
  t_list		*new;

  if (!(new = malloc(sizeof(*new))))
    return (false);
  new->data = data;
  new->next = root;
  new->prev = root->prev;
  root->prev->next = new;
  root->prev = new;
  return (true);
}

void			my_del_elem(t_list *root,
				    t_list *elem_to_del,
				    free_callback *data_free)
{
  t_list		*prev;
  t_list		*next;

  (void)root;
  prev = elem_to_del->prev;
  next = elem_to_del->next;
  prev->next = next;
  next->prev = prev;
  if (data_free)
    data_free(elem_to_del->data);
  free(elem_to_del);
}

void			my_free_list(t_list *root,
				     free_callback *data_free)
{
  t_list		*current;
  t_list		*tmp;

  current = root->next;
  while (current != root)
    {
      tmp = current;
      current = current->next;
      if (data_free)
	data_free(tmp->data);
      free(tmp);
    }
  free(root);
}
