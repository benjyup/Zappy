//
// Created by Jean-Adrien on 19/06/17.
//

#ifndef CLIENT_H_
# define CLIENT_H_

extern char *name;

typedef struct  s_arg
{
    int         port;
    char        *name;
    char        *machine;
}               t_arg;

int help_function(char **av);
int port_function(char **av, t_arg *arg);
int name_function(char **av, t_arg *arg);
int machine_function(char **av, t_arg *arg);
int arg_entry(int ac, char **av, t_arg *arg);
void arg_free(t_arg *arg);
void usage(void);

#endif /* !CLIENT_H_ */
