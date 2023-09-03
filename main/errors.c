/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 00:14:21 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/03 17:22:07 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(t_ms *ms, int exitnumber, char *txt, char *txt2)
{
	ft_putstr_fd("minishell: ", 2);
	if (txt)
		ft_putstr_fd(txt, 2);
	if (txt2 && ft_strlen(txt2) > 0)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(txt2, 2);
	}
	ft_putstr_fd("\n", 2);
	if (ms->array_env)
		free_doublechar(ms->array_env);
	ms->exitstatus = exitnumber;
	return (exitnumber);
}

int	ft_error2(int exitnumber, char *txt, char *txt2, char *txt3)
{
	ft_putstr_fd("minishell: ", 2);
	if (txt)
		ft_putstr_fd(txt, 2);
	if (txt2)
		ft_putstr_fd(txt2, 2);
	if (txt3)
		ft_putstr_fd(txt3, 2);
	ft_putstr_fd("\n", 2);
	return (exitnumber);
}

int	ft_error3(int exitnumber, char *txt, char *txt2, char *txt3)
{
	if (txt)
		ft_putstr_fd(txt, 2);
	if (txt2 && ft_strlen(txt2) > 0)
	{
		ft_putstr_fd(": ", 2);
		if (txt3 && !ft_strncmp(txt3, "not a valid identifier", 23))
			ft_putchar_fd('`', 2);
		ft_putstr_fd(txt2, 2);
		if (txt3 && !ft_strncmp(txt3, "not a valid identifier", 23))
			ft_putchar_fd('\'', 2);
	}
	if (txt3 && ft_strlen(txt3) > 0)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(txt3, 2);
	}
	ft_putstr_fd("\n", 2);
	return (exitnumber);
}

int	ft_error4(int exitnumber, char *txt, char *txt2, char *txt3)
{
	ft_putstr_fd("minishell: ", 2);
	if (txt)
		ft_putstr_fd(txt, 2);
	if (txt2 && ft_strlen(txt2) > 0)
	{
		ft_putstr_fd(": ", 2);
		if (txt3 && !ft_strncmp(txt3, "not a valid identifier", 23))
			ft_putchar_fd('`', 2);
		ft_putstr_fd(txt2, 2);
		if (txt3 && !ft_strncmp(txt3, "not a valid identifier", 23))
			ft_putchar_fd('\'', 2);
	}
	if (txt3 && ft_strlen(txt3) > 0)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(txt3, 2);
	}
	ft_putstr_fd("\n", 2);
	return (exitnumber);
}
