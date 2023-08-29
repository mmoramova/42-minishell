/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/08/29 17:15:38 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_checkinput(t_ms *ms)
{
	if (open_quotes(ms->line, strlen(ms->line)) != 0)
		return(ft_error(ms, 1, "syntax error", "odd number of quotes", NULL));
	return (0);
}

int ft_parse(t_ms *ms)
{
	if (ft_checkinput(ms) == 1)
		return (1);
	ms->start = ft_split_tok(ms, ' ');
	if (ms->start == NULL)
		return (1);
	return (0);
}

void term_init()
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void handle_line(t_ms *ms)
{
	signal(SIGINT, SIG_IGN);
	if (ft_parse(ms) == 0)
	{
		ft_prep_exe(ms);
		//free s_tok
		execute_cmds(ms);
	}
	add_history(ms->line);
	free_line(ms->line);
	//free all
}

int	main(int argc, char **argv , char **env)
{
	t_ms	ms;

	ms.start = NULL;
	ms.exitstatus = 0;

	if (argc != 1 && argv[0])
		return (1);

	if (!env[0])
	{
		env = malloc(3 * sizeof(char*));
		env[0] = ft_strdup("PWD=/Users/josorteg/Documents/GitHub/42-minishell");//chdir
		env[1] = ft_strdup("SHLVL=0");
		env[2] = NULL;
	}
	if(get_env(&ms,env) == 0)
		return (0);
	if (check_env (ms.env, "OLDPWD") == 1)
		add_env (ms.env, "OLDPWD", getcwd(NULL,PATH_MAX));
	term_init();
	while (42)
	{
		g_process = 0;
		signal(SIGINT,handle_sigint);
		signal(SIGQUIT,SIG_IGN);
		ms.line = readline("minishell> ");
		signal(SIGINT, SIG_IGN);
		if (!ms.line)
		{
			if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
			clear_history();
			exit (ms.exitstatus);
		}

		if (ms.line && strlen(ms.line) > 0)
			handle_line(&ms);
	}
	//clean_history();
	free_env(ms.env);
	return (ms.exitstatus);
}

