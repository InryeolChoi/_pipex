/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_info.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:57:41 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/03 16:10:42 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_INFO_H
# define PIPEX_INFO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"

# define READ 0
# define WRITE 1
# define WRONG_PATH 100
# define PIPE_ERROR 101
# define FORK_ERROR 102
# define WRONG_SPLIT 103
# define NO_FILE 104
# define EXEC_ERROR_1 105
# define EXEC_ERROR_2 106
# define DUP2_FAIL 107
# define CLOSE_FAIL 108

typedef struct s_box
{
	int		cmd_num;
	char	**env;
	char	**path;
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	*cmd_abs1;
	char	*cmd_abs2;
	int		infile_fd;
	int		outfile_fd;
	int		pipe[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_box;

void	free_double(char **box);
int		put_error(void);
void	put_exit(t_box *tools);
void	exit_error(int reason, t_box *tools);
void	free_tools(t_box *tools);
void	set_process(t_box *tools);

#endif
