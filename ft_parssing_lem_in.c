/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parssing_lem_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:38:47 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/04 08:39:47 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

void	ft_error_lem_in(void)
{
	ft_printf("ERROR");
	exit(EXIT_FAILURE);
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
	while (tab[1][i] && ft_isdigit(tab[1][i++]));
	if (tab[1][i])
		ft_error_lem_in();
	i = 0;
	while (tab[2][i] && ft_isdigit(tab[2][i++]));
	if (tab[2][i])
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
	i = 1;
	start = 0;
	end = 0;
	while (tab[i])
	{
		if (!ft_strcmp("##start", tab[i]))
			++start;
		else if (!ft_strcmp("##end", tab[i]))
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
	while (str[i] && ft_isdigit(str[i++]));
	if (str[i])
		ft_error_lem_in();
	if ((i = ft_atoi(str)))
		return (i);
	ft_error_lem_in();
	return (0);
}
