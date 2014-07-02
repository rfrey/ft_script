/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 17:27:44 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/04 19:26:53 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "script.h"
#include "libft.h"

void	send_cmd(int ptymst)
{
	int		ret;
	char	buf[1024];

	ret = read(0, buf, 1023);
	if (ret > 0)
		write(ptymst, buf, ret);
}

void	get_result(int ptymst, int fd, int tl)
{
	int		ret;
	char	buf[1024];

	ret = read(ptymst, buf, 1023);
	if (ret > 0)
	{
		write(1, buf, ret);
		write(fd, buf, ret);
	}
	++tl;
}

void	put_header(int fd, t_script data)
{
	struct timeval	now;

	if (!data.opt_q)
	{
		ft_putstr("Script started, output file is ");
		ft_putendl(data.file);
		gettimeofday(&now, NULL);
		ft_putstr_fd("Script started on ", fd);
		ft_putstr_fd(ctime(&now.tv_sec), fd);
	}
}

void	put_footer(int fd, t_script data)
{
	struct timeval	now;

	if (!data.opt_q)
	{
		ft_putstr("\nScript done, output file is ");
		ft_putendl(data.file);
		gettimeofday(&now, NULL);
		ft_putstr_fd("\nScript done on ", fd);
		ft_putstr_fd(ctime(&now.tv_sec), fd);
	}
}
