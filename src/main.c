/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/29 16:45:53 by rfrey             #+#    #+#             */
/*   Updated: 2014/05/04 18:54:29 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "script.h"
#include "libft.h"

static int		get_options(t_script *data, int argc, char **argv, int *i)
{
	int		j;

	j = 1;
	while (argv[*i][j])
	{
		if (argv[*i][j] == 'a')
			data->opt_a = 1;
		else if (argv[*i][j] == 'q')
			data->opt_q = 1;
		else if (argv[*i][j] == 't' && !argv[*i][j + 1])
		{
			++(*i);
			if (*i < argc)
			{
				if ((data->time = ft_atoi(argv[*i])) < 0)
					return (-1);
				return (0);
			}
			else
				return (-1);
		}
		++j;
	}
	return (0);
}

static int		set_options(t_script *data, int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (get_options(data, argc, argv, &i) == -1)
				return (-1);
		}
		else if (!data->file)
			data->file = argv[i];
		else
		{
			data->cmd = argv[i];
			break ;
		}
		++i;
	}
	return (0);
}

static int		init_data(t_script *data, int argc, char **argv, char **envp)
{
	data->envp = envp;
	data->ptyslv = -1;
	data->ptymst = -1;
	data->opt_a = 0;
	data->opt_q = 0;
	data->time = 30;
	data->cmd = NULL;
	data->file = NULL;
	data->shell = get_env(envp, "SHELL");
	if (set_options(data, argc, argv) == -1)
	{
		ft_putendl("usage : ./ft_script [-aq] [-t time] [file [cmd ...]]");
		return (-1);
	}
	if (!data->file)
		data->file = "typescript";
	return (0);
}

int				main(int argc, char **argv, char **envp)
{
	t_script		data;
	struct termios	termos;

	if (ioctl(0, TIOCGETA, &termos) == -1)
		return (1);
	init_term(&termos);
	if (init_data(&data, argc, argv, envp) == -1)
		return (1);
	getpty(&(data.ptyslv), &(data.ptymst));
	if (!data.shell || data.ptymst == -1 || data.ptyslv == -1)
		return (1);
	ioctl(0, TIOCGWINSZ, &data.ws);
	ioctl(data.ptymst, TIOCSWINSZ, &data.ws);
	script(data);
	restaure_term(&termos);
	return (0);
}
