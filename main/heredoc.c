/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:17:03 by mmoramov          #+#    #+#             */
/*   Updated: 2023/07/17 23:32:21 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* For now is working, for all combinations < << except one:
	cat <txt4242 <<x --if txt4242 doesnt exists
*/

void	heredoc_read(char *file, int fd[2])
{
	char	*line;

	while(42)
	{
		line = readline("> ");
		if (line && ft_strlen(line) > 0)
		{
			if (ft_strlen(line) == ft_strlen(file)
				&& ft_strncmp(line, file, ft_strlen(file)) == 0)
			{
				free(line);
				exit(0);
			}
			ft_putstr_fd(line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			free(line);
		}
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

int	heredoc_execute(char *file)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit(errno, strerror(errno), NULL);
	pid = fork();
	if (pid == -1)
		ft_exit(errno, strerror(errno), NULL);
	if (pid == 0)
		heredoc_read(file, fd);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return(fd[0]);
}
