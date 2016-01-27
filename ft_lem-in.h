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
	struct s_lem-in	**way;
	struct s_lem-in	*next;
}					t_lem_in;
