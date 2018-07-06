/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 08:15:07 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/03/27 08:15:09 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char			*ft_itoa(intmax_t number)
{
	char	*res;
	int		sign;
	int		len;

	sign = 0;
	if (number < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	if (number < 0)
	{
		number *= -1;
		sign = 1;
	}
	len = ft_countdigits(number);
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
