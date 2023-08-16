/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/08/16 19:19:44 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_checkinput(t_ms ms)
{
	if (open_quotes(ms.line,strlen(ms.line)) != 0)
	{
		ft_exit(1, "syntax error","odd number of quotes", NULL);
		return(1);
	}
	//if (ft_strchr(ms.line, ''))
	// here i will check if in command is not \ ; or &
	return(0);
}

int ft_parse(t_ms	*ms)
{
	if (ft_checkinput(*ms) == 1)
		return(1);
	ms->start = ft_split_tok(ms, ' ');
	if (ms->start == NULL)
		return (1);
	return(0);
}

void term_init()
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL; //activa
	//term.c_lflag |= ECHOCTL; //desactiva
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void handle_line(t_ms *ms, char **env)
{
	signal(SIGINT,SIG_IGN);
	if (ft_parse(ms) == 0)
	{
		ft_prep_exe(ms);
		execute_cmds(ms, env);
	}
	add_history(ms->line);
	free_line(ms->line);
}

int	main(int argc, char **argv , char *env[])
{
	t_ms	ms;

	ms.start = NULL;
	if (argc != 1 && argv[0])
		return(1);
	//print enviroment (like env, only for test, OK no bus error!!!)
	if(get_env(&ms,env) == 0)
		return (0);
	//adding (plusing!!) oldpwd for cd porpose
	if (check_env (ms.env, "OLDPWD") == 1)
		add_env (ms.env, "OLDPWD", getcwd(NULL,PATH_MAX));
	term_init();
	while (42)
	{
		g_exit.process = 0;
		signal(SIGINT,handle_sigint);
		signal(SIGQUIT,SIG_IGN);
		// if(signal(EOF,handle_sigint)) //control d
		// {
		// 	perror("exit");
		// 	exit(g_exit.status);
		// }

		//NEW PROACH WITH ISATTY
		if (isatty(fileno(stdin)))
			ms.line = readline("minishell> ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			ms.line = ft_strtrim(line, "\n");
			free(line);
		}

		//old readline
		// ms.line = readline("minishell> ");
		if (!ms.line)
			b_exit(1);
		if (ms.line && strlen(ms.line) > 0)
			handle_line(&ms, env);
	}
	//clean_history();
	free_env(ms.env);
	return (g_exit.status);
}

