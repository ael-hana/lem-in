/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:38:31 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/10 10:09:51 by ael-hana         ###   ########.fr       */
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
	int			len;

	if (!(new = ft_strdup("\0")))
		ft_error_lem_in();
	if (!(str = malloc(sizeof(char) * 11)))
		ft_error_lem_in();
	while ((len = read(0, str, 10)) != -1)
	{
		if (!len)
			return (ft_strsplit(new, '\n'));
		str[len] = '\0';
		tmp = new;
		new = ft_strjoin(new, str);
		free(tmp);
	}
	ft_error_lem_in();
	return (NULL);
}

int				main(void)
{
	char		**tab;
	t_lem_in	*ptr;
	void		*save;
	char		**tmp;
	int			i;

	tab = ft_read_stdin();
	ptr = ft_creat_map_lem(tab, ft_strsplit(check_buf(tab), '|'));
	tmp = tab;
	tab = tmp;
	i = 0;
	while (!ft_strchr(tab[i], '-'))
		i++;
	ft_creat_way_lem_in(ptr, tab, i);
	save = ptr;
	while (ptr->starttoend != 1)
		ptr = ptr->next;
	ft_backtrack(ptr);
	ft_len_way(ptr);
	ft_path_finding(ptr, save);
	return (0);
}