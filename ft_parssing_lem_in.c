/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parssing_lem_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:38:47 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/12 11:49:17 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lemin.h"

void		ft_error_lem_in(void)
{
	ft_printf("ERROR");
	exit(EXIT_FAILURE);
}

void		ft_print_tab(char **tab)
{
	while (*tab)
		ft_putendl(*tab++);
	ft_putchar('\n');
}

char		*ft_check_line(char *str)
{
	char	**tab;
	int		i;
	int		len;

	len = 0;
	tab = ft_strsplit(str, ' ');
	while (tab[len])
		++len;
	if (len != 3)
		ft_error_lem_in();
	i = 0;
	while (tab[1][i] && ft_isdigit(tab[1][i]))
		++i;
	if (tab[1][i])
		ft_error_lem_in();
	i = 0;
	while (tab[2][i] && ft_isdigit(tab[2][i]))
		++i;
	if (tab[2][i] && tab[2][i] != 13)
		ft_error_lem_in();
	return (ft_strjoin(tab[0], "|"));
}

void		*check_buf(char **tab)
{
	int		i;
	int		start;
	int		end;
	char	*ret;

	ret = "\0";
	i = 0;
	if (!tab || !*tab || !**tab)
		ft_error_lem_in();
	while (tab[i][0] == '#')
		++i;
	++i;
	start = 0;
	end = 0;
	while (tab[i])
	{
		if (tab[i][ft_strlen(tab[i]) - 1] == 13)
			tab[i][ft_strlen(tab[i]) - 1] = '\0';
		if (!ft_strcmp(tab[i], "##start"))
			++start;
		else if (!ft_strcmp(tab[i], "##end"))
			++end;
		else if (tab[i][0] != '#' && !ft_strchr(tab[i], '-'))
			ret = ft_strjoin(ret, ft_check_line(tab[i]));
		i++;
	}
	if (!(end == 1 && start == 1))
		ft_error_lem_in();
	return (ret);
}

int			ft_return_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		++i;
	if (str[i] && str[i] != 13)
		ft_error_lem_in();
	if ((i = ft_atoi(str)))
		return (i);
	ft_error_lem_in();
	return (0);
}
