/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/08/02 16:44:10 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_checkinput(t_ms ms)
{
	if (open_quotes(ms.line,strlen(ms.line)) != 0)
		return(1);
	return(0);
}

void ft_parse(t_ms	*ms)
{
	//t_tok *tokens;

	if (ft_checkinput(*ms) == 1)
	{
		//TODO ERROR
		exit(1);
	}
	ms->start = ft_split_tok(ms, ' ');


	/*token only for printing:*/
	// tokens = ms->start;
	// while (tokens)
	// {
	// 	printf("%s || ", tokens->content);
	// 	printf("%d\n", tokens->type);
	// 	tokens=tokens->next;
	// }
}

void term_init()
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
	g_exit.proces = 0;
	signal(SIGQUIT,SIG_IGN);
	g_exit.status = 0;
	while (42)
	{
		g_exit.proces = 0;
		signal(SIGINT,handle_sigint);
		// if(signal(EOF,handle_sigint)) //control d
		// {
		// 	perror("exit");
		// 	exit(g_exit.status);
		// }

//NEW PROACH WITH ISATTY
		// if (isatty(fileno(stdin)))
		// 	ms.line = readline("minishell >");
		// else
		// {
		// 	printf("exit");
		// 	exit(1);
		// }


		//old readline

		ms.line = readline("minishell> ");
		if (!ms.line)
		{
			printf("exit");

			exit(g_exit.status);
		}
		signal(SIGINT,handle_sigint);

		g_exit.proces = 0;

		if (ms.line && strlen(ms.line) > 0)
		{
			ft_parse(&ms);
			ft_prep_exe(&ms);

			execute_cmds(&ms, env);
			signal(SIGQUIT,SIG_IGN); //ignore after execution
			//printf("ft_exit: Exit status from main is %d\n", g_exit.status);

			add_history(ms.line);
			free_line(ms.line);
		}
	}
	//clean_history();
	free_env(ms.env);
	return (0);
}

