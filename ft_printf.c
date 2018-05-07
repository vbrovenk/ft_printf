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

int	ft_countdigits_my(intmax_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i = 1;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}


void	ft_putnbr_my(intmax_t n)
{
	// if (n == (-2147483648))
	// {
	// 	write(1, "-2147483648", 11);
	// 	return ;
	// }
	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
	}
	if (n >= 10)
	{
		ft_putnbr_my(n / 10);
		ft_putchar((n % 10) + '0');
	}
	else
		ft_putchar(n + '0');
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

void precision(intmax_t num, t_box *info)
{
	info->precision -= ft_countdigits_my(num);
	if (info->precision > 0)
	{
		info->width -= info->precision;
	}
}

void print(intmax_t num, t_box *info)
{
	if (num < 0 && info->precision > 0)
		// +1 fot sign '-'
		info->precision  +=  1;
	// printf("width %d\n", info->width);
	// printf("precision %d\n", info->precision);
	// printing '-' before zeros
	if (num < 0 && info->precision > 0)
		info->width--;
	if (num < 0 && info->zero == 1)
	{
		write(1, "-", 1);
		num = -num;
		info->plus = 0; // becouse don't need to print '+'
	}
	if (info->minus == 0)
	{
		// '+' before zeros
		if (info->zero == 1 && info->precision == 0)
		{

			if (num >= 0 && info->plus == 1)
			{
				printf("%d\n", num);
				write (1, "+", 1);
			}
			while (info->width-- > 0)
				write(1, "0", 1);
		}
		else
		{
			while (info->width-- > 0)
				write(1, " ", 1);
			if (num >= 0 && info->plus == 1)
				write(1, "+", 1);
			if (info->precision > 0)
			{
				if (num < 0)
				{
					write(1, "-", 1);
					num = -num;
				}
				while (info->precision-- > 0)
					write(1, "0", 1);
			}
		}
		ft_putnbr_my(num);
		return ;
	}
	else
	{
		if (num >= 0 && info->plus == 1 && info->zero == 1)
			write(1, "+", 1);
		if (info->precision != 0)
		{
			if (num < 0)
			{
				write(1, "-", 1);
				num = -num;
			}
			while (info->precision-- > 0)
				write(1, "0", 1);
		}
		ft_putnbr_my(num);
		while (info->width-- > 0)
			write(1, " ", 1);

		return ;
	}
	ft_putnbr_my(num);
}

void print_d(va_list arg, t_box *info, const char *format)
{
	intmax_t num;
	/*============= length =============*/
	if (info->length == '1')
	{
		num = (char)va_arg(arg, int);
	}
	else if (info->length == 'h')
	{
		num = (short)va_arg(arg, int);
	}
	else if (info->length == 'l')
	{
		num = va_arg(arg, long);
	}
	else if (info->length == '2')
	{
		num = va_arg(arg, long long);
	}
	else
		num = va_arg(arg, int);

	// int num = va_arg(arg, int);

	info->width -= ft_countdigits_my(num);
	if (num >= 0 && info->plus == 1)
		info->width--;
	if (num >= 0 && info->space == 1 && info->plus == 0)
	{
		info->width--;
		write(1, " ", 1);
	}

	if (num >= 0 && info->plus == 1 && info->zero == 0 && info->minus == 1)
	{
		write(1, "+", 1);
	}
	/* ================== Precision ===================== */
	if (info->precision != 0)
		precision(num, info);
	print(num, info);
}

void print_x(va_list arg, t_box *info, const char *format)
{
	int num = va_arg(arg, int);
	char *str = ft_itoa_base(num, 16, 0);

	info->width -= ft_strlen(str);
	info->precision = info->precision - ft_strlen(str);
	if (info->precision && info->width > info->precision)
	{
		info->width -= info->precision;
	}
	if (info->minus == 0)
	{
		while (info->width-- > 0)
			write(1, " ", 1);
		while (info->precision-- > 0)
			write(1, "0", 1);
		ft_putstr(str);
	}
	else
	{
		ft_putstr(str);
		while (info->width-- > 0)
			write(1, " ", 1);
	}
}

