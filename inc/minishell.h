/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:51:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/26 18:08:43 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../readline/readline.h"
# include "../readline/history.h"
# include <signal.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <termios.h>
# include "../libs/libft/libft.h"
# include <limits.h>
# include <sys/ioctl.h>
# include <termios.h>

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
	int		fd[2];
	int		parent;
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
	int		cntcmds;
	int		**pipes;
	int		*pids;
	int		heredocfd;

}	t_ms;

//global variable

typedef struct s_exit
{
	int	status;
	int	proces;
}	t_exit;

t_exit	g_exit;



//enviroment functions
t_env	*new_env(char *env);
int		get_env(t_ms *ms, char **env);/*initial version, malloc protetcion and compact*/
char	*get_env_value(t_env *env ,char *var); /*to get a value of env f.e. PATH*/
void	add_env(t_env *env, char *val, char *var); //añade variables, para oldpwd y para export
int		check_env(t_env *env, char *var);
void	change_env(t_env *env, char *var, char *val);

//check line functions and quotes
int		open_quotes(char *line, int i);
char 	*ft_quotes_remove(char *s);
int 	ft_quotes_nbr(char *line);

//split the token
t_tok	*ft_split_tok(t_ms *ms, char c);

//expand
char	*ft_expand (t_ms *ms, char *s);
char	*ft_strjoinfree(char *s1, char const *s2);

//commad structure
void	ft_prep_exe(t_ms	*ms);
int		ft_parent_exe(t_ms	*ms, char **command);

//heredoc
int		heredoc_fillfd(t_ms *ms, t_tok *tokens);
int		heredoc_execute(t_ms *ms, char *file);
void	heredoc_read(t_ms *ms, char *file, int fd[2]);


//builts
int		is_builtin(char *cmd);
int		b_echo(char **com);
int		check_n(char *arg);
int		pwd(t_env *env);
void	print_env(t_env *env);/*only for test, it will becomes ENV command...*/
int		enviroment(t_env *env);
void	print_env_export(t_env *env); //for EXPORT
int		check_export(char	*nenv);
int		cd(t_ms *ms, char **com);
int		export(t_ms *ms, char **com, int parent);
int		unset(t_ms *ms ,char **com);
void	b_exit(void);

//free
void	free_ms(t_ms *ms);
void	free_env(t_env *env);
void	free_line(char *line);
void	free_ex(t_ex *ex);
void	free_tok(t_tok *tok);

//execution
void	execute_cmds(t_ms *ms, char **env);
int		execute_builtin(t_ms *ms,char **cmd, int parent);
void	execve_prepare(t_ms	*ms, char **env, char **cmd);
int		**handle_pipes(t_ms *ms);
int		handle_forks(t_ms *ms, char **env);
void	handle_redirections(t_ms *ms, int fd[2], int lvl);
void	handle_waitpid(int *pids, int is_parent);
void	close_pipes(int **pipes);

//execution second option, i created file executionsV2
void execute_secondoption(t_ms	*ms, char **env);
void execute_secondoption2(t_ms	*ms, char **env);


//exit and signal
void	ft_exit(int exitnumber, char *txt, char *txt2, char *txt3);
void	handle_sigint(int sig);

#endif
