/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:35:40 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/26 16:19:09 by molapoug         ###   ########.fr       */
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

void	open_infile(char *filename, int *in_fd, int prev_fd)
{
	*in_fd = open(filename, O_RDONLY);
	if (*in_fd < 0)
	{
		perror("cant open infile");
		if (prev_fd != -1)
			close(prev_fd);
		exit(1);
	}
}

void	open_outfile(char *filename, int *out_fd, int a, int prev_fd)
{
	if (a == 1)
	{
		*out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*out_fd < 0)
		{
			perror("Permission denied");
			if (prev_fd != -1)
				close(prev_fd);
			exit(1);
		}
	}
	if (a == 2)
	{
		*out_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*out_fd < 0)
		{
			perror("Permission denied");
			if (prev_fd != -1)
				close(prev_fd);
			exit(1);
		}
	}
}

void	pipe_fork(int *pipe_fd, pid_t *pid)
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
	close(in_fd);
	close(out_fd);
	exit(1);
}
