/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:53:57 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/22 19:25:34 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_bonus(char **av, char **envp, int in_fd, int out_fd)
{
	(void)av;
	(void)envp;
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void	open_infile(char *filename, int *in_fd)
{
	*in_fd = open(filename, O_RDONLY);
	if (*in_fd < 0)
	{
		perror("cant open infile");
		exit(1);
	}
}

void	open_outfile(char *filename, int *out_fd)
{
	*out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out_fd < 0)
	{
		perror("cant open outfile");
		exit(1);
	}
}

void	create_pipe_and_fork(int *pipe_fd, pid_t *pid)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		exit(1);
	}
}

void	execute_cmd(char *cmd, char **envp, int in_fd, int out_fd)
{
	child_bonus(NULL, NULL, in_fd, out_fd);
	exec(cmd, envp);
}

void	process_first_cmd(char **av, char **envp, int *prev_fd)
{
	int		pipe_fd[2];
	int		infile_fd;
	pid_t	pid;

	create_pipe_and_fork(pipe_fd, &pid);
	if (pid == 0)
	{
		open_infile(av[1], &infile_fd);
		close(pipe_fd[0]);
		execute_cmd(av[2], envp, infile_fd, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

void	process_middle_cmd(char *cmd, char **envp, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		old_fd;

	old_fd = *prev_fd;
	create_pipe_and_fork(pipe_fd, &pid);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		execute_cmd(cmd, envp, old_fd, pipe_fd[1]);
	}
	close(old_fd);
	close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

void	process_last_cmd(char *cmd, char **envp, int prev_fd, char *outfile)
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
	process_first_cmd(av, envp, &prev_fd);
	i = 3;
	while (i < ac - 2)
	{
		process_middle_cmd(av[i], envp, &prev_fd);
		i++;
	}
	process_last_cmd(av[ac - 2], envp, prev_fd, av[ac - 1]);
	while (wait(NULL) > 0)
		;
	return (0);
}
