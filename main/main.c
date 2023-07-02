/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/02 16:44:45 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int ft_checkinput(t_ms ms)
{
	if (open_quotes(ms.line,567) != 0) //TODO input
		return(1);
	return(0);
}

void ft_parse(t_ms	*ms)
{
	t_tok *tokens;

	if (ft_checkinput(*ms) == 1)
	{
		//TODO ERROR
		exit(1);
	}
	ms->start = ft_split_tok(ms->line, ' ');

	tokens = ms->start;
	while (tokens)
	{
		printf("%s\n", tokens->content);
		tokens=tokens->next;
	}
}

int	main(int argc, char **argv, char *env[])
{
	t_ms	ms;

	ms.start = NULL;
	if (argc != 1 && argv[0])
		return(1);
	ms.env = get_env(env);
	//print enviroment (like env, only for test)
	//print_env(ms.env);
	printf("%s\n",get_env_value(ms.env ,"PATH"));

	while (1)
	{


		ms.line = readline("minishell>");
		//printf("%s\n",ms.line);
		if (ms.line)
		{
			add_history(ms.line);
			ft_parse(&ms);
			// if (ms.line != (void *)0)
			// 	free(ms.line);
		}

		//ms.line = "dfsfsdf fsd fsd fdfs ";
		//ms.tokens = NULL;

		//ft_parse(&ms);
		//add_history(ms.line);

		//printf("%d\n", open_quotes(ms.line,879));

		/*if (ms.line)
		{
		// 	//printf("%d\n",(int)strlen(ms.line));
		// 	//printf("%d\n", open_quotes(ms.line,(int)strlen(ms.line)));

		add_history(ms.line);
			ft_parse(ms);
			free(ms.line);
		}*/

	}
	return (0);
}
