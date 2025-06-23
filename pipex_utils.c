/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:06:07 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/23 20:48:51 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **result)
{
	int	j;

	j = 0;
	if (!result)
		return ;
	while (result[j])
	{
		free(result[j]);
		j++;
	}
	free(result);
}

void	*finder_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	win_norme(char *cmd_path, char **args, char **envp)
{
	execve(cmd_path, args, envp);
	perror("execve failed");
	free(cmd_path);
	ft_free_split(args);
	exit(1);
}

char	*find_path(char *cmd, char **envp)
{
	char	**path_dir;
	char	*path_env;
	char	*full_path;
	char	*cmd_path;
	int		i;

	path_dir = NULL;
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
		if (args)
			ft_free_split(args);
		perror("Invalid command");
		exit(127);
	}
	if (ft_strchr(args[0], '/'))
		cmd_path = args[0];
	else
		cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		ft_free_split(args);
		perror("Command not found");
		exit(127);
	}
	win_norme(cmd_path, args, envp);
}
