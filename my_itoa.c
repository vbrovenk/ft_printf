/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 17:05:28 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/06/27 17:05:32 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		fill(intmax_t number, char *str, int len)
{
	if (number == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (number > 0)
	{
		str[len] = number % 10 + '0';
		number /= 10;
		len--;
	}
}

char			*my_itoa(intmax_t number)
{
	char	*res;
	int		sign;
	int		len;

	sign = 0;
	if (number == -9223372036854775808)
		return (ft_strdup("-9223372036854775808"));
	if (number < 0)
	{
		number *= -1;
		sign = 1;
	}
	len = my_countdigits(number);
	res = (char*)malloc(sizeof(char) * (len + sign + 1));
	if (!res)
		return (0);
	if (sign == 1)
	{
		res[0] = '-';
		len++;
	}
	fill(number, res, len);
	return (res);
}
