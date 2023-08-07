/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:03:28 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/03 16:09:21 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_info.h"

static char	**get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	path = *env + 5;
	return (ft_split(path, ':'));
}

static char	*get_cmd_abs(char **path, char *s1)
{
	int		i;
	int		result;
	char	*s2;
	char	*s3;

	i = 0;
	s2 = ft_strjoin("/", s1);
	while (path[i])
	{
		s3 = ft_strjoin(path[i], s2);
		result = access(s3, X_OK);
		if (result == 0)
		{
			free(s2);
			return (s3);
		}
		free(s3);
		i++;
	}
	free(s2);
	return (NULL);
}

static void	parse_env(t_box *tools, char **av, char **env)
{
	tools->path = get_path(env);
	if (tools->path == NULL)
		exit_error(WRONG_PATH, tools);
	tools->cmd1 = ft_split(av[2], ' ');
	tools->cmd2 = ft_split(av[3], ' ');
	if (!(tools->cmd1) || !(tools->cmd2))
		exit_error(WRONG_SPLIT, tools);
	tools->cmd_abs1 = get_cmd_abs(tools->path, tools->cmd1[0]);
	tools->cmd_abs2 = get_cmd_abs(tools->path, tools->cmd2[0]);
}

int	main(int ac, char **av, char **env)
{
	t_box	*tools;

	if (ac != 5)
		return (put_error());
	else
	{
		tools = (t_box *)malloc(sizeof(t_box));
		if (!tools)
			return (1);
		tools->infile = av[1];
		tools->outfile = av[ac - 1];
		parse_env(tools, av, env);
		tools->env = env;
		tools->cmd_num = ac - 3;
		tools->infile_fd = open(tools->infile, O_RDONLY);
		tools->outfile_fd = open(tools->outfile, \
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		set_process(tools);
	}
	return (0);
}
