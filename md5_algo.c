/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetras <fpetras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:20:52 by fpetras           #+#    #+#             */
/*   Updated: 2019/03/15 15:35:37 by fpetras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t g_s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

uint32_t g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

static uint32_t	leftrotate(uint32_t x, uint32_t c)
{
	return ((x << c) | (x >> (32 - c)));
}

static void	operations(uint32_t b, uint32_t c, uint32_t d, int round,
						uint32_t *f, uint32_t *g)
{
	if (round < 16)
	{
		(*f) = (b & c) | ((~b) & d);
		(*g) = round;
	}
	else if (round < 32)
	{
		(*f) = (d & b) | ((~d) & c);
		(*g) = (5 * round + 1) % 16;
	}
	else if (round < 48)
	{
		(*f) = b ^ c ^ d;
		(*g) = (3 * round + 5) % 16;          
	}
	else
	{
		(*f) = c ^ (b | (~d));
		(*g) = (7 * round) % 16;
	}
}

static uint8_t		*padding(uint8_t *input, size_t len, size_t *msg_len)
{
	uint8_t		*message;
	uint32_t	bits;

	message = NULL;
	bits = 8 * len;
	while ((*msg_len) % 512 != 448)
		(*msg_len)++;
	(*msg_len) /= 8;
	message = ft_calloc((*msg_len) + 64, 1);
	ft_memcpy(message, input, len);
	message[len] = 128;
	ft_memcpy(message + (*msg_len), &bits, sizeof(uint32_t));
	return (message);
}

#define A 0
#define B 1
#define C 2
#define D 3
#define F 4
#define G 5
#define E 6

static void			process(uint8_t *message, uint32_t vars[7], size_t i)
{
	size_t		round;
	uint32_t	*m;

	round = 0;
	m = (uint32_t*)(message + i);
	vars[A] = g_hash[0];
	vars[B] = g_hash[1];
	vars[C] = g_hash[2];
	vars[D] = g_hash[3];
	round = 0;
	while (round < 64)
	{
		operations(vars[B], vars[C], vars[D], round, &vars[F], &vars[G]);
		vars[E] = vars[D];
		vars[D] = vars[C];
		vars[C] = vars[B];
		vars[B] += leftrotate((vars[F] + vars[A] + g_k[round] + m[vars[G]]),
		 g_s[round]);
		vars[A] = vars[E];
		round++;
	}
	g_hash[0] += vars[A];
	g_hash[1] += vars[B];
	g_hash[2] += vars[C];
	g_hash[3] += vars[D];
}

void				md5_algo(uint8_t *input, size_t len)
{
	uint8_t		*message;
	size_t		msg_len;
	uint32_t	vars[7];
	size_t		i;

	msg_len = len * 8 + 1;
	message = padding(input, len, &msg_len);
	g_hash[0] = 0x67452301;
	g_hash[1] = 0xefcdab89;
	g_hash[2] = 0x98badcfe;
	g_hash[3] = 0x10325476;
	i = 0;
	while (i < msg_len)
	{
		process(message, vars, i);
		i += 64;
	}
	free(message);
}