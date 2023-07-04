/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:17 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/04 15:45:20 by mmoramov         ###   ########.fr       */
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
	t_tok *tokens;

	if (ft_checkinput(*ms) == 1)
	{
		//TODO ERROR
		exit(1);
	}
	ms->start = ft_split_tok(ms->line, ' ');


	/*token only for printing:*/
	tokens = ms->start;
	while (tokens)
	{

		printf("%s || ", tokens->content);
		printf("%d\n", tokens->type);
		tokens=tokens->next;
	}
}

int	main(int argc, char **argv) //, char *env[])
{
	t_ms	ms;

	ms.start = NULL;
	if (argc != 1 && argv[0])
		return(1);

	//ms.env = get_env(env);

	//print enviroment (like env, only for test)
	//print_env(ms.env);
	//printf("%s\n",get_env_value(ms.env ,"PATH"));

	while (1)
	{
		ms.line = readline("minishell>");
		if (ms.line && strlen(ms.line) > 0)
		{
			ft_parse(&ms);
			add_history(ms.line);
		}
	}
	return (0);
}
