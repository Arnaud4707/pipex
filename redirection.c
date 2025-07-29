/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:55:34 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/14 22:43:36 by amugisha         ###   ########.fr       */
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

void	redirection_input_file(char **argv, int *pipfd)
{
	char	*input_file;
	int		fd;

	fd = -1;
	if (access(argv[1], F_OK) != 0)
		redirection1(&fd, pipfd);
	else
	{
		input_file = argv[1];
		fd = open(input_file, O_RDONLY);
		if (fd == -1)
		{
			perror("Erreur lors de l'ouverture du fichier");
			exit(EXIT_FAILURE);
		}
		redirection1(&fd, pipfd);
	}
}

void	fail_fd(int *fd, int *pipefd)
{
	if (*fd == -1)
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("Erreur lors de dup2 pour l'entrée");
			close_pipe(pipefd);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(*fd, STDIN_FILENO) == -1)
		{
			perror("Erreur lors de dup2 pour l'entrée");
			close(*fd);
			close_pipe(pipefd);
			exit(EXIT_FAILURE);
		}
		close(*fd);
	}
	close(pipefd[0]);
}

void	redirection1(int *fd, int *pipefd)
{
	fail_fd(fd, pipefd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("Erreur lors de dup2 pour la sortie");
		close_pipe(pipefd);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
}

void	redirection_output_file(char **argv, int *pipfd)
{
	redirection2(pipfd, argv[4]);
}

void	redirection2(int *pipefd, char *output_file)
{
	int	fd;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("Erreur lors de dup2 pour l'entrée");
		close_pipe(pipefd);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Erreur lors de dup2 pour la sortie");
		close_pipe(pipefd);
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}
