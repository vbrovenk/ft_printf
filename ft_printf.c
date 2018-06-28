/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 15:29:24 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/04/30 15:29:26 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

int		is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '0' || c == '#')
		return (1);
	return (0);
}

int		is_correct_type(char t)
{
	if (t == 's' || t == 'S' || t == 'p' || t == 'd' || t == 'D'\
		|| t == 'i' || t == 'o' || t == 'O' || t == 'u' || t == 'U'\
		|| t == 'x' || t == 'X' || t == 'c' || t == 'C')
	{
		return (1);
	}
	return (0);
}

void	reset_box(t_box *info)
{
	info->minus = 0;
	info->plus = 0;
	info->space = 0;
	info->zero = 0;
	info->hash = 0;
	info->width = 0;
	info->precision = 0;
	info->length = 0;
	info->type = 0;
	info->start = 0;
	info->sum_zeroes = 0;
	info->prefix = 0;
}

void	put_flag(t_box *info, char c)
{
	if (c == '-')
		info->minus = 1;
	else if (c == '+')
		info->plus = 1;
	else if (c == ' ')
		info->space = 1;
	else if (c == '0')
		info->zero = 1;
	else if (c == '#')
		info->hash = 1;
}

int		sizeof_sym(int c)
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

int		print(va_list arg, t_box info)
{
	int ret;

	ret = 0;
	if (info.type == 'd' || info.type == 'i' || info.type == 'D')
		ret = print_dec(arg, info);
	else if (info.type == 'u' || info.type == 'U')
		ret = print_unsigned(arg, info);
	else if (info.type == 'x' || info.type == 'X' || info.type == 'p')
		ret = print_hex(arg, info);
	else if (info.type == 'o' || info.type == 'O')
		ret = print_octal(arg, info);
	else if (info.type == 'c' || info.type == 'C')
		ret = print_char(arg, info);
	else if (info.type == 's')
		ret = print_string(arg, info);
	else if (info.type == 'S')
		ret = print_uni_string(arg, info);
	return (ret);
}

t_box	fill_flags(const char *format, int *i, t_box info)
{
	int start;
	char *temp;

	while (is_flag(format[*i]))
	{
		put_flag(&info, format[*i]);
		(*i)++;
	}
	while (ft_isdigit(format[*i]))
	{
		start = *i;
		while (ft_isdigit(format[*i]))
			(*i)++;
		temp = ft_strsub(format, start, *i - start);
		info.width = ft_atoi(temp);
		free(temp);
	}
	while (is_flag(format[*i]))
	{
		put_flag(&info, format[*i]);
		(*i)++;
	}
	return (info);
}

t_box	fill_precision(const char *format, int *i, t_box info)
{
	int start;
	char *temp;

	if (format[*i] == '.')
	{
		(*i)++;
		start = *i;
		while (ft_isdigit(format[*i]))
			(*i)++;
		temp = ft_strsub(format, start, *i - start);
		info.precision = ft_atoi(temp);
		free(temp);
		if (info.precision == 0)
			info.precision = -1;
	}
	if (is_length(format[*i]))
	{
		start = *i;
		while (is_length(format[*i]))
			(*i)++;
		info.length = ft_strsub(format, start, *i - start);
	}
	return (info);
}

int		print_spaces(t_box info)
{
	int ret;

	ret = 0;
	if (info.zero == 1 && info.minus == 0)
	{
		while (--info.width > 0)
			ret += write(1, "0", 1);
	}
	if (info.minus == 1)
	{
		ret += write(1, &info.type, 1);
		while (--info.width > 0)
			ret += write(1, " ", 1);
	}
	else
	{
		while (--info.width > 0)
			ret += write(1, " ", 1);
	ret += write(1, &info.type, 1);
	}
	return (ret);
}

void		out_types(const char *format, int i, int *ret, va_list arg, t_box info)
{
	if (format[i] == '%')
		*ret += print_percent(info);
	if (is_correct_type(format[i]))
	{
		info.type = format[i];
		*ret += print(arg, info);
	}
	else if (format[i] != '%')
	{
		info.type = format[i];
		*ret += print_spaces(info);
	}
}

int		ft_printf(const char *format, ...)
{
	va_list arg;
	t_box info;
	int i;
	int ret;

	va_start(arg, format);
	ret = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			reset_box(&info);
			i++;
			if (format[i] == '\0')
				break ;
			info = fill_flags(format, &i, info);
			info = fill_precision(format, &i, info);
			out_types(format, i, &ret, arg, info);
		}
		else
		{
			ret++;
			write(1, &format[i], 1);
		}
		i++;
	}
	return (ret);
}

int main()
{
	char *str = "Hello";
	long nbr = -922337203;

	int nbr2 = -42;

	int ret_org;
	int ret_my;
	// ========= MY =========
	ret_my = ft_printf("%10.15u\n", 301);

	// ========== ORIGINAL ==========
	ret_org = printf("%10.15u\n", 300);
	
	printf("ORG %d | MY %d\n", ret_org, ret_my);
	while (1)
		;
	return (0);
}