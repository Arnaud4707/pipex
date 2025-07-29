/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:54:04 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/14 22:39:11 by amugisha         ###   ########.fr       */
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

void	command(char *argv, char **path, int i, char **envp)
{
	char	**arg_command;

	arg_command = ft_split(argv, ' ');
	execution(arg_command, path, i, envp);
}

void	execution(char **arg_command, char **path, int i, char **envp)
{
	char	**args;
	int		n;

	n = len_tab(arg_command);
	args = malloc ((n + 1) * sizeof(char *));
	args[n] = NULL;
	while (n > 1)
	{
		n--;
		args[n] = arg_command[n];
	}
	args[0] = path[i];
	if (execve(args[0], args, envp) == -1)
	{
		perror("Erreur lors de execve");
		free_path(path);
		free(args);
		free_tab(arg_command);
		exit(127);
	}
	free(args);
	free_tab(arg_command);
}
