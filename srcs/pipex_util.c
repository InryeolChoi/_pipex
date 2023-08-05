/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:09:15 by inchoi            #+#    #+#             */
/*   Updated: 2023/07/23 14:11:12 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_info.h"

void	free_double(char **box)
{
	int	i;

	i = 0;
	while (box[i])
		free(box[i++]);
	free(box);
}

int	put_error(void)
{
	ft_putstr_fd("wrong inputs", 2);
	return (2);
}

void	free_tools(t_box *tools)
{
	free_double(tools->path);
	free_double(tools->cmd_org1);
	free_double(tools->cmd_org2);
	free(tools->cmd1);
	free(tools->cmd2);
	free(tools);
}
