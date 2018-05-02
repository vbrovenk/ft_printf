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

// get width
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

void reset_box(t_box *info)
{
	info->minus = 0;
	info->plus = 0;
	info->space = 0;
	info->zero = 0;
	info->width = 0;
	info->hash = 0;
	info->precision = 0;
	info->type = '\0';
}

void print_struct(t_box info)
{
	printf("info.minus = %d\n", info.minus);
	printf("info.plus = %d\n", info.plus);
	printf("info.space = %d\n", info.space);
	printf("info.zero = %d\n", info.zero);
	printf("info.width = %d\n", info.width);
	printf("info.hash = %d\n", info.hash);
	printf("info.precision = %d\n", info.precision);
	printf("info.type = %c\n", info.type);
}

int is_correct_type(char t)
{
	if (t == 's' || t == 'S' || t == 'p' || t == 'd' || t == 'D'\
		|| t == 'i' || t == 'o' || t == 'O' || t == 'u' || t == 'U'\
		|| t == 'x' || t == 'X' || t == 'c' || t == 'C')
	{
		return (1);
	}
	return (0);
}

int ft_printf(const char *format, ...)
{
	int i;
	va_list arg;
	t_box info;

	va_start(arg, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			reset_box(&info);
			i++;
			/* =================== Parse flags ==================== */
			while (!is_correct_type(format[i]))
			{
				if (format[i] == '-')
				{
					info.minus = 1;
					i++;
				}
				if (format[i] == '+')
				{
					info.plus = 1;
					i++;
				}
				if (format[i] == ' ')
				{
					info.space = 1;
					while (format[i] == ' ')
						i++;
				}
				if (format[i] == '#')
				{
					info.hash = 1;
					i++;
				}
				// flag 0
				if (format[i] == '0')
				{
					info.zero = 1;
					i++;
				}
				// width
				if (format[i] > '0' && format[i] <= '9')
				{
					info.width = from_stoi(&format[i]);
					i += count_width(&format[i]);
				}
				if (format[i] == '.')
				{
					i++;
					info.precision = from_stoi(&format[i]);
					i += count_width(&format[i]);
				}
			}
			info.type = format[i];
			print_struct(info);
			printf("\n");
			/*================== S ===================*/
			// if (format[i] == 's')
			// {
			// 	char *str = va_arg(arg, char *);
			// 	ft_putstr(str);
			// }
			/*================== D ===================*/
			// else if (format[i] == 'd' || format[i] == 'i')
			// {
			// 	int	num = va_arg(arg, int);
			// 	// width
			// 	if (info.width != 0 && info.minus == 0)
			// 	{
			// 		info.width -= ft_countdigits(num);
			// 		if (info.plus == 1 && num >= 0)
			// 			info.width--;
			// 		if (info.space == 1)
			// 			info.width--;
			// 		while (info.width-- > 0)
			// 			write(1, " ", 1);
			// 	}
			// 	if (num >= 0 && info.plus == 1)
			// 		write(1, "+", 1);
			// 	else if (num >= 0 && info.space == 1)
			// 		write(1, " ", 1);
			// 	if (info.width != 0 && info.minus == 1)
			// 	{
			// 		info.width -= ft_countdigits(num);
			// 		if (info.plus == 1 && num >= 0)
			// 			info.width--;
			// 		if (info.space == 1)
			// 			info.width--;

			// 	}
			// 	// print zeros
			// 	if (info.zero != 0)
			// 	{
			// 		//for '-' before zeros
			// 		info.zero -= ft_countdigits(num);
			// 		if (num < 0)
			// 		{
			// 			write(1, "-", 1);
			// 			num *= -1;
			// 		}
			// 		if (info.plus == 1)
			// 			info.zero--;
			// 		if (info.space == 1)
			// 			info.zero--;
			// 		while (info.zero-- > 0)
			// 			write(1, "0", 1);
			// 	}
			// 	ft_putnbr(num);
			// }
			/*================== X ===================*/
			// else if (format[i] == 'x')
			// {
			// 	int num = va_arg(arg, int);
			// 	char *str = ft_itoa_base(num, 16, 0);
			// 	if (info.width != 0)
			// 	{
			// 		info.width -= ft_strlen(str);
			// 		while (info.width-- > 0)
			// 			write(1, " ", 1); 
			// 	}
			// 	if (info.zero != 0)
			// 	{
			// 		info.zero -= ft_strlen(str);
			// 		while (info.zero-- > 0)
			// 			write(1, "0", 1);
			// 	}
			// 	ft_putstr(str);
			// }
			// else if (format[i] == 'X')
			// {
			// 	int num = va_arg(arg, int);
			// 	char *str = ft_itoa_base(num, 16, 1);
			// 	ft_putstr(str);
			// }
			/*================== O ===================*/
			// else if (format[i] == 'o')
			// {
			// 	int num = va_arg(arg, int);
			// 	char *temp = ft_itoa_base(num, 8, 0);
			// 	ft_putstr(temp);
			// }
		}
		else
			write(1, &format[i], 1);
		i++;
	}
	return (1);
}

int main()
{
	char n[] = "Chaynik";
	int nbr = 10;
	int nbr2 = 228;
	int my_ret, orig_ret;

	ft_printf("%- 35.10d %+0#d\n", nbr, nbr2);

	/* ----------ORIGINAL----------*/

	// printf("%.10d\n", 12345);
	// printf("%010d\n", 12345);
	return (0);
}