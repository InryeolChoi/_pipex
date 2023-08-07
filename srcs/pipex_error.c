/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:04:05 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/03 16:05:31 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_info.h"

static void	exit_error_1(int reason, t_box *tools)
{
	if (reason == WRONG_PATH)
	{
		free(tools);
		exit(1);
	}
	if (reason == PIPE_ERROR)
		ft_putstr_fd("failure : allocating pipes", 2);
	else if (reason == FORK_ERROR)
		ft_putstr_fd("failure : fork error", 2);
	else if (reason == WRONG_SPLIT)
	{
		free_double(tools->path);
		free(tools);
		ft_putstr_fd("failure : wrong split", 2);
	}
	exit(1);
}

static void	exit_error_2(int reason, t_box *tools)
{
	if (reason == NO_FILE)
	{
		ft_putstr_fd(tools->infile, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	else if (reason == DUP2_FAIL)
		perror(tools->infile);
	else if (reason == CLOSE_FAIL)
		perror(tools->infile);
	free_tools(tools);
	exit(1);
}

static void	exit_error_3(int reason, t_box *tools)
{
	if (reason == EXEC_ERROR_1)
		perror(*tools->cmd1);
	else if (reason == EXEC_ERROR_2)
		perror(*tools->cmd2);
	free_tools(tools);
	exit(1);
}

void	exit_error(int r, t_box *tools)
{
	if (r == PIPE_ERROR || r == FORK_ERROR || \
			r == WRONG_SPLIT || r == WRONG_PATH)
		exit_error_1(r, tools);
	else if (r == NO_FILE || r == DUP2_FAIL || r == CLOSE_FAIL)
		exit_error_2(r, tools);
	else if (r == EXEC_ERROR_1 || r == EXEC_ERROR_2)
		exit_error_3(r, tools);
}
