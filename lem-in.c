/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:38:31 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/30 03:21:47 by ael-hana         ###   ########.fr       */
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

void		ft_print_list_lem(t_lem_in *ptr)
{
	while (ptr)
	{
		ft_printf("My ptr : %p name : %s, nombre de fourmis %d, starttoend %d, n_way %d, way %p\n",
				ptr, ptr->name,		ptr->n_hans,	ptr->starttoend, ptr->n_way, ptr->way[0]);
		ptr = ptr->next;
	}
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

int		main(void)
{
	char	**tab;
	void	*ptr;
	char	**tmp;
	int		i;

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
	ft_print_list_lem(ptr);
	return (0);
}
