/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:51:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/13 19:01:26 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <termios.h>
# include "../libs/libft/libft.h"
# include <limits.h>


# define ARG 0
# define PIPE 1
# define INFILE 2
# define HEREDOC 3
# define OUTFILE 4
# define OUTFILETRUNC 5

# define DEF_PATH "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin"

typedef struct s_ex
{
	char	**command;
	// char	**infile;
	// char	**outfile;
	int		fd[2];
	struct s_ex	*next;
	struct s_ex *previous;
} t_ex;


//struct for storage the enviroment
typedef	struct s_tok
{
	char	*content;
	int		type;
	struct	s_tok	*previous;
	struct	s_tok	*next;

}	t_tok;

typedef struct s_env
{
	char	*evar;
	char	*eval;
	struct s_env	*next;
}	t_env;

typedef	struct s_ms
{
	t_env	*env;
	char	*line;
	t_tok	*start;
	t_ex	*exe;

}	t_ms;

//enviroment functions
t_env	*new_env(char *env);
int		get_env(t_ms *ms, char **env);/*initial version, malloc protetcion and compact*/
char	*get_env_value(t_env *env ,char *var); /*to get a value of env f.e. PATH*/
void	add_env(t_ms *ms, char *newvar); //añade variables, para oldpwd y para export
int		check_env(t_env *env, char *var);
void	change_env(t_env *env, char *var, char *val);

//check line functions
int		open_quotes(char *line, int i);

//split the token
t_tok	*ft_split_tok(char *s, char c);

//commad structure
void	ft_prep_exe(t_ms	*ms);

//builts
int		b_echo(char **com);
int		check_n(char *arg);
int		pwd(t_env *env);
void	print_env(t_env *env);/*only for test, it will becomes ENV command...*/
int		env(t_env *env);
void    print_env_export(t_env *env); //for EXPORT
int		cd(t_env *env,char **com);

//free
void	free_ms(t_ms *ms);
void	free_env(t_env *env);
void	free_line(char *line);

//execution
void	ft_execute(t_ms	*ms, char **env);
void	ft_singlecommand(t_ms *ms,char **env);
void	ft_execve_prepare(t_ms	*ms, char **env);

#endif
