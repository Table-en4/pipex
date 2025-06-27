/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:55:02 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/26 16:16:53 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	last_cmd_heredoc(char *cmd, char **envp, int prev_fd, char *outfile)
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
		open_outfile(outfile, &outfile_fd, 2, prev_fd);
		execute_cmd(cmd, envp, prev_fd, outfile_fd);
	}
	close(prev_fd);
}

int	return_pid(void)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	while (wait(&status) > 0)
		exit_code = (status >> 8) & 0xFF;
	return (exit_code);
}

int	parse_heredoc(char **av, char **envp, int *prev_fd)
{
	int	here_doc;

	if (!av[2])
	{
		ft_putstr_fd("Error: add a limiter to the here_doc\n", 2);
		exit(1);
	}
	if (set_pause(av[2], &here_doc) == -1)
		exit(1);
	cmd_heredoc(av[3], envp, here_doc, prev_fd);
	return (4);
}
