/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:26:45 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/05 11:48:39 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info_bonus.h"

static void	set_tools(int ac, char **av, char **env, t_box *tools)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && \
		ft_strlen(av[1]) == 8)
	{
		tools->flag = 1;
		tools->limiter = av[2];
		tools->cmd_num = ac - 4;
	}
	else
	{
		tools->flag = 0;
		tools->infile = av[1];
		tools->cmd_num = ac - 3;
		tools->infile_fd = open(tools->infile, O_RDONLY);
	}
	tools->outfile = av[ac - 1];
	tools->env = env;
	tools->path = get_path(env);
	if (!tools->path)
		exit_cmd(WRONG_SPLIT, tools);
}

static void	set_cmd(char **av, t_box *tools)
{
	int	i;
	int	x;

	tools->cmd = (char ***)malloc(tools->cmd_num * sizeof(char **));
	if (!tools->cmd)
		exit_cmd(MALLOC_FAIL, tools);
	i = 0;
	if (tools->flag == 1)
		x = 3;
	else
		x = 2;
	while (i < tools->cmd_num)
	{
		tools->cmd[i] = ft_split(av[x++], ' ');
		if (!tools->cmd[i])
			exit_cmd(WRONG_SPLIT, tools);
		i++;
	}
}

static char	*join_check(char **path, char *s1)
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

static void	set_cmd_abs(t_box *tools)
{
	int	i;

	tools->cmd_abs = (char **)malloc(tools->cmd_num * sizeof(char *));
	if (!tools->cmd_abs)
		exit_cmd(MALLOC_FAIL, tools);
	i = 0;
	while (i < tools->cmd_num)
	{
		tools->cmd_abs[i] = join_check(tools->path, tools->cmd[i][0]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_box	*tools;

	if (ac < 5)
	{
		ft_putstr_fd("wrong inputs", 2);
		return (2);
	}
	tools = (t_box *)malloc(sizeof(t_box));
	if (!tools)
		return (1);
	set_tools(ac, av, env, tools);
	set_cmd(av, tools);
	set_cmd_abs(tools);
	if (tools->flag == 0)
	{
		tools->outfile_fd = open(tools->outfile, \
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else if (tools->flag == 1)
	{
		tools->outfile_fd = open(tools->outfile, \
				O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	set_process(tools);
}
