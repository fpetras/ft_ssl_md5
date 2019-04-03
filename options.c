/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:51:45 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/03 13:58:10 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		parse_options(int ac, char **av)
{
	if (g_is_hash)
		return (parse_hash_options(ac, av));
	return (EXIT_FAILURE);
}

int		illegal_option(char opt, char **av)
{
	ft_dprintf(2, "%s: %s: illegal option -- %c\n", av[0], av[1], opt);
	if (g_is_hash)
		return (print_hash_usage(av));
	return (EXIT_FAILURE);
}

int		argument_missing(char opt, char **av)
{
	ft_dprintf(2, "%s: %s: option requires an argument -- %c\n",
	av[0], av[1], opt);
	if (g_is_hash)
		return (print_hash_usage(av));
	return (EXIT_FAILURE);
}
