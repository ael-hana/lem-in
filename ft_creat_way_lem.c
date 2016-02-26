/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_way_lem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 18:57:15 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/26 02:58:39 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lemin.h"

t_lem_in		*ft_init_t_lem_in(char *name, void *next, short std, int hans)
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

int				ft_pass_diz(char **tab, int i)
{
	while (*tab[i] == '#')
		++i;
	return (i);
}

t_lem_in		*ft_creat_map_lem(char **tab, char **name)
{
	int			i;
	t_lem_in	*ptr;
	int			osef;
	int			nb_handes;

	ft_check_d(name);
	ptr = NULL;
	osef = 0;
	i = ft_pass_diz(tab, 0);
	nb_handes = ft_return_digit(tab[i++]);
	while (tab[i] && name[osef])
	{
		while (tab[i][0] == '#' && ft_strcmp(tab[i], "##start") &&
				ft_strcmp(tab[i], "##end"))
			++i;
		if (!ft_strcmp(tab[i], "##start") && (i = ft_pass_diz(tab, i)))
			ptr = ft_init_t_lem_in(name[osef], ptr, 1, nb_handes);
		else if (!ft_strcmp(tab[i], "##end") && (i = ft_pass_diz(tab, i)))
			ptr = ft_init_t_lem_in(name[osef], ptr, 2, 0);
		else
			ptr = ft_init_t_lem_in(name[osef], ptr, 0, 0);
		++osef;
		++i;
	}
	return (ptr);
}

t_lem_in		*find_list(t_lem_in *ptr, char *name)
{
	if (ptr->name[ft_strlen(ptr->name) - 1] == 13)
		ptr->name[ft_strlen(ptr->name) - 1] = '\0';
	if (name[ft_strlen(name) - 1] == 13)
		name[ft_strlen(name) - 1] = '\0';
	while (ptr && ft_strcmp(ptr->name, name))
		ptr = ptr->next;
	if (!ptr)
		return (NULL);
	return (ptr);
}

void			ft_creat_way_lem_in(t_lem_in *ptr, char **tab, int i)
{
	char		**tmp;
	t_lem_in	*lst1;
	t_lem_in	*lst2;

	while (tab[i] && (ft_strchr(tab[i], '-') ||
				(tab[i][0] == '#')))
	{
		if (tab[i][0] == '#')
			++i;
		else
		{
			tmp = ft_strsplit(tab[i], '-');
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
