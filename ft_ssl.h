/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:00:22 by fpetras           #+#    #+#             */
/*   Updated: 2019/04/03 13:55:08 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <limits.h>

# define WHITE "\033[37;1m"
# define TEXT_RESET "\033[0;0m"

# define HASH_OPT_STR "pqrs"

enum	e_opts
{
	OPT_P,
	OPT_Q,
	OPT_R,
	OPT_S,
	OPT_NUM
};

enum	e_vars
{
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	I,
	TMP = 4
};

char		*g_cmd;
int			g_opts[OPT_NUM];
int			g_is_hash;
int			g_md;
int			g_sha;
size_t		g_input_len;
uint32_t	g_hash[8];
uint64_t	g_hash64[8];

int			print_usage(char **av);
int			command_is_hash(char **av);
int			parse_options(int ac, char **av);
int			parse_hash_options(int ac, char **av);
int			illegal_option(char opt, char **av);
int			argument_missing(char opt, char **av);
int			print_hash_usage(char **av);
int			hash(int ac, char **av);
char		*read_stdin(void);
char		*read_file(char *filename);
char		*join(char const *s1, char const *s2, size_t len1, size_t len2);
void		print(char *input);
void		md5(char *input);
void		md5_algo(char *input);
void		sha224_256(char *input);
void		sha224_256_algo(char *input);
void		sha384_512(char *input);
void		sha384_512_algo(char *input);
void		init_values(uint32_t *vars);
void		init_values64(uint64_t *vars);
void		add_values(uint32_t *vars);
void		add_values64(uint64_t *vars);
uint32_t	leftrotate(uint32_t x, uint32_t n);
uint32_t	rightrotate(uint32_t x, uint32_t n);
uint64_t	rightrotate64(uint64_t x, uint64_t n);
uint32_t	change_endianness(uint32_t value);
uint64_t	change_endianness64(uint64_t value);

#endif
