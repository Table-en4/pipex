/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:17:45 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/23 16:10:19 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

/*#-------------------------#*
 *----fonctions with int----#*
 *--------------------------#*/
int		t_strlen(char *s);
int		parse_heredoc(char **av, char **envp, int *prev_fd);
int		set_pause(char *limiter, int *here_doc);

/*#-------------------------#*
 *#---fonctions with void---#*
 *#-------------------------#*/
void	*finder_path(char **envp);
void	ft_free_split(char **result);
void	exec(char *cmd, char **envp);
void	child_bonus(char **av, char **envp, int in_fd, int out_fd);
void	open_infile(char *filename, int *in_fd);
void	open_outfile(char *filename, int *out_fd);
void	pipe_fork(int *pipe_fd, pid_t *pid);
void	execute_cmd(char *cmd, char **envp, int in_fd, int out_fd);
void	here_doc_ges(int *fd, char *limiter);
void	cmd_heredoc(char *cmd, char **envp, int heredeoc, int *prev_fd);
void	err_gest(int a);

#endif
