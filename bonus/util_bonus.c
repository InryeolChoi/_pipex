/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:33:21 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/04 14:34:18 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info_bonus.h"

char	**get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	path = *env + 5;
	return (ft_split(path, ':'));
}

static void	free_cmd(char **box, int x)
{
	int	i;

	i = 0;
	while (i < x)
		free(box[i++]);
	free(box);
}

void	free_double(char **box)
{
	int	i;

	i = 0;
	while (box[i])
		free(box[i++]);
	free(box);
}

void	free_tools(t_box *tools)
{
	int	i;

	i = 0;
	free_double(tools->path);
	while (i < tools->cmd_num)
		free_double(tools->cmd_org[i++]);
	free(tools->cmd_org);
	free_cmd(tools->cmd, tools->cmd_num);
	free(tools);
}
