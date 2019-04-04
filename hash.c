/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:38:48 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/01 16:47:48 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	hash_formatted(char *filename, char *input)
{
	if (!g_opts[OPT_Q])
	{
		if (!g_opts[OPT_R])
		{
			if (filename)
				ft_printf("%s (%s) = ", ft_strupr(g_cmd), filename);
			else
				ft_printf("%s (\"%s\") = ", ft_strupr(g_cmd), input);
			ft_strlwr(g_cmd);
		}
	}
	(g_md == 5) ? md5(input) : 0;
	(g_sha == 224 || g_sha == 256) ? sha224_256(input) : 0;
	(g_sha == 384 || g_sha == 512 || g_sha == 512224 || g_sha == 512256) ?
	sha384_512(input) : 0;
	if (!g_opts[OPT_Q] && g_opts[OPT_R])
	{
		if (filename)
			ft_printf(" %s\n", filename);
		else
			ft_printf(" \"%s\"\n", input);
	}
	else
		ft_printf("\n");
}

static int	hash_file(char *filename)
{
	char *input;

	if ((input = read_input(filename)) != NULL)
	{
		hash_formatted(filename, input);
		free(input);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

static int	hash_stdin(void)
{
	char *input;

	if ((input = read_input(NULL)) == NULL)
		return (EXIT_FAILURE);
	g_opts[OPT_P] ? print_input(input) : 0;
	(g_md == 5) ? md5(input) : 0;
	(g_sha == 224 || g_sha == 256) ? sha224_256(input) : 0;
	(g_sha == 384 || g_sha == 512 || g_sha == 512224 || g_sha == 512256) ?
	sha384_512(input) : 0;
	ft_printf("\n");
	free(input);
	return (EXIT_SUCCESS);
}

int			hash(int ac, char **av)
{
	int	i;
	int ret;

	i = 0;
	ret = EXIT_SUCCESS;
	if (ac == 0 || g_opts[OPT_P])
		if (hash_stdin() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (g_opts[OPT_S])
	{
		g_input_len = ft_strlen(av[i]);
		hash_formatted(NULL, av[i]);
		i++;
	}
	while (i < ac)
	{
		if (hash_file(av[i]) == EXIT_FAILURE)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
