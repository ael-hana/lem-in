/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:38:31 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/28 06:26:32 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem-in.h"

char	**ft_read_stdin(void)
{
	char	*str;
	char	*new;
	char	*tmp;
	int		i;
	char	len;

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

t_lem_in	*ft_init_t_lem_in(char *name, void *next, short std, int hans)
{
	t_lem_in	*ptr;

	if (!(ptr = malloc(sizeof(t_lem_in))))
		ft_error_lem_in();
	ptr->name = name;
	ptr->next = next;
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
	int			len;
	int			nb_handes;

	i = 1;
	ptr = NULL;
	osef = 0;
	nb_handes = ft_return_digit(tab[0]);
	while (tab[i] && name[osef])
	{
		if (!ft_strcmp("##start", tab[i]))
		{
			++i;
			ft_printf("start %s\n", name[osef]);
			ptr = ft_init_t_lem_in(name[osef], ptr , 1, nb_handes);
		}
		else if (!ft_strcmp("##end", tab[i]))
		{
			++i;
			ft_printf("end %s\n", name[osef]);
			ptr = ft_init_t_lem_in(name[osef], ptr , 2, 0);
		}
		else
		{
			ft_printf("osef %s\n", name[osef]);
			ptr = ft_init_t_lem_in(name[osef], ptr , 0, 0);
		}
		++osef;
		++i;
	}
	return (ptr);
}

void		ft_print_list_lem(t_lem_in *ptr)
{
	while (ptr)
	{
		ft_printf("name : %s, nombre de fourmis %d, starttoend %d, n_way %d, way %s\n",
				ptr->name,		ptr->n_hans,	ptr->starttoend, ptr->n_way, ptr->way);
		ptr = ptr->next;
	}
}

int		main(void)
{
	char	**tab;
	void	*ptr;
	int		i;

	i = 1;
	tab = ft_read_stdin();
	ptr = ft_creat_map_lem(tab, ft_strsplit(check_buf(tab), '|'));
	while (*tab)
		ft_printf("line %d : %s\n", i++, *tab++);
	ft_print_list_lem(ptr);
	return (0);
}
