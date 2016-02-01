/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:38:31 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/01 19:43:17 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

char	**ft_read_stdin(void)
{
	char	*str;
	char	*new;
	char	*tmp;
	int		i;
	int		len;

	i = 1;
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
		ft_printf("My ptr : %p name : %s, nombre de fourmis %d, starttoend %d, n_way %d, way %p, nw : %d\n,",
				ptr, ptr->name,		ptr->n_hans,	ptr->starttoend, ptr->n_way, ptr->way[0], ptr->nw);
		ptr = ptr->next;
	}
}

void		ft_backtrack(t_lem_in *ptr)
{
	int			i;
	t_lem_in	*tmp;

	i = 0;

	while (ptr->n_way > i)
	{
		tmp = ptr->way[i++];
		if (tmp->nw >= ptr->nw || (!tmp->nw && tmp->starttoend != 1))
		{
			tmp->nw = ptr->nw + 1;
			if (tmp->starttoend != 2)
				ft_backtrack(tmp);
		}
	}
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
	ft_print_list_lem(save);
	return (0);
}
