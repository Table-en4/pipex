/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:16:39 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/21 18:01:48 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	int	fd;
	static char	*line;

	if (ac <= 1)
		return (perror("invalid argument"), 1);
	fd = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("fail to open file"), 1);
	ft_putstr_fd("test d'une string\n a ecrire dans mon fichier\nsansleak", fd);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("%d\n", access(av[1], R_OK | W_OK | F_OK | W_OK | X_OK));
	ft_printf("y a pa eu d'erreur gg\n");
	close(fd);
}
