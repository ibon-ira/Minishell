
#include "minishell.h"

char    *ft_check_< (char ** commands)
{
    
}

ft_check_redirections (char *data)
{
    int     i;
    t_mini  *current;

    *current = *data;
    i = 0;
    while (data->commands[i])
    {
        if (ft_strncmp(data->commands[i], "<", 1) == 0)
            current->infile = ft_check_< (current->commands);
       else  if (ft_strncmp(data->commands[i], "<<", 1) == 0)
            current->infile = ft_check_<< (current->commands);
       else  if (ft_strncmp(data->commands[i], "<",1) == 0)
             current->outfile = ft_check_> (current->commands);
       else  if (ft_strncmp(data->commands[i], ">>",1) == 0)
             current->outfile = ft_check_>> (current->commands);
    }
}