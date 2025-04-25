/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:38:25 by iboiraza          #+#    #+#             */
/*   Updated: 2025/04/24 20:50:08 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# define COLOR_AZUL "\033[34m"
# define GREEN "\033[32m"
# define MAGENTA "\033[1;35m"
# define RST "\033[0m"

# define TEMP_FILE ".\vtemp\th"

typedef struct s_prompt
{
	char			*envp;
	struct s_prompt	*next;
}		t_prompt;

typedef struct s_node
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
	int		is_set;
	pid_t	n_pid;
}	t_node;

typedef struct s_mini
{
	char		**commands;
	char		*full_path;
	int			splits;
	int			ft_count_pipes;
	char		**execute_envp;
	t_node		**nodes;
	int			nbr_nodes;
	char		**bin_path;
	t_prompt	*env;
}	t_mini;

//utils.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_lstsort(t_prompt *lst, int swapped);
void		ft_lstadd_back(t_prompt **lst, t_prompt *new);
t_prompt	*ft_lstlast(t_prompt *lst);
t_prompt	*ft_lstnew(t_prompt *content);
int			ft_isalpha(int c);
int			ft_is_equal_simbol(char *argv);

//utils3.c
void		*ft_calloc(size_t count, size_t size);
void		ft_free(char **a);
void		ft_free_stack(t_prompt *a);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);

//split.c
char		**ft_split(char const *s, char c);
char		**ft_splitquotes(char const *s, char c, char s_quote, char d_quote);
size_t		ft_num_word(char const *s, char c, size_t i, size_t num_word);

//split_utils.c
void		free_split(char **argv);
int			ft_count_splits(char const *s, char c);

//builtins.c
void		echo(char **av, int flag);
void		pwd(int argc);
void		cd(int argc, char *av);
void		unset(char **argv, t_prompt **data);

//builtins_utils.c
void		ft_lscopy(t_prompt **list, char *content);
void		ft_lstsort(t_prompt *lst, int swapped);
t_prompt	*dup_env(t_prompt *original_env);
int			check_env_name(char *argv, int x);
void		asign_env_value(char *argv, t_prompt **data);
//init_shell.c
int			fork_actions(int argc, char **argv, int flag, t_prompt *env);
int			other_actions(int argc, char **argv, t_mini **data);
int			execute_builtin(char **argv, t_prompt *env, t_mini **data);

//exit.c
int			ft_exit(t_mini **data, int flag);

//parse_imput.c
void		remove_quotes(char *imput, int i);
int			detectopenquotes(char *line);
int			check_wrong_pipes(char **commands);
int			check_wrong_redir(char **commands);

//more_parsing.c
char		*prepare_line(char *line, int i, int j);
int			ft_more_checkers(char **commands);
int			ft_check_input(char *line);

//commands.c
void		not_builtin_command(char **data, char **env);
void		do_command(t_mini *data);

//ft_count_pipes.c
int			ft_count_pipes(char **commands);
char		**ft_strdup2(char **commands, int len, int first);
int			ft_len_to_pipe(char **commands, int flag, int start, int first);

//ft_prepare_nodes.c
int			ft_prepare_nodes(t_mini *data);

//ft_execute_commands.c
void		ft_execute_commands(t_mini *data);

//sert_full_cmd_path.c
char		*set_full_path(t_node *node, char **bin_path);
char		**set_full_cmd(char **commands, int i, int cmd);

//set_infile_outfile.c
int			set_infile_outfile(t_node *node, char **commands, int outfile,
				int infile);
int			get_here_doc(char *str[2], char *aux[2]);
void		ft_clean(t_mini *data);
int			check_pipe_redir(char *s, int i);
char		*ft_strdup(const char *s1);
void		set_bin_path(t_mini *data);
int			is_builtin(char *str);
void		ft_free_nodes(t_mini **data, int i);
char		*ft_create_temp(char *line, int i, int count, int j);

//ft_execute_one_command.c
void		prepare_builtin(t_mini *data, t_node *node);
void		execute_simple_command(t_mini *data, t_node *node, pid_t pid);

//env_parsed.c
char		*vars(char *commands, t_prompt *env, int i, int x);
char		*env_split(char const *s, int start);
char		*ft_itoa(int n);

//env_parsed2.c
char		*ft_asign_rare_value(char *var_value);
int			ft_check_dolar_length(char *line, int *j);
int			ft_check_dolars(char *line);
int			ft_check_for_quotes(char c, int *single_q, int *double_q, int *j);
char		*ft_checkvar_value(char *var_value, t_prompt *env, int i);

//signals.c
void		setup_signals(void);
void		handle_sigint(int sig);

//ft_print_prompt.c
void		print_logo(void);
char		*ft_print_user(void);

extern int	g_status;

#endif
