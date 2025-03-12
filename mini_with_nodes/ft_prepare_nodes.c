#include "minishell.h"

void	ft_prepare_nodes(t_mini *data)
{
	if (!check_wrong_redir(data->commands))
        printf("syntax error: redirection\n");
    else if (!check_wrong_pipes(data->commands))
        printf("syntax error: pipes\n");
    else
        printf("hola\n");
    return ;
}