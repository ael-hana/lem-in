#include "ft_lem-in.h"

void	ft_error_lem_in(void)
{
	ft_printf("ERROR");
	exit(EXIT_FAILURE);
}

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
}

void		check_diz(char **tab)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = 0;
	while (tab[i])
	{
		if (!ft_strcmp("##start", tab[i]))
			++start;
		if (!ft_strcmp("##end", tab[i]))
			++end;
		i++;
	}
	if (!(end == 1 && start == 1))
		ft_error_lem_in();
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
}

t_lem_in	*ft_creat_map_lem(char **tab)
{
	int	i;
	int	nb_handes;

	i = 1;
	nb_handes = ft_return_digit(tab[0]);
	check_diz(tab);
	while (tab[i++])
		tab[i++];
	return (NULL);
}

int		main(void)
{
	char	**tab;
	int		i;

	i = 1;
	tab = ft_read_stdin();
	while (*tab)
		ft_printf("line %d : %s\n", i++, *tab++);
	
	return (0);
}
