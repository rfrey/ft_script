/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btwidthbrowse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 16:43:22 by rfrey             #+#    #+#             */
/*   Updated: 2013/12/15 16:33:38 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdio.h>
#include "btree.h"
#include "libft.h"
#include "list.h"

void	ft_btwidthbrowse(t_node *tree)
{
	t_list	*list;
	t_node	*tmp;

	list = NULL;
	if (tree)
	{
		ft_listpushback(&list, tree);
		while (list)
		{
			tmp = (t_node *)ft_listpop(&list);
			printf("%p\n", tmp->data);
			if (tmp->left)
				ft_listpushback(&list, tmp->left);
			if (tmp->right)
				ft_listpushback(&list, tmp->right);
		}
	}
}
