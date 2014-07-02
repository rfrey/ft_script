/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/29 19:12:30 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/02 21:48:43 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include "script.h"
#include "libft.h"

static int		get_slv_fd(int fd)
{
	char		filename[1024];
	struct stat	fileinfos;
	int			fd_slv;

	if ((ioctl(fd, TIOCPTYGNAME, filename)) == -1)
	{
		ft_putendl("ioctl error");
		return (-1);
	}
	if (stat(filename, &fileinfos) == -1)
	{
		ft_putendl("ioctl error");
		return (-1);
	}
	if ((fd_slv = open(filename, O_RDWR)) == -1)
	{
		ft_putendl("open error");
		return (-1);
	}
	return (fd_slv);
}

int				getpty(int *ptyslv, int *ptymst)
{
	if ((*ptymst = open("/dev/ptmx", O_RDWR)) == -1)
	{
		ft_putendl("open error");
		return (-1);
	}
	if (ioctl(*ptymst, TIOCPTYGRANT) == -1)
	{
		ft_putendl("ioctl error");
		return (-1);
	}
	if (ioctl(*ptymst, TIOCPTYUNLK))
	{
		ft_putendl("ioctl error");
		return (-1);
	}
	*ptyslv = get_slv_fd(*ptymst);
	return (0);
}
