/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_way_lem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 18:57:15 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/04 07:23:19 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

t_lem_in	*ft_init_t_lem_in(char *name, void *next, short std, int hans)
{
	t_lem_in	*ptr;

	if (!(ptr = malloc(sizeof(t_lem_in))))
		ft_error_lem_in();
	ptr->name = name;
	ptr->next = next;
	ptr->nw = 0;
	ptr->vld = 0;
	ptr->n_hans = hans;
	ptr->starttoend = std;
	ptr->n_way = 0;
	ptr->way = NULL;
	return (ptr);
	}

t_lem_in		*ft_creat_map_lem(char **tab, char **name)
{
	int			i;
	t_lem_in	*ptr;
	int			osef;
	int			nb_handes;

	i = 0;
	ptr = NULL;
	osef = 0;
	while (tab[i][0] == '#' && tab[i][1] != '#')
		++i;
	nb_handes = ft_return_digit(tab[i++]);
	while (tab[i] && name[osef])
	{
		while (tab[i][0] == '#' && tab[i][1] != '#')
			++i;
		if (!ft_strcmp("##start", tab[i]))
		{
			++i;
			ptr = ft_init_t_lem_in(name[osef], ptr , 1, nb_handes);
		}
		else if (!ft_strcmp("##end", tab[i]))
		{
			++i;
			ptr = ft_init_t_lem_in(name[osef], ptr , 2, 0);
		}
		else
			ptr = ft_init_t_lem_in(name[osef], ptr , 0, 0);
		++osef;
		++i;
	}
	return (ptr);
}

t_lem_in	*find_list(t_lem_in *ptr, char *name)
{
	while (ptr && ft_strcmp(ptr->name, name))
		ptr = ptr->next;
	return (ptr);
}

void		ft_realloc_tab(size_t size, t_lem_in *lst, void *add)
{
	t_lem_in		**tmp;
	t_lem_in		**old;
	unsigned int	i;

	old = lst->way;
	if (!(tmp = malloc(sizeof(t_lem_in) * (size + 1))))
		ft_error_lem_in();
	i = 0;
	while (i < (size - 1))
	{
		tmp[i] = old[i];
		if (tmp[i++] == add)
			return ;
	}
	tmp[i] = add;
	tmp[++i] = NULL;
	if (old)
		free(old);
	lst->way = tmp;
	lst->n_way = size;
}

void		ft_creat_way_lem_in(t_lem_in *ptr, char **tab, int i)
{
	char	**tmp;
	t_lem_in	*lst1;
	t_lem_in	*lst2;

	while (tab[i] && (ft_strchr(tab[i], '-') || (tab[i][0] == '#' && tab[i][1] != '#')))
	{
		if (tab[i][0] == '#' && tab[i][1] != '#')
			++i;
		else
		{
			tmp = ft_strsplit(tab[i], '-');
			ft_putstr(tab[i]);
			ft_putstr("\noklm1\n\n");
			ft_putstr(tmp[0]);
			ft_putstr("\noklm2\n\n");
			if (!(lst1 = find_list(ptr, tmp[0])))
				return ;
			if (!(lst2 = find_list(ptr, tmp[1])))
				return ;
			ft_realloc_tab(lst1->n_way + 1, lst1, lst2);
			ft_realloc_tab(lst2->n_way + 1, lst2, lst1);
			++i;
		}
	}
}
