/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:10:30 by ael-hana          #+#    #+#             */
/*   Updated: 2016/02/12 05:15:11 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEMIN_H
# define FT_LEMIN_H
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf.h"
# include "libft.h"

typedef struct		s_lem_in
{
	char			*name;
	unsigned int	nw;
	int				n_hans;
	unsigned int	vld;
	short			starttoend;
	int				*old_val;
	int				n_way;
	struct s_lem_in	**way;
	struct s_lem_in	*next;
}					t_lem_in;
void				*check_buf(char **tab);
char				*ft_check_line(char *str);
void				ft_creat_way_lem_in(t_lem_in *ptr, char **tab, int i);
void				ft_error_lem_in(void);
t_lem_in			*ft_creat_map_lem(char **tab, char **name);
char				ft_backtrack(t_lem_in *ptr);
void				ft_len_way(t_lem_in *ptr);
int					ft_return_digit(char *str);
void				ft_path_finding(t_lem_in *ptr, t_lem_in *save, int i);
char				ft_swap(t_lem_in **tab_sort, int i);
void				*ft_init_tab_end(t_lem_in *ptr, t_lem_in *start);
void				ft_print_tab(char **tab);
#endif
