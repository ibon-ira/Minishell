
#include "minishell.h"

char    **ft_option1_1(char **commands)
{
    char **new_str;
    
    new_str = malloc(3 * sizeof(char *));
    new_str[0] = ft_strdup(commands[0]);
    new_str[1] = ft_strdup(commands[2]);
    new_str[2] = NULL;
    return (new_str);
}

/*char    **ft_option1_2(char **commands, int pos, int total)
{
    char **new_str;
    int i;
    
    i = 0;
    new_str = malloc(total + 1 * sizeof(char *));
    while (commands[i])
    {
            new_str[i] = ft_strdup(commands[i]);
    }
    new_str[i] = NULL;
    return (new_str);
}
*/
char    **ft_check_1(char **commands)
{
    int     i;
    char    **result;

    i = 0;
    result = NULL;
    if (ft_strncmp(commands[1], "<", 1) == 0)
        result = ft_option1_1(commands);
    return (result);
}

char    **ft_check_pos(char **commands, int pos, int total)
{
   printf("pru1-> %i\n", total);
   printf("pru2-> %i\n", pos);
    if (pos == 1 && total == 2)
        return (ft_option1_1(commands));
    //else
   //     return (ft_option1_2(commands, pos, total));
    return (commands);
}

char    **ft_check_redirections (char **commands, int total)
{
    int     i;

    i = 0;
    printf("pru-> %i\n", total);
    while (commands[i])
    {
        if (ft_strncmp(commands[i], "<", 1) == 0)
            return(ft_check_pos(commands, i, total - 1));
/*        else  if (ft_strncmp(data->commands[i], ">",1) == 0)
            current->outfile = ft_check_> (current->commands);
        else  if (ft_strncmp(data->commands[i], "<<", 1) == 0)
            current->infile = ft_check_<< (current->commands);
        else  if (ft_strncmp(data->commands[i], ">>",1) == 0)
            current->outfile = ft_check_>> (current->commands);
*/      i++;
    }
    return (commands);
}