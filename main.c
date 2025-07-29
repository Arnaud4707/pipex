/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:44:25 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/21 20:31:53 by amugisha         ###   ########.fr       */
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

void	create_file_out(char *output_file)
{
	int	fd;

	fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd);
}

int	check_arg(t_vars *vars, int *error)
{
	int	i;

	if (vars->arg != 5)
	{
		write(1, "./pipex file1 cmd1 cmd2 file2\n", 30);
		exit(127);
	}
	i = 0;
	while (i < vars->arg)
	{
		if (ft_strncmp(vars->argv[i], "", 1) == 0)
		{
			write(1, "./pipex file1 cmd1 cmd2 file2\n", 30);
			exit(127);
		}
		i++;
	}
	create_file_out(vars->argv[4]);
	if (access(vars->argv[1], F_OK) != 0)
	{
		perror("Ne trouve pas le fichier");
		*error = *error - 1;
		return (EXIT_FAILURE);
	}
	return (0);
}

void	free_path(char **path)
{
	if (path[0])
		free(path[0]);
	if (path[1])
		free(path[1]);
}

int	main(int arg, char **argv, char **envp)
{
	t_vars	vars;
	int		error;

	vars.path[0] = NULL;
	vars.path[1] = NULL;
	vars.arg = arg;
	vars.argv = argv;
	vars.envp = envp;
	error = get_path(&vars, check_arg(&vars, &error));
	if (pipe(vars.pipefd) == -1)
	{
		perror("Erreur lors du pipe");
		free_path(vars.path);
		exit(EXIT_FAILURE);
	}
	if (vars.path[0])
		job_fork1(&vars);
	if (vars.path[1])
		job_fork2(&vars);
	close_pipe(vars.pipefd);
	wait_for_all(vars.pid, vars.path);
	free_path(vars.path);
	if (error)
		exit(127);
	return (0);
}
