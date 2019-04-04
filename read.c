/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:15:45 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/27 17:29:17 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char	*file_error(char *filename, int fd)
{
	ft_dprintf(2, "ft_ssl: %s: %s: %s\n", g_cmd, filename, strerror(errno));
	close(fd);
	return (NULL);
}

static int	malloc_error(char *to_free)
{
	to_free ? free(to_free) : 0;
	ft_dprintf(2, "Memory allocation failure\n");
	return (EXIT_FAILURE);
}

char		*read_input(char *filename)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE];
	char	*file[2];

	if ((fd = filename ? open(filename, O_RDONLY) : STDIN_FILENO) == -1)
	{
		ft_dprintf(2, "ft_ssl: %s: %s: %s\n", g_cmd, filename, strerror(errno));
		return (NULL);
	}
	if ((file[0] = ft_strnew(0)) == NULL)
		exit(malloc_error(NULL));
	g_input_len = 0;
	while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		file[1] = file[0];
		if ((file[0] = join(file[1], buf, g_input_len, ret)) == NULL)
			exit(malloc_error(g_input_len ? file[1] : NULL));
		g_input_len += ret;
		free(file[1]);
	}
	if (ret == -1)
		return (file_error(filename, fd));
	close(fd);
	return (file[0]);
}
