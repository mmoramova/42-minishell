/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:19:08 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/03 15:15:03 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_siginth(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(1);
	}
}

void	handle_sigintp(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
		exit(130);
	}
	if (sig == SIGQUIT)
	{
		printf("^\\Quit 3\n");
		exit(131);
	}
}
