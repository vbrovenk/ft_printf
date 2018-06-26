/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 14:51:32 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/06/26 14:51:34 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	get_octal(va_list arg, t_box info)
{
	uintmax_t nbr;

	if (ft_strequ(info.length, "l") || info.type == 'O')
		nbr = va_arg(arg, unsigned long);
	else if (ft_strequ(info.length, "hh"))
		nbr = (unsigned char)va_arg(arg, unsigned int);
	else if (ft_strequ(info.length, "h"))
		nbr = (unsigned short)va_arg(arg, unsigned int);
	else if (ft_strequ(info.length, "ll"))
		nbr = va_arg(arg, unsigned long long);
	else if (ft_strequ(info.length, "j"))
		nbr = va_arg(arg, uintmax_t);
	else if (ft_strequ(info.length, "z"))
		nbr = (size_t)va_arg(arg, size_t);
	else
		nbr = va_arg(arg, unsigned int);
	return (nbr);
}

void		calc_spaces_oct(t_box *info, char *number)
{
	info->sum_zeroes = info->precision - ft_strlen(number);
	if (info->sum_zeroes < 0)
		info->sum_zeroes = 0;
	info->start = info->width - info->sum_zeroes - ft_strlen(number);
	if (info->start < 0)
		info->start = 0;
	if (info->hash == 1 && info->sum_zeroes == 0 && number[0] != '0')
	{
		info->prefix = "0";
		info->start -= 1;
	}
	if (info->zero == 1 && info->precision == 0 && info->minus == 0)
	{
		info->sum_zeroes += info->start;
		info->start = 0;
	}
}

int			print_octal(va_list arg, t_box info)
{
	uintmax_t	nbr;
	char		*number;

	nbr = get_octal(arg, info);
	number = ft_itoa_base(nbr, 8, 0);
	if (info.precision == -1 && nbr == 0)
	{
		number = ft_strdup("");
		info.precision = 0;
	}
	calc_spaces_oct(&info, number);
	while (info.sum_zeroes-- > 0)
		number = ft_strjoin("0", number);
	number = ft_strjoin(info.prefix, number);
	if (info.minus)
		while (info.start-- > 0)
			number = ft_strjoin(number, " ");
	else
		while (info.start-- > 0)
			number = ft_strjoin(" ", number);
	ft_putstr(number);
	return (ft_strlen(number));
}
