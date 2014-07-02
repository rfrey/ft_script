/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/03 18:02:29 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/04 19:16:43 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "script.h"

static void		bufcat(char *s1, char *s2, int *len1, int len2)
{
	int				i;

	i = 0;
	while (i < len2)
	{
		s1[i + *len1] = s2[i];
		++i;
	}
	*len1 += len2;
}

static void		put_buf(int fd, char *buf, int *size)
{
	write(fd, buf, *size);
	*size = 0;
}

void			output_buffer(int fd, char *buf, int size, int tl)
{
	static time_t	clock = 0;
	struct timeval	now;
	static char		obuf[OUTPUT_BUFFER];
	static int		osize = 0;

	gettimeofday(&now, NULL);
	if (clock == 0)
		clock = now.tv_sec;
	if (osize + size > OUTPUT_BUFFER || size > OUTPUT_BUFFER)
	{
		put_buf(fd, obuf, &osize);
		if (size > OUTPUT_BUFFER)
		{
			write(fd, buf, size);
			return ;
		}
	}
	bufcat(obuf, buf, &osize, size);
	if (now.tv_sec - clock >= tl)
	{
		put_buf(fd, obuf, &osize);
		clock = now.tv_sec;
	}
}
