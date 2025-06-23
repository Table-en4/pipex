/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:16:39 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/23 20:30:41 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		wait(NULL);
		exit(1);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	wait(NULL);
	exec(av[3], envp);
}

/*int	main(int ac, char **av, char **envp)
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
}*/
