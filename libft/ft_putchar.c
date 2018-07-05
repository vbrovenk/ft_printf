/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 14:16:30 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/03/25 14:16:31 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		sizeof_symbol(int c)
{
	if (c < 128)
		return (1);
	else if (c < 2048)
		return (2);
	else if (c < 65536)
		return (3);
	else
		return (4);
}

int		ft_putchar(unsigned int c)
{
	unsigned char symbol[4];

	if (c < 128)
		symbol[0] = c;
	else if (c < 2048)
	{
		symbol[0] = (c >> 6 & 31) | 192;
		symbol[1] = (c & 63) | 128;
	}
	else if (c < 65536)
	{
		symbol[0] = ((c >> 12) & 15) | 224;
		symbol[1] = ((c >> 6) & 63) | 128;
		symbol[2] = (c & 63) | 128;
	}
	else
	{
		symbol[0] = (c >> 18 & 7) | 240;
		symbol[1] = (c >> 12 & 63) | 128;
		symbol[2] = (c >> 6 & 63) | 128;
		symbol[3] = (c & 63) | 128;
	}
	write(1, &symbol, sizeof_symbol(c));
	return (sizeof_symbol(c));
}
