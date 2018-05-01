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

#include <stdarg.h>
#include <stdio.h>
#include "libft/libft.h"
#include "ft_printf.h"

int from_stoi(const char *str)
{
	int i;
	int nbr;

	i = 0;
	nbr = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr);
}

int count_width(const char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		i++;
	}
	return (i);
}

int ft_printf(const char *format, ...)
{
	int i;
	va_list arg;
	t_box box;
	int temp;         //var for flag 0
	int temp_width = 0;   //var for flag width 

	va_start(arg, format);
	i = 0;
	box.length = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '+')
			{
				box.plus = 1;
				i++;
			}
			if (format[i] == ' ')
			{
				box.space = 1;
				while (format[i] == ' ')
					i++;
			}
			// flag 0
			if (format[i] == '0')
			{
				box.zero = 1;
				temp = from_stoi(&format[i]);
				i += count_width(&format[i]);
			}
			// width
			if (format[i] > '0' && format[i] <= '9')
			{
				temp_width = from_stoi(&format[i]);
				i += count_width(&format[i]);
			}
			if (format[i] == 's')
			{
				char *str = va_arg(arg, char *);
				ft_putstr(str);
				box.length += ft_strlen(str);
			}
			else if (format[i] == 'd' || format[i] == 'i')
			{
				int	num = va_arg(arg, int);
				// width
				if (temp_width != 0)
				{
					temp_width -= ft_countdigits(num);
					if (box.plus == 1)
						temp_width--;
					while (temp_width -- > 0)
						write(1, " ", 1);
				}
				if (num >= 0 && box.plus == 1)
					write(1, "+", 1);
				else if (num >= 0 && box.space == 1)
					write(1, " ", 1);
				// print zeros
				if (box.zero == 1)
				{
					temp -= ft_countdigits(num);
					if (box.plus == 1)
						temp--;
					if (box.space == 1)
						temp--;
					while (temp-- > 0)
						write(1, "0", 1);
				}
				ft_putnbr(num);
				box.length += ft_countdigits(num);
			}
			else if (format[i] == 'x')
			{
				int num = va_arg(arg, int);
				char *temp = ft_itoa_base(num, 16, 0);
				ft_putstr(temp);
				box.length += ft_strlen(temp);
			}
			else if (format[i] == 'X')
			{
				int num = va_arg(arg, int);
				char *temp = ft_itoa_base(num, 16, 1);
				ft_putstr(temp);
				box.length += ft_strlen(temp);
			}
			else if (format[i] == 'o')
			{
				int num = va_arg(arg, int);
				char *temp = ft_itoa_base(num, 8, 0);
				ft_putstr(temp);
				box.length += ft_strlen(temp);
			}
			// else if (format[i] == 'p')
			// {
			// 	int num = va_arg(arg, int);
			// 	char *temp = ft_itoa_base(num, 16, 0);
			// }
		}
		else
		{
			write(1, &format[i], 1);
			box.length += 1;
		}
		i++;
	}
	return (box.length);
}

int main()
{
	char n[] = "Chaynik";
	int nbr = 10;
	int my_ret, orig_ret;

	ft_printf("%d\n", nbr);
	/* ----------ORIGINAL----------*/
	printf("%d\n", nbr);
	return (0);
}