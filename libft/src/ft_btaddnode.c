/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btaddnode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 18:33:36 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/15 18:09:03 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "btree.h"

void		ft_btaddnode(t_node **btree, void *data, t_cmpfunc cmpfunc)
{
	if (!*btree)
		*btree = ft_btinitnode(data);
	else
	{
		if (cmpfunc(data, (*btree)->data) >= 0)
			ft_btaddnode(&((*btree)->right), data, cmpfunc);
		else
			ft_btaddnode(&((*btree)->left), data, cmpfunc);
		ft_btbalancing(btree);
	}
}
