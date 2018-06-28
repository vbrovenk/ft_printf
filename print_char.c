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

void	uni_char(int c, char *string)
{
	if (c < 128)
		string[0] = c;
	else if (c < 2048)
	{
		string[0] = (c >> 6 & 31) | 192;
		string[1] = (c & 63) | 128;
	}
	else if (c < 65536)
	{
		string[0] = ((c >> 12) & 15) | 224;
		string[1] = ((c >> 6) & 63) | 128;
		string[2] = (c & 63) | 128;
	}
	else
	{
		string[0] = (c >> 18 & 7) | 224;
		string[1] = (c >> 12 & 63) | 128;
		string[2] = (c >> 6 & 63) | 128;
		string[3] = (c & 63) | 128;
	}
}

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

int		print_char(va_list arg, t_box info)
{
	int		c;
	char	*string;
	char	*temp;
	int		ret;

	c = va_arg(arg, int);
	if ((info.start = info.width - sizeof_sym(c)) < 0)
		info.start = 0;
	string = ft_strnew(sizeof_sym(c));
	uni_char(c, string);
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
	if (info.minus)
	{
		while (info.start-- > 0)
		{
			temp = string;
			string = ft_strjoin(string, " ");
			free(temp);
		}
	}
	else
	{
		while (info.start-- > 0)
		{
			temp = string;
			string = ft_strjoin(" ", string);
			free(temp);
		}
	}
	output_char(c, info, string);
	(c == 0) ? (ret = ft_strlen(string) + 1) : (ret = ft_strlen(string));
	free(string);
	return (ret);
}
