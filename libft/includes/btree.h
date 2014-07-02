/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrey <rfrey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 18:22:15 by rfrey             #+#    #+#             */
/*   Updated: 2014/04/20 20:32:06 by rfrey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

typedef struct	s_node
{
	void			*data;
	struct s_node	*right;
	struct s_node	*left;
	int				heigth;
}				t_node;

typedef int(*t_cmpfunc)(void*, void*);
typedef void(*t_freefunc)(void*);

void			ft_btaddnode(t_node **btree, void *data, t_cmpfunc cmpfunc);
t_node			*ft_btinitnode(void *data);
void			ft_btclear(t_node **tree, t_freefunc freefunc);
void			ft_btsetheigth(t_node *tree);
void			ft_btbalancing(t_node **tree);
void			ft_btrightbalancing(t_node **root);
void			ft_btleftbalancing(t_node **root);
int				ft_btgeth(t_node *tree);
void			ft_btwidthbrowse(t_node *tree);

#endif
