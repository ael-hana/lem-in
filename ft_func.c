/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/25 15:49:02 by ael-hana          #+#    #+#             */
/*   Updated: 2016/03/07 23:29:56 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lemin.h"

void			ft_ch_str(char **tab, char *str)
{
	int			i;
	int			len;

	i = 0;
	len = 0;
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], str))
			++len;
		++i;
	}
	if (len != 1)
		ft_error_lem_in();
}

void			ft_realloc_tab(size_t size, t_lem_in *lst, void *add)
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

void			ft_overwrite_tab_ret(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		if (tab[i][ft_strlen(tab[i]) - 1] == 13)
			tab[i][ft_strlen(tab[i]) - 1] = '\0';
}

void			ft_len_nl(char *tab)
{
	static int	ok = 1;

	if (ft_strchr(tab, '\n'))
		++ok;
	else
		ok = 0;
	if (ok == 2)
		ft_error_lem_in();
}

int				ft_len_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		++i;
	return (i);
}
