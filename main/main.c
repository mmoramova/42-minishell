/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/08/04 11:43:34 by josorteg         ###   ########.fr       */
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
    term.c_lflag &= ~ECHOCTL; //activa
	//term.c_lflag |= ECHOCTL; //desactiva
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
	while (42)
	{
		g_exit.proces = 0;
		signal(SIGINT,handle_sigint);
		signal(SIGQUIT,SIG_IGN);
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
		// 	char *line;
		// 	line = get_next_line(fileno(stdin));
		// 	ms.line = ft_strtrim(line, "\n");
		// 	free(line);
		// }


		//old readline

		ms.line = readline("minishell> ");
		if (!ms.line)
		{
			printf("exit");
			b_exit(g_exit.status);
		}
		if (ms.line && strlen(ms.line) > 0)
		{
			signal(SIGINT,SIG_IGN);
			ft_parse(&ms);
			ft_prep_exe(&ms);

			execute_cmds(&ms, env);
			//ignore after execution
			//printf("ft_exit: Exit status from main is %d\n", g_exit.status);

			add_history(ms.line);
			free_line(ms.line);
		}
	}
	//clean_history();
	free_env(ms.env);
	return (g_exit.status);
}

