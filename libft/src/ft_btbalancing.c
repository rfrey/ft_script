/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btbalancing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 15:10:39 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/15 18:24:08 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		ft_btbalancing(t_node **node)
{
	int		h_right;
	int		h_left;

	ft_btsetheigth(*node);
	h_left = ft_btgeth((*node)->left);
	h_right = ft_btgeth((*node)->right);
	if (h_left - h_right == 2)
	{
		if (ft_btgeth((*node)->left->left) < ft_btgeth((*node)->left->right))
			ft_btleftbalancing(&((*node)->left));
		ft_btrightbalancing(node);
	}
	else if (h_left - h_right == -2)
	{
		if (ft_btgeth((*node)->right->right) < ft_btgeth((*node)->right->left))
			ft_btrightbalancing(&((*node)->right));
		ft_btleftbalancing(node);
	}
}

int			ft_btgeth(t_node *tree)
{
	if (!tree)
		return (-1);
	else
		return (tree->heigth);
}

void		ft_btrightbalancing(t_node **root)
{
	t_node	*pivot;

	pivot = (*root)->left;
	(*root)->left = pivot->right;
	pivot->right = *root;
	*root = pivot;
	ft_btsetheigth(pivot->right);
	ft_btsetheigth(pivot);
}

void		ft_btleftbalancing(t_node **root)
{
	t_node	*pivot;

	pivot = (*root)->right;
	(*root)->right = pivot->left;
	pivot->left = *root;
	*root = pivot;
	ft_btsetheigth(pivot->left);
	ft_btsetheigth(pivot);
}

void		ft_btsetheigth(t_node *tree)
{
	int		h_left;
	int		h_right;

	h_left = ft_btgeth(tree->left);
	h_right = ft_btgeth(tree->right);
	tree->heigth = 1 + ((h_left > h_right) ? h_left : h_right);
}
