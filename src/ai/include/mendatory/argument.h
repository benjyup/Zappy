/*
** argument.h for  in /home/vincent/rendu/Zappy/PSU_2016_zappy/src/ai/include/mendatory
** 
** Made by vincent.mesquita@epitech.eu
** Login   <vincent@epitech.net>
** 
** Started on  Sun Jul  2 21:10:11 2017 vincent.mesquita@epitech.eu
** Last update Sun Jul  2 21:10:11 2017 vincent.mesquita@epitech.eu
*/

#ifndef ARGUMENT_H_
# define ARGUMENT_H_

extern char *name;

typedef struct  s_arg
{
    int         port;
    char        *team;
    char        *host;
}               t_arg;

int help_function(char **av);
int port_function(char **av, t_arg *arg);
int name_function(char **av, t_arg *arg);
int machine_function(char **av, t_arg *arg);
int arg_entry(int ac, char **av, t_arg *arg);
void arg_free(t_arg *arg);
void usage(void);

#endif /* !ARGUMENT_H_ */
