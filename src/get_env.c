/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 15:30:39 by rfrey             #+#    #+#             */
/*   Updated: 2014/04/30 15:32:50 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*get_env(char **envp, char *get)
{
	int			i;
	int			len;

	len = ft_strlen(get);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(get, envp[i], len) && envp[i][len] == '=')
			return (&(envp[i][len + 1]));
		i++;
	}
	return (NULL);
}
