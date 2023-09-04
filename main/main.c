/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/04 19:17:13 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_init()
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	handle_line(t_ms *ms)
{
	signal(SIGINT, SIG_IGN);
	if (ft_parse(ms) == 0)
	{
		ft_prep_exe(ms);
		execute_cmds(ms);
	}
	add_history(ms->line);
	//free_doublechar(ms->array_env);
	//free all
}

int	main(int argc, char **argv, char **env)
{
	t_ms	ms;

	ms.start = NULL;
	ms.exitstatus = 0;
	if (argc != 1 && argv[0])
		return (1);
	if (!env[0])
	{
		env = malloc(3 * sizeof(char*));
		env[0] = ft_strdup(getcwd(NULL, PATH_MAX));
		env[1] = ft_strdup("SHLVL=0");
		env[2] = NULL;
	}
	if(get_env(&ms, env) == 0)
		return (0);
	if (check_env (ms.env, "OLDPWD") == 1)
		add_env (ms.env, "OLDPWD", getcwd(NULL, PATH_MAX));
	term_init();
	while (42)
	{
		g_process = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		ms.line = readline("minishell> ");
		signal(SIGINT, SIG_IGN);
		if (!ms.line)
		{
			ft_exit_finish();
			exit (ms.exitstatus);
		}
		if (ms.line && ft_strlen(ms.line) > 0)
			handle_line(&ms);
		free_line(ms.line);
	}
	//clean_history();
	free_env(ms.env);
	return (ms.exitstatus);
}

