/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/02 18:55:48 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/04 17:04:04 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <sys/ioctl.h>

int		init_term(struct termios *termios)
{
	termios->c_lflag &= ~(ECHO | ECHONL | ICANON | ICRNL | ISIG);
	if (ioctl(0, TIOCSETA, termios) == -1)
		return (-1);
	return (0);
}

int		restaure_term(struct termios *termios)
{
	termios->c_lflag |= (ECHO | ECHONL | ICANON | ISIG | ICRNL);
	if (ioctl(0, TIOCSETA, termios) == -1)
		return (-1);
	return (0);
}
