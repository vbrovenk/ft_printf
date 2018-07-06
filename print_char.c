/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:16:00 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/06/26 16:16:02 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// void	uni_char(int c, char *string)
// {
// 	if (c < 128)
// 		string[0] = c;
// 	else if (c < 2048)
// 	{
// 		string[0] = (c >> 6 & 31) | 192;
// 		string[1] = (c & 63) | 128;
// 	}
// 	else if (c < 65536)
// 	{
// 		string[0] = ((c >> 12) & 15) | 224;
// 		string[1] = ((c >> 6) & 63) | 128;
// 		string[2] = (c & 63) | 128;
// 	}
// 	else
// 	{
// 		string[0] = (c >> 18 & 7) | 240;
// 		string[1] = (c >> 12 & 63) | 128;
// 		string[2] = (c >> 6 & 63) | 128;
// 		string[3] = (c & 63) | 128;
// 	}
// }

void	output_char(int c, t_box info, char *string)
{
	if (c == 0)
	{
		if (info.minus)
		{
			write(1, "", 1);
			ft_putstr(string);
		}
		else
		{
			ft_putstr(string);
			write(1, "", 1);
		}
	}
	else
		ft_putstr(string);
}

char	*help_print(t_box info, int c, char *string)
{
	char *temp;

	if ((info.start = info.width - sizeof_sym(c)) < 0)
		info.start = 0;
	if (info.zero == 1 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}
	while (info.sum_zeroes-- > 0)
	{
		temp = string;
		string = ft_strjoin("0", string);
		free(temp);
	}
	string = output(info, string);
	output_char(c, info, string);
	return (string);
}

// int		sizeof_uni(unsigned int c)
// {
// 	if (c < 128 || MB _CUR_MAX != 4)
// 		return (1);
// 	else if (c < 2048)
// 		return (2);
// 	else if (c < 65536)
// 		return (3);
// 	else
// 		return (4);
// }

// int		uni_putchar(unsigned int c)
// {
// 	unsigned char symbol[4];

// 	if (c < 128 || MB_CUR_MAX != 4)
// 		symbol[0] = c;
// 	else if (c < 2048)
// 	{
// 		symbol[0] = (c >> 6 & 31) | 192;
// 		symbol[1] = (c & 63) | 128;
// 	}
// 	else if (c < 65536)
// 	{
// 		symbol[0] = ((c >> 12) & 15) | 224;
// 		symbol[1] = ((c >> 6) & 63) | 128;
// 		symbol[2] = (c & 63) | 128;
// 	}
// 	else
// 	{
// 		symbol[0] = (c >> 18 & 7) | 240;
// 		symbol[1] = (c >> 12 & 63) | 128;
// 		symbol[2] = (c >> 6 & 63) | 128;
// 		symbol[3] = (c & 63) | 128;
// 	}
// 	write(1, &symbol, sizeof_uni(c));
// 	return (sizeof_uni(c));
// }

int		print_uni_char(va_list arg, t_box info)
{
	unsigned int c;
	int ret;

	ret = 0;
	c = va_arg(arg, unsigned int);
	if (c != 0)
		ret += sizeof_sym(c);
	if ((info.start = info.width - sizeof_sym(c)) < 0)
		info.start = 0;
	if (info.zero == 1 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}
	if (info.zero == 1)
		while (info.sum_zeroes-- > 0)
			ret += write (1, "0", 1);
	if (info.minus == 1)
	{
		ft_putchar(c);
		while (info.start-- > 0)
			ret += write(1, " ", 1);
	}
	else
	{
		while (info.start-- > 0)
			ret += write(1, " ", 1);
		ft_putchar(c);
	}
	return ((c == 0) ? (ret + 1) : ret);
}

int		print_char(va_list arg, t_box info)
{
	char	c;
	char	*string;
	int		ret;

	if (ft_strequ(info.length, "l") || ft_strequ(info.length, "ll"))
	{
		free(info.length);
		return (print_uni_char(arg, info));
	}
	c = (char)va_arg(arg, int);
	string = ft_strnew(2);
	string[0] = c;
	string = help_print(info, c, string);
	if (c == 0)
		ret = ft_strlen(string) + 1;
	else
		ret = ft_strlen(string);
	free(string);
	return (ret);
}
