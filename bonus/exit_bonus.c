/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:37:32 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/04 14:38:03 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info_bonus.h"

static void	exit_cmd1(int reason)
{
	if (reason == MALLOC_FAIL)
		ft_putstr_fd("failure : malloc failure\n", 2);
	else if (reason == WRONG_SPLIT)
		ft_putstr_fd("failure : split failure\n", 2);
	exit(1);
}

static void	exit_cmd2(int reason, t_box *tools)
{
	if (reason == PIPE_ERROR)
		ft_putstr_fd("failure : allocating pipes\n", 2);
	else if (reason == FORK_ERROR)
		ft_putstr_fd("failure : fork error\n", 2);
	else if (reason == NO_FILE)
	{
		ft_putstr_fd(tools->infile, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	exit(1);
}

static void	exit_cmd3(t_box *tools)
{
	if (tools->flag == 0)
		perror(tools->infile);
	else if (tools->flag == 1)
		perror("here_doc");
	exit(1);
}

void	exit_cmd(int r, t_box *tools)
{
	if (r == MALLOC_FAIL || r == WRONG_SPLIT)
		exit_cmd1(r);
	else if (r == PIPE_ERROR || r == FORK_ERROR || r == NO_FILE)
		exit_cmd2(r, tools);
	else if (r == DUP2_FAIL || r == CLOSE_FAIL)
		exit_cmd3(tools);
	else if (r == LINE_STOP)
		exit(1);
}

void	execve_fail(char *cmd, t_box *tools)
{
	perror(cmd);
	free_tools(tools);
	exit(1);
}
