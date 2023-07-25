/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/25 20:41:13 by mmoramov         ###   ########.fr       */
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

	g_exitstatus = 0;
	while (42)
	{
		signal(SIGINT,handle_sigint);
		signal(SIGQUIT,SIG_IGN);
		ms.line = readline("minishell> ");
		if (!ms.line)
		{
			printf("exit\n");
			exit(0);
		}
		if (ms.line && strlen(ms.line) > 0)
		{

			if (ft_strncmp(ms.line,"exit",4) == 0)
			{
				free_env(ms.env);
				exit(0);
			}
			ft_parse(&ms);
			ft_prep_exe(&ms);

			//print ms exe
			//print env
			//print_env(ms.env);

			execute_cmds(&ms, env);
			printf("ft_exit: Exit status from main is %d\n", g_exitstatus);

			add_history(ms.line);
			free_line(ms.line);
		}
	}
	//clean_history();
	free_env(ms.env);
	return (0);
}

