/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:51:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/04 19:18:03 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
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


# define ARG 0
# define PIPE 1
# define INFILE 2
# define HEREDOC 3
# define OUTFILE 4
# define OUTFILETRUNC 5

typedef struct s_ex
{
	char	**command;
	char	**infile;
	char	**outfile;
	int		fd[2];
	struct s_ex	*next;
	struct s_ex *previous;
};


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

}	t_ms;

//enviroment functions
t_env	*get_env(char **env);/*initial version, malloc protetcion and compact*/
void	print_env(t_env *env);/*only for test, it will becomes env command...*/
char	*get_env_value(t_env *env ,char *var); /*to get a value of env f.e. PATH*/

//check line functions
int		open_quotes(char *line, int i);

//split the token
t_tok	*ft_split_tok(char *s, char c);

#endif
