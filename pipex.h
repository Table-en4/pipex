/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:17:45 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/22 18:21:30 by molapoug         ###   ########.fr       */
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
 *#---fonctions with char---#*
 *#-------------------------#*/
char	*get_next_line(int fd);
char	*ft_strdu(char *s);
char	*t_strjoin(char *s1, char *s2);

/*#-------------------------#*
 *----fonctions with int----#*
 *--------------------------#*/
int		t_strlen(char *s);

/*#-------------------------#*
 *#---fonctions with void---#*
 *#-------------------------#*/
void	*finder_path(char **envp);
void	ft_free_split(char **result);
void	exec(char *cmd, char **envp);

#endif
