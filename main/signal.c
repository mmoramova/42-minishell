/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:19:08 by josorteg          #+#    #+#             */
/*   Updated: 2023/07/25 17:15:45 by josorteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{

        rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
	}
}

