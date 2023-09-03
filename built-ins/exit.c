/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:43:43 by josorteg          #+#    #+#             */
/*   Updated: 2023/09/03 15:30:14 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_finish(void)
{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	clear_history();
}

int	ft_atoi_longchecker(const char *str)
{
	int					i;
	unsigned long long	nbr;
	int					sign;

	nbr = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (sign == 1 && nbr > LONG_MAX)
		return (1);
	if (sign == -1 && nbr != 0 && ((nbr - 1) > LONG_MAX))
		return (1);
	return (0);
}

long	ft_atoi_long(const char *str)
{
	int		i;
	long	nbr;
	int		sign;

	nbr = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

int	b_exit_checkinput(char *str)
{
	size_t	i;
	int		isnum;
	int		numlen;

	(0 || (i = 0) || (isnum = 0) || (numlen = 0));
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		(1 && (i = i + 1) && (isnum = 1));
	while (ft_isdigit(str[i]))
	{
		i++;
		isnum = 1;
		numlen++;
	}
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (i == ft_strlen(str) && isnum == 1 && numlen <= 19)
		return (0);
	return (1);
}

int	b_exit(t_ms *ms, char **com, int parent)
{
	int	exitstatus;

	exitstatus = ms->exitstatus;
	if (com[1] && (b_exit_checkinput(com[1]) == 1
			|| ft_atoi_longchecker(com[1]) == 1))
	{
		ft_exit_finish();
		ms->exitstatus = 255;
		ft_error2(255, "exit: ", com[1], ": numeric argument required");
		exit (255);
	}
	else if (com[1] && com[2] != NULL)
	{
		ft_error(ms, 1, com[0], "too many arguments");
		return (1);
	}
	else if (com[1])
		exitstatus = ft_atoi_long(com[1]);
	else
		exitstatus = ms->exitstatus;
	if (parent == 1)
		ft_exit_finish();
	exit(exitstatus);
	return (exitstatus);
}
