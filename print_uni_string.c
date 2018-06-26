/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uni_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:35:17 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/06/26 16:35:19 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int uni_putstr(int *string, int count_print)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (string[i] != '\0' && len < count_print)
	{
		ft_putchar(string[i]);
		if (string[i] < 128)
			len += 1;
		else if (string[i] < 2048)
			len += 2;
		else if (string[i] < 65536)
			len += 3;
		else
			len += 4;
		i++;
	}
	return (len);
}

int print_uni_string(va_list arg, t_box info)
{
	int *temp;
	int length;
	int i;
	int res;
	char *str;

	temp = va_arg(arg, int*);
	length = 0;
	i = 0;
	res = 0;
	if (temp == NULL)
		str = "(null)";
	else
	{
		while (temp[i] != '\0')
		{
			length += sizeof_sym(temp[i]);
			i++;
		}
	}
	info.start = info.width - length;
	if (info.zero == 1 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}
	while (info.sum_zeroes-- > 0)
		res += write(1, "0", 1);
	// fignya dlya precision 
	if (info.precision == 0)
		info.precision = length;
	if (info.minus)
	{
		if (temp != NULL)
			res += uni_putstr(temp, info.precision);
		else
		{
			ft_putstr(str);
			res += 6;	
		}
		while (info.start-- > 0)
			res += write(1, " ", 1);
	}
	else
	{
		while (info.start-- > 0)
			res += write(1, " ", 1);
		if (temp != NULL)
			res += uni_putstr(temp, info.precision);
		else
		{
			ft_putstr(str);
			res += 6;	
		}
	}
	return (res);
}
