/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:39:06 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/03 13:52:51 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	set_option(char opt)
{
	g_opts[OPT_P] = (opt == 'p') ? 1 : g_opts[OPT_P];
	g_opts[OPT_Q] = (opt == 'q') ? 1 : g_opts[OPT_Q];
	g_opts[OPT_R] = (opt == 'r') ? 1 : g_opts[OPT_R];
	g_opts[OPT_S] = (opt == 's') ? 1 : g_opts[OPT_S];
}

static int	parse_hash_options_2(char **av, int i, int j)
{
	if (!ft_strcmp("--", av[i]))
		return (i + 1);
	else if (ft_strchr(HASH_OPT_STR, av[i][j]))
		set_option(av[i][j]);
	else
		return (illegal_option(av[i][j], av));
	if (av[i][j] == 's' && !av[i][j + 1] && av[i + 1])
		return (i + 1);
	else if (av[i][j] == 's' && av[i][j + 1])
	{
		av[i] = &av[i][j + 1];
		return (i);
	}
	else if (av[i][j] == 's')
		return (argument_missing(av[i][j], av));
	return (0);
}

int			parse_hash_options(int ac, char **av)
{
	int i;
	int j;
	int opt_end;

	i = 2;
	while (i < ac)
	{
		j = 1;
		while (av[i][j] && av[i][0] == '-')
		{
			if ((opt_end = parse_hash_options_2(av, i, j)) != 0)
				return (opt_end);
			j++;
		}
		if (av[i][0] != '-' || !ft_strcmp("-", av[i]))
			return (i);
		i++;
	}
	return (i);
}
