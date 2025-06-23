/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:16:39 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/23 16:17:34 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**path_dir;
	char	*path_env;
	char	*full_path;
	char	*cmd_path;
	int		i;

	path_env = finder_path(envp);
	if (!path_env)
		return (NULL);
	path_dir = ft_split(path_env, ':');
	if (!path_dir)
		return (NULL);
	i = 0;
	while (path_dir[i])
	{
		full_path = ft_strjoin(path_dir[i], "/");
		cmd_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (ft_free_split(path_dir), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_split(path_dir), NULL);
}

void	exec(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		perror("Invalid command");
		exit(1);
	}
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		ft_free_split(args);
		perror("Command not found");
		exit(1);
	}
	execve(cmd_path, args, envp);
	perror("execve failed");
	free(cmd_path);
	ft_free_split(args);
	exit(1);
}

void	child(char **av, char **envp, int *pipe_fd)
{
	int	infile_fd;

	infile_fd = open(av[1], O_RDONLY);
	if (infile_fd < 0)
	{
		perror("cant open infile");
		exit(1);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec(av[2], envp);
}

void	parent(char **av, char **envp, int *pipe_fd)
{
	int	outfile_fd;

	outfile_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror("cant open outfile");
		exit(0);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	exec(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (ac != 5)
		return (ft_putstr_fd("Error in argument\n", 2), 1);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		child(av, envp, pipe_fd);
	else
		parent(av, envp, pipe_fd);
}
