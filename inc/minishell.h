/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:51:20 by josorteg          #+#    #+#             */
/*   Updated: 2023/06/29 17:23:42 by josorteg         ###   ########.fr       */
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




//struct for storage the enviroment




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
}	t_ms;


//enviroment functions

t_env   *get_env(char **env);/*initial version, malloc protetcion and compact*/
void    print_env(t_env *env);/*only for test, it will becomes env command...*/
char    *get_env_value(t_env *env ,char *var); /*to get a value of env f.e. PATH*/



#endif
