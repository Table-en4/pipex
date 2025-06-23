/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:53:57 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/23 12:35:03 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



void	first_cmd(char **av, char **envp, int *prev_fd)
{
	int		pipe_fd[2];
	int		infile_fd;
	pid_t	pid;

	pipe_fork(pipe_fd, &pid);
	if (pid == 0)
	{
		open_infile(av[1], &infile_fd);
		close(pipe_fd[0]);
		execute_cmd(av[2], envp, infile_fd, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

void	bridge_cmd(char *cmd, char **envp, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		old_fd;

	old_fd = *prev_fd;
	pipe_fork(pipe_fd, &pid);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		execute_cmd(cmd, envp, old_fd, pipe_fd[1]);
	}
	close(old_fd);
	close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

void	last_cmd(char *cmd, char **envp, int prev_fd, char *outfile)
{
	int		outfile_fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		open_outfile(outfile, &outfile_fd);
		execute_cmd(cmd, envp, prev_fd, outfile_fd);
	}
	close(prev_fd);
}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	prev_fd;

	if (ac < 4)
		return (ft_putstr_fd("Error: need at least 4 arguments\n", 2), 1);
	first_cmd(av, envp, &prev_fd);
	i = 3;
	while (i < ac - 2)
	{
		bridge_cmd(av[i], envp, &prev_fd);
		i++;
	}
	last_cmd(av[ac - 2], envp, prev_fd, av[ac - 1]);
	while (wait(NULL) > 0)
		;
	return (0);
}
