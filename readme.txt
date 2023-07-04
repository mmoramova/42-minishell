int	ft_child_process(char **argv, char **env, int *fd)
{
	int	file;

	file = open(argv[1], O_RDONLY, 0666);
	if (file == -1)
		ft_exit(errno, argv[1], strerror(errno));
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	ft_close(fd, file);
	ft_execve_prepare(argv[2], env);
	return (0);
}

int	ft_parent_process(char **argv, char **env, int *fd)
{
	int	file;

	file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	//open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (file == -1)
		ft_exit(1, argv[4], strerror(errno));
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	ft_close(fd, file);
	ft_execve_prepare(argv[3], env);
	return (0);
}
