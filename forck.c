/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forck.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:51:47 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/14 22:24:44 by amugisha         ###   ########.fr       */
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

void	job_fork1(t_vars *vars)
{
	vars->pid[0] = fork();
	if (vars->pid[0] == -1)
	{
		perror("Erreur lors de fork");
		exit(EXIT_FAILURE);
	}
	if (vars->pid[0] == 0)
	{
		redirection_input_file(vars->argv, vars->pipefd);
		command(vars->argv[2], vars->path, 0, vars->envp);
	}
}

void	job_fork2(t_vars *vars)
{
	vars->pid[1] = fork();
	if (vars->pid[1] == -1)
	{
		perror("Erreur lors de fork");
		exit(EXIT_FAILURE);
	}
	if (vars->pid[1] == 0)
	{
		redirection_output_file(vars->argv, vars->pipefd);
		command(vars->argv[3], vars->path, 1, vars->envp);
	}
}
