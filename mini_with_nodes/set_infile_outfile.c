#include "minishell.h"

void	check_heredoc(char *limit, int *infile)
{
	char	*aux[2];
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	aux[0] = limit;
	*infile = get_here_doc(str, aux);
	if (*infile == -1)
		*infile = STDIN_FILENO;
}

int	first_case_aux(char **commands, int *outfile, int i)
{
	if (*outfile != STDOUT_FILENO)
		close(*outfile);
	*outfile = open(commands[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (*outfile == -1)
	{
		printf(" : No such file or directory\n");
		return (0);
	}
	return (1);
}

int	second_case_aux(char **commands, int *outfile, int i)
{
	if (*outfile != STDOUT_FILENO)
		close(*outfile);
	*outfile = open(commands[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*outfile == -1)
	{
		printf(" : No such file or directory\n");
		return (0);
	}
	return (1);
}

int	third_case_aux(char **commands, int *infile, int i)
{
	if (!ft_strncmp(commands[i - 1], "<", 1))
	{
		if (*infile != STDIN_FILENO && *infile != -1)
			close(*infile);
		*infile = open(commands[i], O_RDONLY);
		if (*infile == -1)
		{
            printf("%s : No such file or directory\n", commands[i]);
			*infile = STDIN_FILENO;
			return (0);
		}
	}
	else
		check_heredoc(commands[i], infile);
	return (1);
}

int	set_infile_outfile(t_node *node, char **commands, int outfile, int infile)
{
	int	i;

	i = -1;
	while (commands[++i] != NULL)
	{
        if (!ft_strncmp(commands[i], ">>", 2) && commands[i + 1])
		{
			if (second_case_aux(commands, &outfile, ++i) == 0)
				return (0);
		}
		else if (!ft_strncmp(commands[i], ">", 1) && commands[i + 1])
		{
			if (first_case_aux(commands, &outfile, ++i) == 0)
				return (0);
		}
		else if ((!ft_strncmp(commands[i], "<", 1) || !ft_strncmp(commands[i], "<<", 2))
			&& commands[i + 1])
		{
			if (third_case_aux(commands, &infile, ++i) == 0)
				return (0);
		}
	}
	node->infile = infile;
	node->outfile = outfile;
	return (1);
}