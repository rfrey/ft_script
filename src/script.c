/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 15:34:40 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/04 19:26:09 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "libft.h"
#include "script.h"

static int	get_file_fd(t_script data)
{
	int		fd;
	int		rights;

	rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (data.opt_a)
		fd = open(data.file, O_CREAT | O_APPEND | O_WRONLY, rights);
	else
		fd = open(data.file, O_CREAT | O_WRONLY | O_TRUNC, rights);
	return (fd);
}

int			init_pty(int pty)
{
	setsid();
	if (ioctl(pty, TIOCSCTTY, NULL) == -1)
		return (-1);
	dup2(pty, 0);
	dup2(pty, 1);
	dup2(pty, 2);
	if (pty > 2)
		close(pty);
	return (0);
}

static void	handle_son(t_script data)
{
	char	*args[4];

	args[0] = data.shell;
	args[1] = "-i";
	args[2] = NULL;
	if (data.cmd)
	{
		args[1] = "-c";
		args[2] = data.cmd;
		args[3] = NULL;
	}
	close(data.ptymst);
	if (init_pty(data.ptyslv) == -1)
	{
		ft_putendl("init_pty error");
		return ;
	}
	if (execve(data.shell, args, data.envp) == -1)
	{
		ft_putendl("execve error");
		return ;
	}
}

static void	handle_father(t_script data, pid_t son_pid)
{
	int		fd;
	int		status;
	fd_set	set;

	if ((fd = get_file_fd(data)) == -1)
	{
		ft_putendl("open error");
		return ;
	}
	close(data.ptyslv);
	FD_ZERO(&set);
	put_header(fd, data);
	while (waitpid(son_pid, &status, WNOHANG) != son_pid)
	{
		FD_SET(0, &set);
		FD_SET(data.ptymst, &set);
		select(data.ptymst + 1, &set, NULL, NULL, NULL);
		if (FD_ISSET(0, &set))
			send_cmd(data.ptymst);
		if (FD_ISSET(data.ptymst, &set))
			get_result(data.ptymst, fd, data.time);
	}
	put_footer(fd, data);
}

void		script(t_script data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_son(data);
	else if (pid > 0)
		handle_father(data, pid);
	else
		ft_putendl("fork error");
}
