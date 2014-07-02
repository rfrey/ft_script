/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btclear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/09 23:52:09 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/15 18:21:38 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "btree.h"

void	ft_btclear(t_node **tree, t_freefunc freefunc)
{
	if (!tree)
		return ;
	if (!*tree)
		return ;
	ft_btclear(&((*tree)->left), freefunc);
	ft_btclear(&((*tree)->right), freefunc);
	if (freefunc)
		freefunc((*tree)->data);
	free(*tree);
	*tree = NULL;
}
