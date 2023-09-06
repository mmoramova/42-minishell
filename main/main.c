/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/06 11:54:25 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_init(void)
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
}

void	env_init(t_ms *ms, char **env)
{
	ms->exitstatus = 0;
	ms->oldpwd = 0;
	ms->pwd = 1;
	if (!env[0])
	{
		env = malloc(3 * sizeof(char *));
		env[0] = ft_strdup(getcwd(NULL, PATH_MAX));
		env[1] = ft_strdup("SHLVL=0");
		env[2] = NULL;
	}
	get_env(ms, env);
	if (check_env(ms->env, "OLDPWD") == 0)
		ft_unset_env(ms, "OLDPWD");
}

int	main(int argc, char **argv, char **env)
{
	t_ms	ms;

	if (argc != 1 && argv[0])
		return (1);
	ms.start = NULL;
	env_init(&ms, env);
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
		free(ms.line);
	}
	free_env(ms.env);
	return (ms.exitstatus);
}
