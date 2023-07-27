/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:19:08 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/27 17:42:48 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void process_0(int sig)
{
	//rl_catch_signals = 0;

    if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		exit(1);
}

void	process_1(int sig)
{
	if (sig == SIGINT)
	{
		g_exit.status = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		b_exit(0);
	}
	if (sig == SIGQUIT)
	{
		;
	}
}

void	process_2(int sig)
{
	if (sig == SIGINT) //control d
	{
		printf("^C\n");
		g_exit.status = 130;
	}
	if (sig == SIGQUIT) //control
	{
		printf("^\\Quit 3\n");
		g_exit.status = 131;
	}
}



void	handle_sigint(int sig)
{
	if (g_exit.proces == 0)
		process_0(sig);
	else if (g_exit.proces == 1) //heredoc
		process_1(sig);
	else if (g_exit.proces == 2) //execution
		process_2(sig);
}