void reset_box(t_box *info)
{
	info->minus = 0;
	info->plus = 0;
	info->space = 0;
	info->zero = 0;
	info->hash = 0;
	info->width = 0;
	info->precision = 0;
	// info->length = 0;
	info->type = '\0';
}

void print_struct(t_box info)
{
	printf("info.minus = %d\n", info.minus);
	printf("info.plus = %d\n", info.plus);
	printf("info.space = %d\n", info.space);
	printf("info.zero = %d\n", info.zero);
	printf("info.hash = %d\n", info.hash);
	printf("info.width = %d\n", info.width);
	printf("info.precision = %d\n", info.precision);
	printf("info.length = %c\n", info.length);
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
	int temp;		// remember index for getting number
	char *number;   // getting str(number) for ft_atoi

	va_start(arg, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			reset_box(&info);
			i++;
			/* =================== Parse flags ==================== */
			while (format[i] && !is_correct_type(format[i]))
			{
				// if ()
				if (format[i] == '-')
				{
					info.minus = 1;
					i++;
				}
				else if (format[i] == '+')
				{
					info.plus = 1;
					i++;
				}
				else if (format[i] == ' ')
				{
					info.space = 1;
					while (format[i] == ' ')
						i++;
				}
				else if (format[i] == '#')
				{
					info.hash = 1;
					i++;
				}
				// flag 0
				else if (format[i] == '0')
				{
					info.zero = 1;
					i++;
				}
				// width
				else if (format[i] > '0' && format[i] <= '9')
				{
					temp = i;
					i += count_width(&format[i]);
					number = ft_strsub(format, temp, i - temp);
					info.width = ft_atoi(number);
				}
				else if (format[i] == '.')
				{
					i++;
					temp = i;
					i += count_width(&format[i]);
					number = ft_strsub(format, temp, i - temp);
					info.precision = ft_atoi(number);
				}
				else if (format[i] == 'h' && format[i + 1] == 'h')
				{
					info.length = '1';
					i += 2;
				}
				else if (format[i] == 'h')
				{
					info.length = 'h';
					i++;
				}
				else if (format[i] == 'l' && format[i + 1] == 'l')
				{
					info.length = '2';
					i += 2;
				}
				else if (format[i] == 'l')
				{
					info.length = 'l';
					i++;
				}
				else if (format[i] == 'j')
				{
					info.length = 'j';
					i++;
				}
				else if (format[i] == 'z')
				{
					info.length = 'z';
					i++;
				}
				else
				{
					if (is_correct_type(format[i]))
						break ;
					i++;
				}
			}
			info.type = format[i];
			// print_struct(info);
			// printf("\n");
			/*================== S ===================*/
			// if (format[i] == 's')
			// {
			// 	char *str = va_arg(arg, char *);
			// 	ft_putstr(str);
			// }
			/*================== D ===================*/
			// else 
			if (info.type == 'd' || info.type == 'i')
			{
				print_d(arg, &info, format);
			}
			/*================== X ===================*/
			else if (format[i] == 'x')
			// {

				print_x(arg, &info, format);
			// 	if (info.width != 0)
			// 	{
					 
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

void	tests_integer(void)
{
	int i = 74395;
	int j;
	int min = -123456;
	int max = 2147483647;

	ft_printf("========== simple ==========\n"); j = 1;

	printf("%d OR: %i@\n", j, i); // simple
	ft_printf("%d FT: %i@\n", j, i);
	j++;
	printf("%d OR: %i@\n", j, -i);
	ft_printf("%d FT: %i@\n", j, -i);
	j++;
	printf("%d OR: %i@\n", j, 0);
	ft_printf("%d FT: %i@\n", j, 0);
	j++;
	printf("%d OR: %i@\n", j, min);
	ft_printf("%d FT: %i@\n", j, min);
	j++;
	printf("%d OR: %i@\n", j, max);
	ft_printf("%d FT: %i@\n", j, max);
	j++;

	ft_printf("========== width ==========\n"); j = 1;

	printf("%d OR: %3i@\n", j, i);
	ft_printf("%d FT: %3i@\n", j, i);
	j++;
	printf("%d OR: %20i@\n", j, i);
	ft_printf("%d FT: %20i@\n", j, i);
	j++;
	printf("%d OR: %3i@\n", j, -i);
	ft_printf("%d FT: %3i@\n", j, -i);
	j++;
	printf("%d OR: %20i@\n", j, -i);
	ft_printf("%d FT: %20i@\n", j, -i);
	j++;
	printf("%d OR: %10i@\n", j, 0);
	ft_printf("%d FT: %10i@\n", j, 0);
	j++;
	printf("%d OR: %20i@\n", j, min);
	ft_printf("%d FT: %20i@\n", j, min);
	j++;
	printf("%d OR: %20i@\n", j, max);
	ft_printf("%d FT: %20i@\n", j, max);
	j++;

	ft_printf("========== precision ==========\n"); j = 1;

	printf("%d OR: %.3i@\n", j, i);
	ft_printf("%d FT: %.3i@\n", j, i);
	j++;
	printf("%d OR: %.20i@\n", j, i);
	ft_printf("%d FT: %.20i@\n", j, i);
	j++;
	printf("%d OR: %.3i@\n", j, -i);
	ft_printf("%d FT: %.3i@\n", j, -i);
	j++;
	printf("%d OR: %.20i@\n", j, -i);
	ft_printf("%d FT: %.20i@\n", j, -i);
	j++;
	printf("%d OR: %.10i@\n", j, 0);
	ft_printf("%d FT: %.10i@\n", j, 0);
	j++;
	printf("%d OR: %.20i@\n", j, min);
	ft_printf("%d FT: %.20i@\n", j, min);
	j++;
	printf("%d OR: %.20i@\n", j, max);
	ft_printf("%d FT: %.20i@\n", j, max);
	j++;

	ft_printf("========== width + precision ==========\n"); j = 1;

	printf("%d OR: %1.3i@\n", j, i);
	ft_printf("%d FT: %1.3i@\n", j, i);
	j++;
	printf("%d OR: %1.20i@\n", j, i);
	ft_printf("%d FT: %1.20i@\n", j, i);
	j++;
	printf("%d OR: %3.20i@\n", j, i);
	ft_printf("%d FT: %3.20i@\n", j, i);
	j++;
	printf("%d OR: %10.20i@\n", j, i);
	ft_printf("%d FT: %10.20i@\n", j, i);
	j++;
	printf("%d OR: %20.10i@\n", j, i);
	ft_printf("%d FT: %20.10i@\n", j, i);
	j++;
	printf("%d OR: %20.5i@\n", j, i);
	ft_printf("%d FT: %20.5i@\n", j, i);
	j++;
	printf("%d OR: %1.3i@\n", j, -i);
	ft_printf("%d FT: %1.3i@\n", j, -i);
	j++;
	printf("%d OR: %1.20i@\n", j, -i);
	ft_printf("%d FT: %1.20i@\n", j, -i);
	j++;
	printf("%d OR: %3.20i@\n", j, -i);
	ft_printf("%d FT: %3.20i@\n", j, -i);
	j++;
	printf("%d OR: %10.20i@\n", j, -i);
	ft_printf("%d FT: %10.20i@\n", j, -i);
	j++;
	printf("%d OR: %5.10i@\n", j, 0);
	ft_printf("%d FT: %5.10i@\n", j, 0);
	j++;
	printf("%d OR: %10.5i@\n", j, 0);
	ft_printf("%d FT: %10.5i@\n", j, 0);
	j++;
	printf("%d OR: %10.20i@\n", j, min);
	ft_printf("%d FT: %10.20i@\n", j, min);
	j++;
	printf("%d OR: %20.10i@\n", j, min);
	ft_printf("%d FT: %20.10i@\n", j, min);
	j++;
	printf("%d OR: %10.20i@\n", j, max);
	ft_printf("%d FT: %10.20i@\n", j, max);
	j++;

	ft_printf("========== minus + width ==========\n"); j = 1;

	printf("%d OR: %-3i@\n", j, i);
	ft_printf("%d FT: %-3i@\n", j, i);
	j++;
	printf("%d OR: %-20i@\n", j, i);
	ft_printf("%d FT: %-20i@\n", j, i);
	j++;
	printf("%d OR: %-3i@\n", j, -i);
	ft_printf("%d FT: %-3i@\n", j, -i);
	j++;
	printf("%d OR: %-20i@\n", j, -i);
	ft_printf("%d FT: %-20i@\n", j, -i);
	j++;
	printf("%d OR: %-10i@\n", j, 0);
	ft_printf("%d FT: %-10i@\n", j, 0);
	j++;
	printf("%d OR: %-20i@\n", j, min);
	ft_printf("%d FT: %-20i@\n", j, min);
	j++;
	printf("%d OR: %-20i@\n", j, max);
	ft_printf("%d FT: %-20i@\n", j, max);
	j++;

	

	ft_printf("========== plus ==========\n"); j = 1;

	printf("%d OR: %i@\n", j, i); // simple
	ft_printf("%d FT: %i@\n", j, i);
	j++;
	printf("%d OR: %i@\n", j, -i);
	ft_printf("%d FT: %i@\n", j, -i);
	j++;
	printf("%d OR: %i@\n", j, 0);
	ft_printf("%d FT: %i@\n", j, 0);
	j++;
	printf("%d OR: %i@\n", j, min);
	ft_printf("%d FT: %i@\n", j, min);
	j++;
	printf("%d OR: %i@\n", j, max);
	ft_printf("%d FT: %i@\n", j, max);
	j++;

	ft_printf("========== width + precision + minus ==========\n"); j = 1;

	printf("%d OR: %-1.3i@\n", j, i);
	ft_printf("%d FT: %-1.3i@\n", j, i);
	j++;
	printf("%d OR: %-1.20i@\n", j, i);
	ft_printf("%d FT: %-1.20i@\n", j, i);
	j++;
	printf("%d OR: %-3.20i@\n", j, i);
	ft_printf("%d FT: %-3.20i@\n", j, i);
	j++;
	printf("%d OR: %-10.20i@\n", j, i);
	ft_printf("%d FT: %-10.20i@\n", j, i);
	j++;
	printf("%d OR: %-20.10i@\n", j, i);
	ft_printf("%d FT: %-20.10i@\n", j, i);
	j++;
	printf("%d OR: %-20.5i@\n", j, i);
	ft_printf("%d FT: %-20.5i@\n", j, i);
	j++;
	printf("%d OR: %-1.3i@\n", j, -i);
	ft_printf("%d FT: %-1.3i@\n", j, -i);
	j++;
	printf("%d OR: %-1.20i@\n", j, -i);
	ft_printf("%d FT: %-1.20i@\n", j, -i);
	j++;
	printf("%d OR: %-3.20i@\n", j, -i);
	ft_printf("%d FT: %-3.20i@\n", j, -i);
	j++;
	printf("%d OR: %-10.20i@\n", j, -i);
	ft_printf("%d FT: %-10.20i@\n", j, -i);
	j++;
	printf("%d OR: %-5.10i@\n", j, 0);
	ft_printf("%d FT: %-5.10i@\n", j, 0);
	j++;
	printf("%d OR: %-10.5i@\n", j, 0);
	ft_printf("%d FT: %-10.5i@\n", j, 0);
	j++;
	printf("%d OR: %-10.20i@\n", j, min);
	ft_printf("%d FT: %-10.20i@\n", j, min);
	j++;
	printf("%d OR: %-20.10i@\n", j, min);
	ft_printf("%d FT: %-20.10i@\n", j, min);
	j++;
	printf("%d OR: %-10.20i@\n", j, max);
	ft_printf("%d FT: %-10.20i@\n", j, max);
	j++;

	// printf("%0i\n", i);
	// printf("% +q\n", i);
	// printf("%-0i\n", i);
	// printf("%+i\n", i);
	// printf("%#i\n", i);
}

// void test_42(void)
// {
// 	ft_printf("%d\n", 2147483648);                  //-> "-2147483648"
// 	   printf("%d\n", 2147483648);
//  	ft_printf("%d\n", -2147483648);                 //-> "-2147483648"
//  	   printf("%d\n", -2147483648);
//  	ft_printf("%d\n", -2147483649);                 //-> "2147483647"
//  	   printf("%d\n", -2147483649);
//  	ft_printf("% d\n", 42);                         //-> " 42"
//  	   printf("% d\n", 42);
//  	ft_printf("% d\n", -42);                        //-> "-42"
//  	   printf("% d\n", -42);
//  	ft_printf("%+d\n", 42);                         //-> "+42"
//  	   printf("%+d\n", 42);
//  	ft_printf("%+d\n", -42);                        //-> "-42"
//  	   printf("%+d\n", -42);
//  	ft_printf("%+d\n", 0);                          //-> "+0"
//  	   printf("%+d\n", 0);
//  	// ft_printf("%+d\n", 4242424242424242424242);     //-> "-1"
//  	   // printf("%+d\n", 4242424242424242424242);
//  	ft_printf("% +d\n", 42);                        //-> "+42"
//  	   printf("% +d\n", 42);
//  	ft_printf("% +d\n", -42);                       //-> "-42"
//  	   printf("% +d\n", -42);
//  	ft_printf("%+ d\n", 42);                        //-> "+42"
//  	   printf("%+ d\n", 42);
//  	ft_printf("%+ d\n", -42);                       //-> "-42"
//  	   printf("%+ d\n", -42);
//  	ft_printf("%  +d\n", 42);                       //-> "+42"
//  	   printf("%  +d\n", 42); 
//  	ft_printf("%  +d\n", -42);                      //-> "-42"
//  	   printf("%  +d\n", -42);
//  	ft_printf("%+  d\n", 42);                       //-> "+42"
//  	   printf("%+  d\n", 42);
//  	ft_printf("%+  d\n", -42);                      //-> "-42"
//  	   printf("%+  d\n", -42);
//  	ft_printf("% ++d\n", 42);                       //-> "+42"
//  	   printf("% ++d\n", 42);
//  	ft_printf("% ++d\n", -42);                      //-> "-42"
//  	   printf("% ++d\n", -42);
//  	ft_printf("%++ d\n", 42);                       //-> "+42"
//  	   printf("%++ d\n", 42);
//  	ft_printf("%++ d\n", -42);                      //-> "-42"
//  	   printf("%++ d\n", -42);
//  	ft_printf("%0d\n", -42);                        //-> "-42"
//  	   printf("%0d\n", -42);
//  	ft_printf("%00d\n", -42);                       //-> "-42"
//  	   printf("%00d\n", -42);
//  	ft_printf("%5d\n", 42);                         //-> "   42"
//  	   printf("%5d\n", 42);
//  	ft_printf("%05d\n", 42);                        //-> "00042"
//  	   printf("%05d\n", 42);
//  	ft_printf("%0+5d\n", 42);                       //-> "+0042"
//  	   printf("%0+5d\n", 42); 
//  	ft_printf("%5d\n", -42);                        //-> "  -42"
//  	   printf("%5d\n", -42); 
//  	ft_printf("%05d\n", -42);                       //-> "-0042"
//  	   printf("%05d\n", -42);
//  	ft_printf("%0+5d\n", -42);                      //-> "-0042"
//  	   printf("%0+5d\n", -42); 
//  	ft_printf("%-5d\n", 42);                        //-> "42   "
//  	   printf("%-5d\n", 42); 
//  	ft_printf("%-05d\n", 42);                       //-> "42   "
//  	   printf("%-05d\n", 42);
//  	ft_printf("%-5d\n", -42);                       //-> "-42  "
//  	   printf("%-5d\n", -42); 
//  	ft_printf("%-05d\n", -42);                      //-> "-42  "
//  	   printf("%-05d\n", -42);
// }

int main()
{
	char n[] = "Chaynik";
	// long long nbr = -9223372036854775808;
	int nbr = -2147483649;
	int nbr2 = 228;
	// int my_ret, orig_ret;

	ft_printf("%hd\n", nbr);

	/* ----------ORIGINAL----------*/

	printf("%hd\n", nbr);

	// tests_integer();
	// test_42();
	return (0);
}

