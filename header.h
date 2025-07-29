/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amugisha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:01 by amugisha          #+#    #+#             */
/*   Updated: 2025/01/14 22:34:47 by amugisha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

typedef struct s_vars {
	int		pipefd[2];
	int		arg;
	pid_t	pid[2];
	char	**envp;
	char	**argv;
	char	*path[2];
}				t_vars;

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*get_command(char *repo, char *command);
void	job_fork1(t_vars *vars);
void	job_fork2(t_vars *vars);
void	get_var(char *argv, char **env, char **command, int *ok);
void	redirection_input_file(char **argv, int *pipfd);
void	redirection_output_file(char **argv, int *pipfd);
void	fail_fd(int *fd, int *pipefd);
void	redirection1(int *fd, int *pipefd);
void	redirection2(int *pipefd, char *output_file);
void	command(char *argv, char **path, int i, char **envp);
void	execution(char **arg_command, char **path, int i, char **envp);
int		get_path(t_vars *vars, int i);
void	free_tab(char **tab);
void	free_path(char **path);
void	close_pipe(int *pipefd);
void	wait_for_all(pid_t *pid, char **path);
int		var_path(char *argv, char **envp, char **command);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		len(char *str);
int		len_tab(char **tab);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
