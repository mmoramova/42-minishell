/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:51:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/06 11:31:23 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libs/readline/readline.h"
# include "../libs/readline/history.h"
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

typedef struct s_ex
{
	char		**command;
	int			fd[2];
	int			parent;
	struct s_ex	*next;
	struct s_ex	*previous;
}	t_ex;

//struct for storage the enviroment
typedef struct s_tok
{
	char			*content;
	int				type;
	struct s_tok	*previous;
	struct s_tok	*next;

}	t_tok;

typedef struct s_env
{
	char			*evar;
	char			*eval;
	struct s_env	*next;
}	t_env;

typedef struct s_ms
{
	t_env	*env;
	char	**array_env;
	char	*line;
	t_tok	*start;
	t_ex	*exe;
	int		cntcmds;
	int		**pipes;
	int		*pids;
	int		heredocfd;
	int		exitstatus;
	int		pwd;
	int		oldpwd;
}	t_ms;

//global variable
int	g_process;

//enviroment functions
t_env	*new_env(char *env);
int		get_env(t_ms *ms, char **env);
char	*get_env_value(t_env *env, char *var);
void	add_env(t_env *env, char *val, char *var);
int		check_env(t_env *env, char *var);
void	change_env(t_env *env, char *var, char *val);
char	**env_toarray(t_ms *ms);
t_env	*new_env_plus(char *env);
void	plus_env(t_env *env, char *var, char *val);
void	shlvl_add(t_ms *ms);
void	ft_unset_env(t_ms *ms, char *com);

//check line functions and quotes
int		open_quotes(char *line, int i);
char	*ft_q_r(char *s);
int		ft_quotes_nbr(char *line);
int		ft_wordlen_wq(char const *s, char c);

//split the token
int		ft_parse(t_ms *ms);
t_tok	*ft_split_tok(t_ms *ms, char c);
int		ft_tok_addtype(char *s);
int		ft_tok_checks(t_ms *ms, t_tok *lst);
int		ft_tok_checks2(t_ms *ms, t_tok *lst);
t_tok	*ft_toklstnew(t_ms	*ms, t_tok	*tokens, char *content);
t_tok	*ft_toklstlast(t_tok *lst);
void	ft_toklstadd_back(t_tok **lst, t_tok *new);
int		ft_lstcmd_count(t_tok *token);

//expand
char	*ft_expand(t_ms *ms, char *s);
char	*ft_start_expand(char *s, int i);
char	*ft_var_expand(char *s, int i);
char	*ft_sub_expand(t_ms *ms, char *var, int i, char *str);
t_tok	*ft_expand_token(char *str);
char	*ft_exp_quotes(char *str, int quot);

//commad structure
void	ft_prep_exe(t_ms	*ms);
int		ft_parent_exe(t_ms	*ms, char **command);

//heredoc
int		heredoc_fillfd(t_ms *ms, t_tok *tokens);
int		heredoc_execute(t_ms *ms, char *file);
void	heredoc_read(t_ms *ms, char *file, int fd[2]);
void	heredoc_checkline(t_ms *ms, char *file, int fd[2], char *line);

//utils
char	*ft_strjoinfree(char *s1, char *s2);
int		ft_fd_isopen(int fd);
int		ft_count_types(t_tok *token, int type);
int		openfd(t_ms *ms, int type, int fd[2], char *file);

//builts
int		is_builtin(char *cmd);
int		b_echo(char **com);
int		check_n(char *arg);
int		pwd(t_env *env);
void	print_env(t_env *env);/*only for test, it will becomes ENV command...*/
int		enviroment(t_env *env);
void	print_env_export(t_env *env); //for EXPORT
int		check_export(char *nenv);
int		cd(t_ms *ms, char **com);
int		export(t_ms *ms, char **com);
int		check_export_plus(char *nenv);
int		unset(t_ms *ms, char **com);
int		b_exit(t_ms *ms, char **com, int parent);

//free
void	free_ms(t_ms *ms);
void	free_env(t_env *env);
void	free_ex(t_ex *ex);
void	free_tok(t_tok *tok);
void	free_doublechar(char **ptr);
void	free_doubleint(int **ptr);
void	free_ex_exit(t_ms *ms, int exitstatus);

//execution
void	execute_cmds(t_ms *ms);
int		execute_builtin(t_ms *ms, char **cmd, int parent);
void	execve_prepare(t_ms	*ms, char **cmd);
void	ft_execve(t_ms	*ms, char *path, char **cmd, char **env);
void	ft_execve_paths(t_ms *ms, char **cmd, char **paths);
int		**handle_pipes(t_ms *ms);
int		handle_forks(t_ms *ms);
void	handle_child(t_ms *ms, t_ex *com, int i);
void	handle_redirections(t_ms *ms, int fd[2], int lvl);
void	handle_waitpid(t_ms *ms, int is_parent);
void	close_pipes(int **pipes);

//error and signal
int		ft_error(t_ms *ms, int exitnumber, char *txt, char *txt2);
int		ft_error2(int exitnumber, char *txt, char *txt2, char *txt3);
int		ft_error3(int exitnumber, char *txt, char *txt2, char *txt3);
int		ft_error4(int exitnumber, char *txt, char *txt2, char *txt3);
void	handle_sigint(int sig);
void	handle_siginth(int sig);
void	handle_sigintp(int sig);

void	handle_line(t_ms *ms);
void	ft_exit_finish(void);
#endif
