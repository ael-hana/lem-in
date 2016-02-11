/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_finding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 22:58:47 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/11 05:10:53 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lemin.h"

char	ft_backtrack(t_lem_in *ptr)
{
	int			i;
	char		ok;
	t_lem_in	*tmp;

	i = 0;
	ok = 1;
	while (ptr->n_way > i)
	{
		tmp = ptr->way[i++];
		if (tmp->starttoend == 2)
			return (0);
		if (tmp->nw > ptr->nw + 1 || (tmp->nw == 0 && tmp->starttoend != 1))
		{
			tmp->nw = ptr->nw + 1;
			if (tmp->starttoend != 2)
				ok = ft_backtrack(tmp);
		}
		else if (ok && ptr->n_way == i)
			ptr->nw = 0;
	}
	i = 0;
	while (ptr->starttoend == 1 && !ptr->way[i]->nw)
		++i;
	if (!ptr->way[i]->nw)
		ft_error_lem_in();
	return (ok);
}

int		ft_size_to_end(t_lem_in *ptr)
{
	t_lem_in	*tmp;
	int			i;

	i = 0;
	if (ptr->starttoend == 2)
		return (1);
	while (42)
	{
		tmp = ptr->way[i++];
		if (tmp->starttoend == 1)
			tmp->starttoend = 1;
		else if (tmp->starttoend == 2)
			return (1);
		else if (tmp->nw - 1 == ptr->nw)
			return (ft_size_to_end(tmp) + 1);
	}
}

void	ft_len_way(t_lem_in *ptr)
{
	int			i;
	t_lem_in	*tmp;

	i = 0;
	while (ptr->n_way > i)
	{
		tmp = ptr->way[i++];
		tmp->vld = ft_size_to_end(tmp);
	}
}
