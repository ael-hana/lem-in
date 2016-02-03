/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:38:31 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/03 23:52:31 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

char	**ft_read_stdin(void)
{
	char	*str;
	char	*new;
	char	*tmp;
	int		len;

	new = ft_strdup("\0");
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

void		ft_select_branch(t_lem_in *ptr, t_lem_in **tab)
{
	
}

void		ft_path_finding(t_lem_in *ptr)
{
	int		i;
	void	*tmp;
	t_lem_in	*tab_sort[ptr->n_way];

	i = 0;
	while (ptr->n_way > i)
	{
		tab_sort[i] = ptr->way[i];
		++i;
	}
	i = 0;
	while (ptr->n_way > (i + 1))
	{
		if (tab_sort[i] > tab_sort[i + 1])
		{
			tmp = tab_sort[i];
			tab_sort[i] = tab_sort[i + 1];
			tab_sort[i + 1] = tmp;
			i = 0;
		}
		else
			++i;
	}
}

int		main(void)
{
	char		**tab;
	t_lem_in	*ptr;
	char		*str;
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
	return (0);
}
