/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_finding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 22:58:47 by ael-hana          #+#    #+#             */
/*   Updated: 2016/03/07 23:29:29 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lemin.h"

char	ft_backtrack(t_lem_in *ptr)
{
	int				i;
	static char		ok = 1;
	t_lem_in		*tmp;

	i = 0;
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
	while (ptr->starttoend == 1 && i < ptr->n_way && !ptr->way[i]->nw)
		++i;
	i == ptr->n_way && ptr->starttoend == 1 ? ft_error_lem_in() : 0;
	return (ok);
}

int		ft_size_to_end(t_lem_in *ptr)
{
	t_lem_in	*tmp;
	int			v;
	int			i;

	i = 0;
	v = 0;
	if (ptr->starttoend == 2)
		return (1);
	while (ptr->n_way > i)
	{
		tmp = ptr->way[i++];
		if (tmp->starttoend == 1)
			tmp->starttoend = 1;
		if (tmp->starttoend == 2)
			return (1);
		if (tmp->nw - 1 == ptr->nw)
		{
			if ((v = ft_size_to_end(tmp)) < 0)
				return (-1);
			return (v + 1);
		}
	}
	return (-1);
}

void	ft_len_way(t_lem_in *ptr)
{
	int			i;
	int			v;
	t_lem_in	*tmp;

	i = 0;
	while (ptr->n_way > i)
	{
		tmp = ptr->way[i++];
		if ((v = ft_size_to_end(tmp)) >= 0)
			tmp->vld = v;
		else
		{
			v = i;
			while (v - 1 < ptr->n_way)
			{
				ptr->way[v - 1] = ptr->way[v];
				v++;
			}
			--ptr->n_way;
		}
	}
}

void	ft_check_d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_ch_str(tab, tab[i++]);
}
