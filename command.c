/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:08:56 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/01 16:47:33 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	strisdigit(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int			command_is_hash(char **av)
{
	if (!ft_strcasecmp("md5", av[1]))
		g_md = 5;
	else if (!ft_strncasecmp("sha", av[1], 3) && ft_strlen(av[1]) > 3 &&
		strisdigit(&av[1][3]))
	{
		g_sha = ft_atoi(&av[1][3]);
		if (g_sha != 224 && g_sha != 256 && g_sha != 384 && g_sha != 512 &&
			g_sha != 512224 && g_sha != 512256)
			return (0);
	}
	else
		return (0);
	return (1);
}
