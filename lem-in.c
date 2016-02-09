/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:38:31 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/09 05:47:37 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

char	**ft_read_stdin(void)
{
	char	*str;
	char	*new;
	char	*tmp;
	int		len;

	if (!(new = ft_strdup("\0")))
		ft_error_lem_in();
	if (!(str = malloc(sizeof(char) * 11)))
		ft_error_lem_in();
	while ((len = read(0, str, 10)) != -1)
	{
		if (!len)
			return (ft_strsplit(new, '\n'));
		str[len] = '\0';
		new = ft_strjoin((tmp = new), str);
		free(tmp);
	}
	ft_error();
	return (NULL);
}

void		ft_print_list_lem(t_lem_in *ptr)
{
	while (ptr)
	{
		ft_printf("My ptr : %p name : %s, nombre de fourmis %d, starttoend %d, n_way %d, way %p, nw : %d, vld : %d\n",
				ptr, ptr->name,		ptr->n_hans,	ptr->starttoend, ptr->n_way, ptr->way[0], ptr->nw, ptr->vld);
		ptr = ptr->next;
	}
}

void		ft_run_hans(t_lem_in *ptr, int num)
{
	int	i;
	int	old;

	i = 0;
	if (ptr->starttoend == 2)
	{
		while (ptr->old_val[i] && ptr->old_val[i] != -42)
			++i;
		if (num)
			ptr->old_val[i] = num;
		return;
	}
	old = ptr->n_hans;
	ptr->n_hans = num;
	while (ptr->n_way > i)
	{
		if (ptr->way[i]->nw == (ptr->nw + 1) || ptr->way[i]->starttoend == 2)
		{
			ft_run_hans(ptr->way[i], old);
			return;
		}
		++i;
	}
}

void		ft_print_pos(t_lem_in *ptr, int remove)
{
	int	i;

	i = 0;
	if (ptr->starttoend == 2)
	{
		while (ptr->old_val[i] != -42)
		{
			if (remove == ptr->old_val[i])
			{
				ft_printf("L%d-%s ", ptr->old_val[i], ptr->name);
				ptr->old_val[i] = 0;
			}
			if (ptr->old_val[i])
				ft_printf("L%d-%s ", ptr->old_val[i], ptr->name);
			if (remove != ptr->old_val[i])
				ptr->old_val[i] = 0;
			++i;
		}
		return ;
	}
	while (ptr->n_way > i)
	{
		if (ptr->way[i]->nw == (ptr->nw + 1) || ptr->way[i]->starttoend == 2)
		{
			ft_print_pos(ptr->way[i], remove);
			if (!ptr->starttoend && ptr->n_hans)
				ft_printf("L%d-%s ", ptr->n_hans, ptr->name);
		//	if (!ft_strcmp(ptr->name, "3"))
		//		ft_printf("name : %s, ptr : %p\n", ptr->way[i]->name, ptr->way[i]);
		}
		++i;
	}
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

void		ft_select_branch(t_lem_in *ptr, t_lem_in **tab, t_lem_in *list)
{
	int		i;
	void	*osef;
	int		oklm;

	oklm = 0;
	osef = list;
	while (list->starttoend != 2)
		list = list->next;
	if (!(list->old_val = (int *)malloc(sizeof(int) * (ptr->n_way + 1))))
		ft_error_lem_in();
	while (ptr->n_way > oklm)
		list->old_val[oklm++] = 0;
	list->old_val[ptr->n_way] = -42;
	oklm = 1;
	i = ptr->n_way - 1;
	ptr->way = tab;
	while (ft_search_val(list->old_val, ptr->n_hans, osef) || oklm == 1)
	{
		if ((tab[i]->vld <= (ptr->nw - oklm) || i == 0) && oklm <= ptr->n_hans)
			ft_run_hans(tab[i], oklm++);
		else
			ft_run_hans(tab[i], 0);
		if (--i < 0)
		{
			i = ptr->n_way - 1;
			ft_print_pos(ptr, ptr->n_hans);
			write(1, "\n", 1);
		}
	}
	ft_print_pos(ptr, ptr->n_hans);
	write(1, "\n", 1);
}

void		ft_path_finding(t_lem_in *ptr, t_lem_in *save)
{
	int		i;
	int		ix;
	void	*tmp;
	t_lem_in	*tab_sort[ptr->n_way + 1];

	i = 0;
	ix = 0;
	while (ptr->n_way > i)
	{
		if (ptr->way[i]->vld && !ptr->way[i]->starttoend)
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
		{
			tmp = tab_sort[i];
			tab_sort[i] = tab_sort[i + 1];
			tab_sort[i + 1] = tmp;
			i = 0;
		}
		else
			++i;
	}
	ft_select_branch(ptr, tab_sort, save);
}

int		main(void)
{
	char		**tab;
	t_lem_in	*ptr;
	void		*save;
	char		**tmp;
	int			i;

	i = 1;
	tab = ft_read_stdin();
	ptr = ft_creat_map_lem(tab, ft_strsplit(check_buf(tab), '|'));
	tmp = tab;
	while (*tab)
		ft_printf("line %d : %s\n", i++, *tab++);
	tab = tmp;
	i = 0;
	while (!ft_strchr(tab[i], '-'))
		i++;
	ft_creat_way_lem_in(ptr, tab, i);
	save = ptr;
	while (ptr->starttoend != 1)
		ptr = ptr->next;
	ft_backtrack(ptr);
	//ft_path_finding(save, NULL, 0);
	ft_len_way(ptr);
	ft_print_list_lem(save);
	ft_path_finding(ptr, save);
	dprintf(1, "lol");
	return (0);
}
