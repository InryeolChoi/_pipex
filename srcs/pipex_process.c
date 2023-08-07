/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:07:20 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/03 16:09:01 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_info.h"

static void	close_pipe(t_box *tools)
{
	if (close(tools->pipe[WRITE]) == -1)
		exit_error(CLOSE_FAIL, tools);
	if (close(tools->pipe[READ]) == -1)
		exit_error(CLOSE_FAIL, tools);
}

static void	first_child(t_box *tools)
{
	if (access(tools->infile, F_OK) == -1)
		exit_error(NO_FILE, tools);
	if (dup2(tools->infile_fd, STDIN_FILENO) == -1)
		exit_error(DUP2_FAIL, tools);
	if (close(tools->infile_fd) == -1)
		exit_error(CLOSE_FAIL, tools);
	if (dup2(tools->pipe[WRITE], STDOUT_FILENO) == -1)
		exit_error(DUP2_FAIL, tools);
	close_pipe(tools);
	if (!tools->cmd_abs1)
		exit_error(EXEC_ERROR_1, tools);
	else if (execve(tools->cmd_abs1, tools->cmd1, tools->env) < 0)
		exit_error(EXEC_ERROR_1, tools);
}

static void	second_child(t_box *tools)
{
	if (dup2(tools->pipe[READ], STDIN_FILENO) == -1)
		exit_error(DUP2_FAIL, tools);
	close_pipe(tools);
	if (dup2(tools->outfile_fd, STDOUT_FILENO) == -1)
		exit_error(DUP2_FAIL, tools);
	if (close(tools->outfile_fd) == -1)
		exit_error(CLOSE_FAIL, tools);
	if (access(tools->cmd_abs2, X_OK) == -1)
		exit_error(EXEC_ERROR_2, tools);
	if (!tools->cmd_abs2)
		exit_error(EXEC_ERROR_2, tools);
	else if (execve(tools->cmd_abs2, tools->cmd2, tools->env) < 0)
		exit_error(EXEC_ERROR_2, tools);
}

void	set_process(t_box *tools)
{
	int	i;

	i = 0;
	if (pipe(tools->pipe) < 0)
		exit_error(PIPE_ERROR, tools);
	tools->pid1 = fork();
	if (tools->pid1 == -1)
		exit_error(FORK_ERROR, tools);
	if (tools->pid1 == 0)
		first_child(tools);
	tools->pid2 = fork();
	if (tools->pid2 == -1)
		exit_error(FORK_ERROR, tools);
	if (tools->pid2 == 0)
		second_child(tools);
	close_pipe(tools);
	waitpid(tools->pid1, NULL, 0);
	waitpid(tools->pid2, NULL, 0);
	free_tools(tools);
}
