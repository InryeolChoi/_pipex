/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:52:02 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/04 14:54:19 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info_bonus.h"

void	create_pipe(t_box *tools)
{
	if (pipe(tools->pipe) < 0)
		exit_cmd(PIPE_ERROR, tools);
}

static void	parent(t_box *tools)
{
	if (close(tools->pipe[WRITE]) == -1)
		exit_cmd(CLOSE_FAIL, tools);
	if (dup2(tools->pipe[READ], STDIN_FILENO) == -1)
		exit_cmd(DUP2_FAIL, tools);
	if (close(tools->pipe[READ]) == -1)
		exit_cmd(CLOSE_FAIL, tools);
}

void	heredoc_start(t_box *tools)
{
	tools->infile_fd = open(HEREDOC_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tools->infile_fd == -1)
		exit_cmd(NO_FILE, tools);
}

void	set_process(t_box *tools)
{
	int	i;
	int	status;

	i = 0;
	if (tools->flag == 1)
		heredoc_start(tools);
	while (i < tools->cmd_num)
	{
		create_pipe(tools);
		tools->pid = fork();
		if (tools->pid == -1)
			exit_cmd(FORK_ERROR, tools);
		else if (tools->pid == 0)
			child(tools, i);
		else
			parent(tools);
		i++;
	}
	i = 0;
	while (i < tools->cmd_num)
	{
		wait(&status);
		i++;
	}
	free_tools(tools);
}
