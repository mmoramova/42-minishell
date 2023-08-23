/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:19:08 by josorteg          #+#    #+#             */
/*   Updated: 2023/08/24 00:08:23 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void handle_sigint(int sig)
{
	//rl_catch_signals = 0;

	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}

}

void	handle_siginth(int sig) //heredoc
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(1);
	}

}

void	handle_sigintp(int sig) //execution
{
	write(2,"a",1);
	if (sig == SIGINT) //control c
	{

		printf("^C\n");
		exit(130);
	}

	if (sig == SIGQUIT) //control contrabarra
	{
		printf("^\\Quit 3\n");
		exit(131);
	}
}



// void	handle_sigint(int sig)
// {
// 	if (g_process == 0)
// 		process_0(sig);
// 	else if (g_process == 1) //execution
// 		process_1(sig);
// 	else if (g_process == 2) //heredoc hijo
// 		process_2(sig);

// }



