/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:48:20 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/23 15:06:59 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*read_line_stdin(void)
{
	char	buffer[10024];
	int		i;
	int		bytes_read;
	char	c;

	i = 0;
	while (i < 10023)
	{
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read <= 0)
			return (NULL);
		buffer[i++] = c;
		if (c == '\n')
			break;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

void	here_doc_ges(int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	write(STDOUT_FILENO, "heredoc> ", 9);
	while (1)
	{
		line = read_line_stdin();
		if (!line)
			break;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && 
			line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "heredoc> ", 9);
	}
	close(fd[1]);
	exit(0);
}

void	cmd_heredoc(char *cmd, char **envp, int heredoc, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe_fork(pipe_fd, &pid);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		execute_cmd(cmd, envp, heredoc, pipe_fd[1]);
	}
	close(heredoc);
	close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

void	err_gest(int a)
{
	if (a == 1)
	{
		perror("pipe");
		exit(1);
	}
	if (a == 2)
	{
		perror("fork");
		exit(1);
	}
}

int	parse_heredoc(char **av, char **envp, int *prev_fd)
{
	int	here_doc;

	if (!av[2])
		return (ft_putstr_fd("add a limiter to the here_doc", 2), 1);
	if (set_pause(av[2], &here_doc) == -1)
		return (1);
	cmd_heredoc(av[3], envp, here_doc, prev_fd);
	return (4);
}
