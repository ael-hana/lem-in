/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_hans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:24:46 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/11 04:13:52 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lemin.h"

int			ft_print_posi2(t_lem_in *ptr)
{
	void	*save;
	int		i;
	int		len;

	save = ptr;
	len = 0;
	while (ptr)
	{
		if (!ptr->starttoend && ptr->n_hans)
			len = ft_printf("L%d-%s ", ptr->n_hans, ptr->name);
		ptr = ptr->next;
	}
	i = 0;
	ptr = save;
	while (ptr->starttoend != 2)
		ptr = ptr->next;
	while (ptr->old_val[i] != -42)
	{
		if (ptr->old_val[i])
			len = ft_printf("L%d-%s ", ptr->old_val[i], ptr->name);
		ptr->old_val[i] = 0;
		++i;
	}
	return (len);
}

short		ft_search_val(int *tab, int s, t_lem_in *ptr)
{
	unsigned int	i;
	short			ok;

	i = 0;
	while (tab[i] != -42 && tab[i] != s)
		++i;
	ok = 0;
	while (ptr)
	{
		ok = !ptr->starttoend && ptr->n_hans ? 1 : ok;
		ptr = ptr->next;
	}
	return (tab[i] == -42 && ok ? 1 : 0);
}

void		ft_run_hans(t_lem_in *ptr, int num)
{
	int	i;
	int	old;

	i = 0;
	if (ptr->starttoend >= 2)
	{
		while (ptr->old_val[i] && ptr->old_val[i] != -42)
			++i;
		if (num)
			ptr->old_val[i] = num;
		return ;
	}
	old = ptr->n_hans;
	ptr->n_hans = num;
	while (ptr->n_way > i)
	{
		if (ptr->way[i]->nw == (ptr->nw + 1) || ptr->way[i]->starttoend == 2)
		{
			ft_run_hans(ptr->way[i], old);
			return ;
		}
		++i;
	}
}

void		ft_select_branch(t_lem_in *ptr, t_lem_in **tab, t_lem_in *list)
{
	int		i;
	void	*osef;
	int		oklm;

	osef = list;
	list = ft_init_tab_end(ptr, osef);
	oklm = 1;
	i = ptr->n_way - 1;
	ptr->way = tab;
	while (ft_search_val(list->old_val, ptr->n_hans, osef) || oklm <= ptr->n_hans)
	{
		if ((tab[i]->vld <= (ptr->nw - oklm) || i == 0) && oklm <= ptr->n_hans)
		{
			ft_run_hans(tab[i], oklm++);
		}
		else
			ft_run_hans(tab[i], 0);
		if (--i < 0)
		{
			i = ptr->n_way - 1;
			ft_print_posi2(osef);
			write(1, "\n", 1);
		}
	}
	ft_print_posi2(osef) ? write(1, "\n", 1) : 0;
}

void		ft_path_finding(t_lem_in *ptr, t_lem_in *save)
{
	int			i;
	int			ix;
	t_lem_in	*tab_sort[ptr->n_way + 1];

	i = 0;
	ix = 0;
	while (ptr->n_way > i)
	{
		if ((ptr->way[i]->vld && !ptr->way[i]->starttoend) ||
				ptr->way[i]->starttoend == 2)
			tab_sort[i - ix] = ptr->way[i];
		else
			++ix;
		++i;
	}
	ptr->n_way = i - ix;
	i = 0;
	while (ptr->n_way > (i + 1))
	{
		if ((tab_sort[i]->vld > tab_sort[i + 1]->vld) &&
				!(tab_sort[i + 1]->starttoend) && !(tab_sort[i]->starttoend))
			i = ft_swap(tab_sort, i);
		else
			++i;
	}
	ft_select_branch(ptr, tab_sort, save);
}
