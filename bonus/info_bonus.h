/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inchoi <inchoi@student.42Seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:56:38 by inchoi            #+#    #+#             */
/*   Updated: 2023/08/04 14:57:22 by inchoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_BONUS_H
# define INFO_BONUS_H

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
# define MALLOC_FAIL 100
# define WRONG_PATH 101
# define PIPE_ERROR 102
# define FORK_ERROR 103
# define WRONG_SPLIT 104
# define NO_FILE 105
# define EXEC_FAIL 106
# define LINE_STOP 107
# define DUP2_FAIL 108
# define CLOSE_FAIL 109
# define HEREDOC_FILE "./infile_for_header"

typedef struct s_box
{
	int		cmd_num;
	char	*infile;
	char	*outfile;
	char	**env;
	char	**path;
	char	***cmd_org;
	char	**cmd;
	int		infile_fd;
	int		outfile_fd;
	int		pipe[2];
	pid_t	pid;
	int		flag;
	char	*limiter;
}	t_box;

void	free_double(char **box);
void	free_tools(t_box *tools);
void	exit_cmd(int r, t_box *tools);
char	**get_path(char **env);
void	set_process(t_box *tools);
void	create_pipe(t_box *tools);
void	child(t_box *tools, int i);

#endif
