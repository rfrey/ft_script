/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btinitnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 19:27:02 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/15 16:53:08 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "btree.h"

t_node			*ft_btinitnode(void *data)
{
	t_node		*new_node;

	if ((!(new_node = (t_node *)malloc(sizeof(t_node)))))
		return (NULL);
	new_node->data = data;
	new_node->right = NULL;
	new_node->left = NULL;
	ft_btsetheigth(new_node);
	return (new_node);
}
