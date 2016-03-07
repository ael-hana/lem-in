/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:38:31 by ael-hana          #+#    #+#             */
/*   Updated: 2016/03/07 23:33:38 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lemin.h"

void			*ft_init_tab_end(t_lem_in *ptr, t_lem_in *start)
{
	int			oklm;

	while (start->starttoend != 2)
		start = start->next;
	if (!(start->old_val = (int *)malloc(sizeof(int) * (ptr->n_way + 1))))
		ft_error_lem_in();
	oklm = 0;
	while (ptr->n_way > oklm)
		start->old_val[oklm++] = 0;
	start->old_val[ptr->n_way] = -42;
	return (start);
}

char			ft_swap(t_lem_in **tab_sort, int i)
{
	void		*tmp;

	tmp = tab_sort[i];
	tab_sort[i] = tab_sort[i + 1];
	tab_sort[i + 1] = tmp;
	return (0);
}

char			**ft_read_stdin(void)
{
	char		*str;
	char		*new;
	char		*tmp;
	static int	s = 0;
	int			len;

	new = ft_strdup("\0");
	str = ft_memalloc(2);
	!str || !new ? ft_error_lem_in() : 0;
	while ((len = read(0, str, 1)) != -1 && ++s < 10000)
	{
		if (!len)
		{
			!*new ? ft_error_lem_in() : 0;
			return (ft_strsplit(new, '\n'));
		}
		str[len] = '\0';
		ft_len_nl(str);
		tmp = new;
		new = ft_strjoin(new, str);
		free(tmp);
	}
	ft_error_lem_in();
	return (NULL);
}

void			ft_color(int ac, char **tab)
{
	static int	ok = 0;

	if (ac > 1 && !ok)
	{
		if (ft_strstr(tab[1], "v"))
			ok = ft_printf("\033[35m");
		else if (ft_strstr(tab[1], "b"))
			ok = ft_printf("\033[34m");
		else if (ft_strstr(tab[1], "y"))
			ok = ft_printf("\033[33m");
		else if (ft_strstr(tab[1], "g"))
			ok = ft_printf("\033[32m");
		else if (ft_strstr(tab[1], "s"))
			ok = ft_printf("\033[42m");
	}
	else if (ac > 1 && ok)
		ft_printf("\033[0m");
}

int				main(int ac, char **av)
{
	char		**tab;
	t_lem_in	*ptr;
	void		*save;
	int			i;

	ft_color(ac, av);
	if (!(tab = ft_read_stdin()))
		ft_error_lem_in();
	ft_overwrite_tab_ret(tab);
	if (!(ptr = ft_creat_map_lem(tab, ft_strsplit(check_buf(tab), '|'))))
		ft_error_lem_in();
	i = 0;
	while (tab[i] && !ft_strchr(tab[i], '-'))
		i++;
	!tab[i] ? ft_error_lem_in() : 0;
	ft_creat_way_lem_in(ptr, tab, i);
	save = ptr;
	while (ptr->starttoend != 1 && ptr)
		ptr = ptr->next;
	ft_backtrack(ptr) ? ft_error_lem_in() : 0;
	ft_len_way(ptr);
	ft_print_tab(tab);
	ft_path_finding(ptr, save, 0);
	ft_color(ac, av);
	return (0);
}
