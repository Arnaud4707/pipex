/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:20:44 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/14 22:45:00 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "header.h"

char	*get_command(char *repo, char *command)
{
	char	*str;
	char	*tmp;

	if (command[0] == '/')
		tmp = ft_strdup(command);
	else if (command[0] == '.')
		return (NULL);
	else
	{
		str = ft_strjoin(repo, "/");
		tmp = ft_strjoin(str, command);
		free(str);
	}
	if (access(tmp, F_OK | X_OK) == 0)
		return (tmp);
	free(tmp);
	return (NULL);
}

void	get_var(char *argv, char **env, char **command, int *ok)
{
	char	**commande;
	int		j;
	char	**repos;

	commande = ft_split(argv, '=');
	if (ft_strncmp(env[0], "PATH", 4) == 0)
	{
		j = 0;
		repos = ft_split(env[1], ':');
		while (repos[j] && *ok == 0)
		{
			*command = get_command(repos[j], commande[0]);
			if (*command != NULL)
				*ok = *ok + 1;
			if (*ok == 0 && *command)
				free(*command);
			j++;
		}
		free_tab(repos);
	}
	free_tab(commande);
}

int	var_path(char *argv, char **envp, char **command)
{
	int		i;
	char	**env;
	int		ok;

	i = 0;
	ok = 0;
	while (envp[i])
	{
		env = ft_split(envp[i], '=');
		get_var(argv, env, command, &ok);
		free_tab(env);
		i++;
	}
	if (ok == 0)
		return (-1);
	return (0);
}

int	r_directory(int com, char *str, char **path)
{
	int		i;
	char	**command;

	i = 0;
	if (com == -1)
	{
		if (len(str) < 3 || str[0] != '.' || str[1] != '/')
			return (-1);
		command = ft_split(str, ' ');
		*path = malloc ((len(command[0])) * sizeof(char));
		if (!*path)
			return (-1);
		ft_strlcpy(*path, (char *)(command[0] + 2), len(command[0]));
		if (access(*path, X_OK) == 0)
		{
			free(*path);
			*path = ft_strdup(command[0]);
			free_tab(command);
			return (0);
		}
		free_tab(command);
		free(*path);
		*path = NULL;
	}
	return (com);
}

int	get_path(t_vars *vars, int f)
{
	int	com1;
	int	com2;

	com1 = r_directory(var_path(vars->argv[2], vars->envp, &(vars->path[0])),
			vars->argv[2], &(vars->path[0]));
	com2 = r_directory(var_path(vars->argv[3], vars->envp, &(vars->path[1])),
			vars->argv[3], &(vars->path[1]));
	if (f != 0)
	{
		free(vars->path[0]);
		vars->path[0] = NULL;
	}
	if (com1 == -1 || com2 == -1)
	{
		if (com1 == -1 && f == 0)
		{
			perror("command pas trouver");
		}
		if (com2 == -1)
		{
			perror("command pas trouver");
			return (EXIT_FAILURE);
		}
	}
	return (0);
}
