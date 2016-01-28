/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem-in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 00:45:43 by ael-hana          #+#    #+#             */
/*   Updated: 2016/01/28 06:26:35 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

typedef struct		s_lem_in
{
	char			*name;
	int				n_hans;
	short			starttoend;
	int				n_way;
	struct s_lem_in	**way;
	struct s_lem_in	*next;
}					t_lem_in;
void				*check_buf(char **tab);
char				*ft_check_line(char *str);
void				ft_error_lem_in(void);
