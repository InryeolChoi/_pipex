/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:34:35 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/04 14:37:21 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info_bonus.h"

static void	heredoc_exec(t_box *tools)
{
	size_t	lim_len;
	char	*str;

	lim_len = ft_strlen(tools->limiter);
	while (1)
	{
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		if (!str)
			break ;
		if (ft_strncmp(tools->limiter, str, lim_len) == 0 && \
				ft_strlen(str) == lim_len + 1)
			break ;
		write(tools->infile_fd, str, ft_strlen(str));
		free(str);
	}
}

static void	zero_child(t_box *tools)
{
	if (tools->infile_fd == -1)
		exit_cmd(NO_FILE, tools);
	if (dup2(tools->infile_fd, STDIN_FILENO) == -1)
		exit_cmd(DUP2_FAIL, tools);
	if (close(tools->infile_fd) == -1)
		exit_cmd(CLOSE_FAIL, tools);
	if (dup2(tools->pipe[WRITE], STDOUT_FILENO) == -1)
		exit_cmd(DUP2_FAIL, tools);
	if (close(tools->pipe[WRITE]) == -1)
		exit_cmd(CLOSE_FAIL, tools);
}

static void	middle_child(t_box *tools)
{
	if (dup2(tools->pipe[WRITE], STDOUT_FILENO) == -1)
		exit_cmd(DUP2_FAIL, tools);
	if (close(tools->pipe[WRITE]) == -1)
		exit_cmd(CLOSE_FAIL, tools);
}

static void	last_child(t_box *tools)
{
	if (tools->outfile_fd == -1)
		exit_cmd(NO_FILE, tools);
	if (close(tools->pipe[WRITE]) == -1)
		exit_cmd(CLOSE_FAIL, tools);
	if (dup2(tools->outfile_fd, STDOUT_FILENO) == -1)
		exit_cmd(DUP2_FAIL, tools);
	if (close(tools->outfile_fd) == -1)
		exit_cmd(CLOSE_FAIL, tools);
}

void	child(t_box *tools, int i)
{
	close(tools->pipe[READ]);
	if (i == 0)
	{
		if (tools->flag == 1)
			heredoc_exec(tools);
		zero_child(tools);
	}
	else if (i == tools->cmd_num - 1)
		last_child(tools);
	else
		middle_child(tools);
	if (execve(tools->cmd[i], tools->cmd_org[i], tools->env) == -1)
		exit_cmd(EXEC_FAIL, tools);
}
