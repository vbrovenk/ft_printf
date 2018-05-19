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
#include <stdarg.h>

int	is_length(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

int is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '0' || c == '#')
		return (1);
	return (0);
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

void print_struct(t_box info)
{
	printf("info.minus = %d\n", info.minus);
	printf("info.plus = %d\n", info.plus);
	printf("info.space = %d\n", info.space);
	printf("info.zero = %d\n", info.zero);
	printf("info.hash = %d\n", info.hash);
	printf("info.width = %d\n", info.width);
	printf("info.precision = %d\n", info.precision);
	printf("info.length %s\n", info.length);
	printf("info.type = %c\n", info.type);
	printf("info.start = %d\n", info.start);
	printf("info.sum_zeroes = %d\n", info.sum_zeroes);
	printf("info.prefix = %s\n", info.prefix);

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
	info->length = 0;
	info->type = 0;

	info->start = 0;
	info->sum_zeroes = 0;
	info->prefix = 0;
}

void put_flag(t_box *info, char c)
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

int print_dec(va_list arg, t_box info)
{
	intmax_t nbr;
	char *number;
	char *temp;

	if (ft_strequ(info.length, "hh"))
		nbr = (char)va_arg(arg, int);
	else if (ft_strequ(info.length, "h"))
		nbr = (short)va_arg(arg, int);
	else if (ft_strequ(info.length, "ll"))
		nbr = va_arg(arg, long long);
	else if (ft_strequ(info.length, "l"))
		nbr = va_arg(arg, long);
	else if (ft_strequ(info.length, "j"))
		nbr = va_arg(arg, intmax_t);
	else if (ft_strequ(info.length, "z"))
		nbr = (size_t)va_arg(arg, size_t);
	else
		nbr = va_arg(arg, int);

	number = my_itoa(nbr);
	if (nbr < 0)
	{
		info.prefix = "-";
		number = ft_strsub(number, 1, ft_strlen(number) - 1);
	}
	if ((info.sum_zeroes = info.precision - ft_strlen(number)) < 0)
		info.sum_zeroes = 0;
	info.start = info.width - info.sum_zeroes - ft_strlen(number) - ft_strlen(info.prefix);
	if (info.start < 0)
		info.start = 0;
	if (info.space == 1 && nbr >= 0)
	{
		info.prefix = " ";
		info.start -= 1;
	}
	if (info.plus == 1 && nbr >= 0)
	{
		info.prefix = "+";
		info.start -= 1;
	}
	if (info.zero == 1 && info.precision == 0 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}
	
	while (info.sum_zeroes-- > 0)
		number = ft_strjoin("0", number);
	number = ft_strjoin(info.prefix, number);
	if (info.minus)
		while (info.start-- > 0)
			number = ft_strjoin(number, " ");
	else
		while (info.start-- > 0)
			number = ft_strjoin(" ", number);

	// temp = ft_strnew(info.start);
	// ft_memset(temp, " ", info.start);
	// if (info.minus)
	// 	number = ft_strjoin(number, temp);
	// else
	// 	number = ft_strjoin(temp, number);
	ft_putstr(number);
	return (ft_strlen(number));
}

int print_unsigned(va_list arg, t_box info)
{
	uintmax_t nbr;
	char *number;

	if (ft_strequ(info.length, "hh"))
		nbr = (unsigned char)va_arg(arg, unsigned int);
	else if (ft_strequ(info.length, "h"))
		nbr = (unsigned short)va_arg(arg, unsigned int);
	else if (ft_strequ(info.length, "ll"))
		nbr = va_arg(arg, unsigned long long);
	else if (ft_strequ(info.length, "l"))
		nbr = va_arg(arg, unsigned long);
	else if (ft_strequ(info.length, "j"))
		nbr = va_arg(arg, uintmax_t);
	else if (ft_strequ(info.length, "z"))
		nbr = (size_t)va_arg(arg, size_t);
	else
		nbr = va_arg(arg, unsigned int);

	number = my_itoa(nbr);

	info.sum_zeroes = info.precision - ft_strlen(number);
	if (info.sum_zeroes < 0)
		info.sum_zeroes = 0;
	info.start = info.width - info.sum_zeroes - ft_strlen(number);
	if (info.start < 0)
		info.start = 0;
	if (info.zero == 1 && info.precision == 0 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}

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

int print_hex(va_list arg, t_box info)
{
	uintmax_t nbr;
	char *number;

	if (ft_strequ(info.length, "hh"))
		nbr = (unsigned char)va_arg(arg, unsigned int);
	else if (ft_strequ(info.length, "h"))
		nbr = (unsigned short)va_arg(arg, unsigned int);
	else if (ft_strequ(info.length, "ll"))
		nbr = va_arg(arg, unsigned long long);
	else if (ft_strequ(info.length, "l"))
		nbr = va_arg(arg, unsigned long);
	else if (ft_strequ(info.length, "j"))
		nbr = va_arg(arg, uintmax_t);
	else if (ft_strequ(info.length, "z"))
		nbr = (size_t)va_arg(arg, size_t);
	else
		nbr = va_arg(arg, unsigned int);

	if (info.type == 'x')
		number = ft_itoa_base(nbr, 16, 0);
	else
		number = ft_itoa_base(nbr, 16, 1);

	// if (info.precision == -1 && nbr == 0)
	// 	number = ft_strdup("");
	info.sum_zeroes = info.precision - ft_strlen(number);
	if (info.sum_zeroes < 0)
		info.sum_zeroes = 0;
	info.start = info.width - info.sum_zeroes - ft_strlen(number);
	if (info.start < 0)
		info.start = 0;
	if (info.hash == 1 && nbr != 0)
	{
		if (info.type == 'x')
			info.prefix = "0x";
		else
			info.prefix = "0X";
		info.start -= 2;
	}
	if (info.zero == 1 && info.precision == 0 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}
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

int print_octal(va_list arg, t_box info)
{
	uintmax_t nbr;
	char *number;

	if (ft_strequ(info.length, "hh"))
		nbr = (unsigned char)va_arg(arg, unsigned int);
	else if (ft_strequ(info.length, "h"))
		nbr = (unsigned short)va_arg(arg, unsigned int);
	else if (ft_strequ(info.length, "ll"))
		nbr = va_arg(arg, unsigned long long);
	else if (ft_strequ(info.length, "l"))
		nbr = va_arg(arg, unsigned long);
	else if (ft_strequ(info.length, "j"))
		nbr = va_arg(arg, uintmax_t);
	else if (ft_strequ(info.length, "z"))
		nbr = (size_t)va_arg(arg, size_t);
	else
		nbr = va_arg(arg, unsigned int);

	number = ft_itoa_base(nbr, 8, 0);

	info.sum_zeroes = info.precision - ft_strlen(number);
	if (info.sum_zeroes < 0)
		info.sum_zeroes = 0;
	info.start = info.width - info.sum_zeroes - ft_strlen(number);
	if (info.start < 0)
		info.start = 0;
	if (info.hash == 1 && info.sum_zeroes == 0)
	{
		info.prefix = "0";
		info.start -= 1;
	}
	if (info.zero == 1 && info.precision == 0 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}

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

int print_char(va_list arg, t_box info)
{
	char c;
	char *string;

	c = va_arg(arg, int);
	info.start = info.width - 1;
	if (info.start < 0)
		info.start = 0;
	string = ft_strnew(2);
	string[0] = c;

	if (info.zero == 1 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}

	while (info.sum_zeroes-- > 0)
		string = ft_strjoin("0", string);
	if (info.minus)
		while (info.start-- > 0)
			string = ft_strjoin(string, " ");
	else
		while (info.start-- > 0)
			string = ft_strjoin(" ", string);

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
	return ( (c == 0) ? (ft_strlen(string) + 1) : ft_strlen(string));
}

int print_string(va_list arg, t_box info)
{
	char *temp;
	char *string;

	temp = va_arg(arg, char*);
	string = ft_strdup(temp);
	if (temp == 0)
		string = ft_strdup("(null)");
	
	// doesn't work with precision 0
	if (info.precision != 0)
		string = ft_strsub(string, 0, info.precision);
	info.start = info.width - ft_strlen(string);
	if (info.zero == 1 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}
	while (info.sum_zeroes-- > 0)
		string = ft_strjoin("0", string);
	if (info.minus)
		while (info.start-- > 0)
			string = ft_strjoin(string, " ");
	else
		while (info.start-- > 0)
			string = ft_strjoin(" ", string);
	ft_putstr(string);
	return (ft_strlen(string));
}

int print_percent(t_box info)
{
	char *string;

	string = ft_strnew(2);
	string[0] = '%';
	if ((info.start = info.width - 1) < 0)
		info.start = 0;
	if (info.zero == 1 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}
	while (info.sum_zeroes-- > 0)
		string = ft_strjoin("0", string);
	if (info.minus)
		while (info.start-- > 0)
			string = ft_strjoin(string, " ");
	else
		while (info.start-- > 0)
			string = ft_strjoin(" ", string);
	ft_putstr(string);
	return (ft_strlen(string));
}

int print(va_list arg, t_box info)
{
	int ret;

	ret = 0;
	if (info.type == 'd' || info.type == 'i')
	{
		ret = print_dec(arg, info);
	}
	else if (info.type == 'u')
	{
		ret = print_unsigned(arg, info);
	}
	else if (info.type == 'x' || info.type == 'X')
	{
		ret = print_hex(arg, info);
	}
	else if (info.type == 'o' || info.type == 'O')
	{
		ret = print_octal(arg, info);
	}
	else if (info.type == 'c')
	{
		ret = print_char(arg, info);
	}
	else if (info.type == 's')
	{
		ret = print_string(arg, info);
	}
	return (ret);
}

int ft_printf(const char *format, ...)
{
	va_list arg;
	t_box info;
	int i;
	int start;
	va_start(arg, format);
	int ret;

	ret = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			reset_box(&info);
			i++;
			while (is_flag(format[i]))
			{
				put_flag(&info, format[i]);
				i++;
			}
			while (ft_isdigit(format[i]))
			{
				start = i;
				while (ft_isdigit(format[i]))
					i++;
				info.width = ft_atoi(ft_strsub(format, start, i - start));
			}
			if (format[i] == '.')
			{
				i++;
				start = i;
				// if nbr = 0 and precision = 0 => output ""
				// if (format[i + 1] == '0' || !ft_isdigit(format[i + 1]))
				// {
				// 	info.precision = -1;
				// 	i++;
				// }
				while (ft_isdigit(format[i]))
					i++;
				info.precision = ft_atoi(ft_strsub(format, start, i - start));
			}
			if (is_length(format[i]))
			{
				start = i;
				while (is_length(format[i]))
					i++;
				info.length = ft_strsub(format, start, i - start);
			}
			if (is_correct_type(format[i]))
			{
				info.type = format[i];
				ret += print(arg, info);
			}
			if (format[i] == '%')
				ret += print_percent(info);
			// print_struct(info);
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

// void test_42(void)
// {
//    	    ft_printf("%d\n", 2147483648);                  //-> "-2147483648"
//    	       printf("%d\n", 2147483648);
//     	ft_printf("%d\n", -2147483648);                 //-> "-2147483648"
//     	   printf("%d\n", -2147483648);
//     	ft_printf("%d\n", -2147483649);                 //-> "2147483647"
//     	   printf("%d\n", -2147483649);
//     	ft_printf("% d\n", 42);                         //-> " 42"
//     	   printf("% d\n", 42);
//     	ft_printf("% d\n", -42);                        //-> "-42"
//     	   printf("% d\n", -42);
//     	ft_printf("%+d\n", 42);                         //-> "+42"
//     	   printf("%+d\n", 42);
//     	ft_printf("%+d\n", -42);                        //-> "-42"
//     	   printf("%+d\n", -42);
//     	ft_printf("%+d\n", 0);                          //-> "+0"
//     	   printf("%+d\n", 0);
//     	// ft_printf("%+d\n", 4242424242424242424242);     //-> "-1"
//     	   // printf("%+d\n", 4242424242424242424242);
//     	ft_printf("% +d\n", 42);                        //-> "+42"
//     	   printf("% +d\n", 42);
//     	ft_printf("% +d\n", -42);                       //-> "-42"
//     	   printf("% +d\n", -42);
//     	ft_printf("%+ d\n", 42);                        //-> "+42"
//     	   printf("%+ d\n", 42);
//     	ft_printf("%+ d\n", -42);                       //-> "-42"
//     	   printf("%+ d\n", -42);
//     	ft_printf("%  +d\n", 42);                       //-> "+42"
//     	   printf("%  +d\n", 42); 
//     	ft_printf("%  +d\n", -42);                      //-> "-42"
//     	   printf("%  +d\n", -42);
//     	ft_printf("%+  d\n", 42);                       //-> "+42"
//     	   printf("%+  d\n", 42);
//     	ft_printf("%+  d\n", -42);                      //-> "-42"
//     	   printf("%+  d\n", -42);
//     	ft_printf("% ++d\n", 42);                       //-> "+42"
//     	   printf("% ++d\n", 42);
//     	ft_printf("% ++d\n", -42);                      //-> "-42"
//     	   printf("% ++d\n", -42);
//     	ft_printf("%++ d\n", 42);                       //-> "+42"
//     	   printf("%++ d\n", 42);
//     	ft_printf("%++ d\n", -42);                      //-> "-42"
//     	   printf("%++ d\n", -42);
//     	ft_printf("%0d\n", -42);                        //-> "-42"
//     	   printf("%0d\n", -42);
//     	ft_printf("%00d\n", -42);                       //-> "-42"
//     	   printf("%00d\n", -42);
//     	ft_printf("%5d\n", 42);                         //-> "   42"
//     	   printf("%5d\n", 42);
//     	ft_printf("%05d\n", 42);                        //-> "00042"
//     	   printf("%05d\n", 42);
//     	ft_printf("%0+5d\n", 42);                       //-> "+0042"
//     	   printf("%0+5d\n", 42); 
//     	ft_printf("%5d\n", -42);                        //-> "  -42"
//     	   printf("%5d\n", -42); 
//     	ft_printf("%05d\n", -42);                       //-> "-0042"
//     	   printf("%05d\n", -42);
//     	ft_printf("%0+5d\n", -42);                      //-> "-0042"
//     	   printf("%0+5d\n", -42); 
//     	ft_printf("%-5d\n", 42);                        //-> "42   "
//     	   printf("%-5d\n", 42); 
//     	ft_printf("%-05d\n", 42);                       //-> "42   "
//     	   printf("%-05d\n", 42);
//     	ft_printf("%-5d\n", -42);                       //-> "-42  "
//     	   printf("%-5d\n", -42); 
//     	ft_printf("%-05d\n", -42);                      //-> "-42  "
//     	   printf("%-05d\n", -42);
// 	    ft_printf("%hd\n", 32767);                        //-> "32767"
// 	       printf("%hd\n", 32767);
//         // ft_printf("%hd\n", −32768);                       //-> "0"
//            // printf("%hd\n", −32768);
//         ft_printf("%hd\n", 32768);                        //-> "-32768"
//            printf("%hd\n", 32768);
//         // ft_printf("%hd\n", −32769);                       //-> "0"
//            // printf("%hd\n", −32769);
//         ft_printf("%hhd\n", 127);                         //-> "127"
//            printf("%hhd\n", 127);
//         ft_printf("%hhd\n", 128);                         //-> "-128"
//            printf("%hhd\n", 128);
//         ft_printf("%hhd\n", -128);                        //-> "-128"
//            printf("%hhd\n", -128);
//         ft_printf("%hhd\n", -129);                        //-> "127"
//            printf("%hhd\n", -129);
//         ft_printf("%ld\n", 2147483647);                   //-> "2147483647"
//            printf("%ld\n", 2147483647);
//         ft_printf("%ld\n", -2147483648);                  //-> "-2147483648"
//            printf("%ld\n", -2147483648);
//         ft_printf("%ld\n", 2147483648);                   //-> "2147483648"
//            printf("%ld\n", 2147483648);
//         ft_printf("%ld\n", -2147483649);                  //-> "-2147483649"
//            printf("%ld\n", -2147483649);
//         ft_printf("%lld\n", 9223372036854775807);         //-> "9223372036854775807"
//            printf("%lld\n", 9223372036854775807);
//         ft_printf("%lld\n", -9223372036854775808);        //-> "-9223372036854775808"
//            printf("%lld\n", -9223372036854775808);
//         ft_printf("%jd\n", 9223372036854775807);          //-> "9223372036854775807"
//            printf("%jd\n", 9223372036854775807);
//         ft_printf("%jd\n", -9223372036854775808);         //-> "-9223372036854775808"
//            printf("%jd\n", -9223372036854775808);
//         ft_printf("%zd\n", 4294967295);                   //-> "4294967295"
//            printf("%zd\n", 4294967295);
//         ft_printf("%zd\n", 4294967296);                   //-> "4294967296"
//            printf("%zd\n", 4294967296);
//         ft_printf("%zd\n", -0);                           //-> "0"
//            printf("%zd\n", -0);
//         ft_printf("%zd\n", -1);                           //-> "-1"
//            printf("%zd\n", -1);
//         ft_printf("%d\n", 1);                             //-> "1"
//            printf("%d\n", 1);
//         ft_printf("%d %d\n", 1, -2);                      //-> "1 -2"
//            printf("%d %d\n", 1, -2);
//         ft_printf("%d %d %d\n", 1, -2, 33);               //-> "1 -2 33"
//            printf("%d %d %d\n", 1, -2, 33);
//         ft_printf("%d %d %d %d\n", 1, -2, 33, 42);        //-> "1 -2 33 42"
//            printf("%d %d %d %d\n", 1, -2, 33, 42);
//         ft_printf("%d %d %d %d gg!\n", 1, -2, 33, 42, 0); //-> "1 -2 33 42 gg!"
//            printf("%d %d %d %d gg!\n", 1, -2, 33, 42, 0);
//         ft_printf("%4.15d\n", 42);                        //-> "000000000000042"
//            printf("%4.15d\n", 42);
//         ft_printf("%.2d\n", 4242);                        //-> "4242"
//            printf("%.2d\n", 4242); 
//         ft_printf("%.10d\n", 4242);                       //-> "0000004242"
//            printf("%.10d\n", 4242);
//         ft_printf("%10.5d\n", 4242);                      //-> "     04242"
//            printf("%10.5d\n", 4242);
//         ft_printf("%-10.5d\n", 4242);                     //-> "04242     "
//            printf("%-10.5d\n", 4242);
//         ft_printf("% 10.5d\n", 4242);                     //-> "     04242"
//            printf("% 10.5d\n", 4242);
//         ft_printf("%+10.5d\n", 4242);                     //-> "    +04242"
//            printf("%+10.5d\n", 4242);
//         ft_printf("%-+10.5d\n", 4242);                    //-> "+04242    "
//            printf("%-+10.5d\n", 4242); 
//         ft_printf("%03.2d\n", 0);                         //-> " 00"
//            printf("%03.2d\n", 0);
//         ft_printf("%03.2d\n", 1);                         //-> " 01"
//            printf("%03.2d\n", 1);
//         ft_printf("%03.2d\n", -1);                        //-> "-01"
//            printf("%03.2d\n", -1);
//         ft_printf("@moulitest: %.10d\n", -42);            //-> "@moulitest: -0000000042"
//            printf("@moulitest: %.10d\n", -42);
//         ft_printf("@moulitest: %.d %.0d\n", 42, 43);      //-> "@moulitest: 42 43"
//            printf("@moulitest: %.d %.0d\n", 42, 43);
//         ft_printf("@moulitest: %.d %.0d\n", 0, 0);        //-> "@moulitest:  "
//            printf("@moulitest: %.d %.0d\n", 0, 0);
//         ft_printf("@moulitest: %5.d %5.0d\n", 0, 0);      //-> "@moulitest:            "
//            printf("@moulitest: %5.d %5.0d\n", 0, 0);
// }

// void test_x_s_o(void)
// {
// 	ft_printf("");                                                               //-> ""
// 	   printf("");
// 	ft_printf("\n");                                                             //-> "$\n"
// 	   printf("\n");
// 	ft_printf("test\n");                                                           //-> "test\n"
// 	   printf("test\n");
// 	ft_printf("test\n");                                                         //-> "test$\n"
// 	   printf("test\n");
// 	ft_printf("1234\n");                                                           //-> "1234"\n
// 	   printf("1234\n");
// 	ft_printf("%%\n");                                                             //-> "%"
// 	   printf("%%\n");
// 	ft_printf("%5%\n");                                                            //-> "    %"
// 	   printf("%5%\n");
// 	ft_printf("%-5%\n");                                                           //-> "%    "
// 	   printf("%-5%\n");
// 	ft_printf("%.0%\n");                                                           //-> "%"
// 	   printf("%.0%\n");
// 	ft_printf("%%\n", "test");                                                     //-> "%"
// 	   printf("%%\n", "test");
// 	ft_printf("%   %\n", "test");                                                  //-> "%"
// 	   printf("%   %\n", "test");
// 	ft_printf("%x\n", 42);                                                         //-> "2a"
// 	   printf("%x\n", 42);
// 	ft_printf("%X\n", 42);                                                         //-> "2A"
// 	   printf("%X\n", 42);
// 	ft_printf("%x\n", 0);                                                          //-> "0"
// 	   printf("%x\n", 0);
// 	ft_printf("%X\n", 0);                                                          //-> "0"
// 	   printf("%X\n", 0);
// 	ft_printf("%x\n", -42);                                                        //-> "ffffffd6"
// 	   printf("%x\n", -42);
// 	ft_printf("%X\n", -42);                                                        //-> "FFFFFFD6"
// 	   printf("%X\n", -42);
// 	ft_printf("%x\n", 4294967296);                                                 //-> "0"
// 	   printf("%x\n", 4294967296);
// 	ft_printf("%X\n", 4294967296);                                                 //-> "0"
// 	   printf("%X\n", 4294967296);
// 	ft_printf("%10x\n", 42);                                                       //-> "        2a"
// 	   printf("%10x\n", 42);
// 	ft_printf("%-10x\n", 42);                                                      //-> "2a        "
// 	   printf("%-10x\n", 42);
// 	ft_printf("%lx\n", 4294967296);                                                //-> "100000000"
// 	   printf("%lx\n", 4294967296);
// 	ft_printf("%llX\n", 4294967296);                                               //-> "100000000"
// 	   printf("%llX\n", 4294967296);
// 	ft_printf("%hx\n", 4294967296);                                                //-> "0"
// 	   printf("%hx\n", 4294967296);
// 	ft_printf("%hhX\n", 4294967296);                                               //-> "0"
// 	   printf("%hhX\n", 4294967296);
// 	ft_printf("%jx\n", 4294967295);                                                //-> "ffffffff"
// 	   printf("%jx\n", 4294967295);
// 	ft_printf("%jx\n", 4294967296);                                                //-> "100000000"
// 	   printf("%jx\n", 4294967296);
// 	ft_printf("%jx\n", -4294967296);                                               //-> "ffffffff00000000"
// 	   printf("%jx\n", -4294967296);
// 	ft_printf("%jx\n", -4294967297);                                               //-> "fffffffeffffffff"
// 	   printf("%jx\n", -4294967297);
// 	ft_printf("%llx\n", 9223372036854775807);                                      //-> "7fffffffffffffff"
// 	   printf("%llx\n", 9223372036854775807);
// 	ft_printf("%llx\n", 9223372036854775808);                                      //-> "7fffffffffffffff"
// 	   printf("%llx\n", 9223372036854775808);
// 	ft_printf("%010x\n", 542);                                                     //-> "000000021e"
// 	   printf("%010x\n", 542);
// 	ft_printf("%-15x\n", 542);                                                     //-> "21e            "
// 	   printf("%-15x\n", 542);
// 	ft_printf("%2x\n", 542);                                                       //-> "21e"
// 	   printf("%2x\n", 542);
// 	ft_printf("%.2x\n", 5427);                                                     //-> "1533"
// 	   printf("%.2x\n", 5427);
// 	ft_printf("%5.2x\n", 5427);                                                    //-> " 1533"
// 	   printf("%5.2x\n", 5427);
// 	ft_printf("%#x\n", 42);                                                        //-> "0x2a"
// 	   printf("%#x\n", 42);
// 	ft_printf("%#llx\n", 9223372036854775807);                                     //-> "0x7fffffffffffffff"
// 	   printf("%#llx\n", 9223372036854775807); 
// 	ft_printf("%#x\n", 0);                                                         //-> "0"
// 	   printf("%#x\n", 0);
// 	ft_printf("%#x\n", 42);                                                        //-> "0x2a"
// 	   printf("%#x\n", 42);
// 	ft_printf("%#X\n", 42);                                                        //-> "0X2A"
// 	   printf("%#X\n", 42);
// 	ft_printf("%#8x\n", 42);                                                       //-> "    0x2a"
// 	   printf("%#8x\n", 42);
// 	ft_printf("%#08x\n", 42);                                                      //-> "0x00002a"
// 	   printf("%#08x\n", 42);
// 	ft_printf("%#-08x\n", 42);                                                     //-> "0x2a    "
// 	   printf("%#-08x\n", 42);
// 	ft_printf("@moulitest: %#.x %#.0x\n", 0, 0);                                   //-> "@moulitest:  "
// 	   printf("@moulitest: %#.x %#.0x\n", 0, 0);
// 	ft_printf("@moulitest: %.x %.0x\n", 0, 0);                                     //-> "@moulitest:  "
// 	   printf("@moulitest: %.x %.0x\n", 0, 0);
// 	ft_printf("@moulitest: %5.x %5.0x\n", 0, 0);                                   //-> "@moulitest:            "
// 	   printf("@moulitest: %5.x %5.0x\n", 0, 0);
	// ft_printf("%s\n", "abc");                                                      //-> "abc"
	//    printf("%s\n", "abc");
	// ft_printf("%s\n", "this is a string");                                         //-> "this is a string"
	//    printf("%s\n", "this is a string");
	// ft_printf("%s\n", "this is a string");                                        //-> "this is a string "
	//    printf("%s\n", "this is a string");
	// ft_printf("%s  \n", "this is a string");                                       //-> "this is a string  "
	//    printf("%s  \n", "this is a string");
	// ft_printf("this is a %s\n", "string");                                         //-> "this is a string"
	//    printf("this is a %s\n", "string");
	// ft_printf("%s is a string\n", "this");                                         //-> "this is a string"
	//    printf("%s is a string\n", "this");
	// ft_printf("Line Feed %s\n", "\n");                                             //-> "Line Feed $\n"
	//    printf("Line Feed %s\n", "\n");
	// ft_printf("%10s is a string\n", "this");                                       //-> "      this is a string"
	//    printf("%10s is a string\n", "this");
	// ft_printf("%.2s is a string\n", "this");                                       //-> "th is a string"
	//    printf("%.2s is a string\n", "this");
	// ft_printf("%5.2s is a string\n", "this");                                      //-> "   th is a string"
	//    printf("%5.2s is a string\n", "this");
	// ft_printf("%10s is a string\n", "");                                           //-> "           is a string"
	//    printf("%10s is a string\n", "");
	// ft_printf("%.2s is a string\n", "");                                           //-> " is a string"
	//    printf("%.2s is a string\n", "");
	// ft_printf("%5.2s is a string\n", "");                                          //-> "      is a string"
	//    printf("%5.2s is a string\n", "");
	// ft_printf("%-10s is a string\n", "this");                                      //-> "this       is a string"
	//    printf("%-10s is a string\n", "this");
	// ft_printf("%-.2s is a string\n", "this");                                      //-> "th is a string"
	//    printf("%-.2s is a string\n", "this");
	// ft_printf("%-5.2s is a string\n", "this");                                     //-> "th    is a string"
	//    printf("%-5.2s is a string\n", "this");
	// ft_printf("%-10s is a string\n", "");                                          //-> "           is a string"
	//    printf("%-10s is a string\n", "");
	// ft_printf("%-.2s is a string\n", "");                                          //-> " is a string"
	//    printf("%-.2s is a string\n", "");
	// ft_printf("%-5.2s is a string\n", "");                                         //-> "      is a string"
	//    printf("%-5.2s is a string\n", "");
	// ft_printf("%s %s\n", "this", "is");                                            //-> "this is"
	//    printf("%s %s\n", "this", "is");
	// ft_printf("%s %s %s\n", "this", "is", "a");                                    //-> "this is a"
	//    printf("%s %s %s\n", "this", "is", "a");
	// ft_printf("%s %s %s %s\n", "this", "is", "a", "multi");                        //-> "this is a multi"
	//    printf("%s %s %s %s\n", "this", "is", "a", "multi"); 
	// ft_printf("%s %s %s %s string. gg!\n", "this", "is", "a", "multi", "string");  //-> "this is a multi string. gg!"
	//    printf("%s %s %s %s string. gg!\n", "this", "is", "a", "multi", "string");
	// ft_printf("%s%s%s%s%s\n", "this", "is", "a", "multi", "string");               //-> "thisisamultistring"
	//    printf("%s%s%s%s%s\n", "this", "is", "a", "multi", "string");
	// ft_printf("@moulitest: %s\n", NULL);                                           //-> "@moulitest: (null)"
	//    printf("@moulitest: %s\n", NULL);
	// ft_printf("%.2c\n", NULL);                                                     //-> "^@"
	//    printf("%.2c\n", NULL);
// 	ft_printf("%c\n", 42);                                                         //-> "*"
// 	   printf("%c\n", 42);
// 	ft_printf("%5c\n", 42);                                                        //-> "    *"
// 	   printf("%5c\n", 42);
// 	ft_printf("%-5c\n", 42);                                                       //-> "*    "
// 	   printf("%-5c\n", 42);
// 	ft_printf("@moulitest: %c\n", 0);                                              //-> "@moulitest: ^@"
// 	   printf("@moulitest: %c\n", 0);
// 	ft_printf("%2c\n", 0);                                                         //-> " ^@"
// 	   printf("%2c\n", 0);
// 	ft_printf("null %c and text\n", 0);                                            //-> "null ^@ and text"
// 	   printf("null %c and text\n", 0); 
// 	ft_printf("% c\n", 0);                                                         //-> "^@"
// 	   printf("% c\n", 0);
// 	ft_printf("%o\n", 40);                                                         //-> "50"
// 	   printf("%o\n", 40);
// 	ft_printf("%5o\n", 41);                                                        //-> "   51"
// 	   printf("%5o\n", 41);
// 	ft_printf("%05o\n", 42);                                                       //-> "00052"
// 	   printf("%05o\n", 42);
// 	ft_printf("%-5o\n", 2500);                                                     //-> "4704 "
// 	   printf("%-5o\n", 2500);
// 	ft_printf("%#6o\n", 2500);                                                     //-> " 04704"
// 	   printf("%#6o\n", 2500);
// 	ft_printf("%-#6o\n", 2500);                                                    //-> "04704 "
// 	   printf("%-#6o\n", 2500);
// 	ft_printf("%-05o\n", 2500);                                                    //-> "4704 "
// 	   printf("%-05o\n", 2500);
// 	ft_printf("%-5.10o\n", 2500);                                                  //-> "0000004704"
// 	   printf("%-5.10o\n", 2500);
// 	ft_printf("%-10.5o\n", 2500);                                                  //-> "04704     "
// 	   printf("%-10.5o\n", 2500);
// 	ft_printf("@moulitest: %o\n", 0);                                              //-> "@moulitest: 0"
// 	   printf("@moulitest: %o\n", 0);
// 	ft_printf("@moulitest: %.o %.0o\n", 0, 0);                                     //-> "@moulitest:  "
// 	   printf("@moulitest: %.o %.0o\n", 0, 0);
// 	ft_printf("@moulitest: %5.o %5.0o\n", 0, 0);                                   //-> "@moulitest:            "
// 	   printf("@moulitest: %5.o %5.0o\n", 0, 0);
// 	ft_printf("@moulitest: %#.o %#.0o\n", 0, 0);                                   //-> "@moulitest: 0 0"
// 	   printf("@moulitest: %#.o %#.0o\n", 0, 0);
// 	ft_printf("@moulitest: %.10o\n", 42);                                          //-> "@moulitest: 0000000052"
// 	   printf("@moulitest: %.10o\n", 42);
// }

// void failed_tests()
// {
//   // ft_printf("@moulitest: %#.x %#.0x\n", 0, 0);    //-> "@moulitest:  "
//   //    printf("@moulitest: %#.x %#.0x\n", 0, 0);
//   // ft_printf("@moulitest: %.x %.0x\n", 0, 0);      //-> "@moulitest:  "
//   //    printf("@moulitest: %.x %.0x\n", 0, 0);
//   // ft_printf("@moulitest: %5.x %5.0x\n", 0, 0);    //-> "@moulitest:            "
//   //    printf("@moulitest: %5.x %5.0x\n", 0, 0);

// 	ft_printf("%.2c", NULL);                      //-> "^@"
// 	   printf("%.2c", NULL);
// }

int main()
{
	char *str = "Hello";
	int nbr = 842;

	int nbr2 = -42;

	int ret_org;
	int ret_my;
	/*========= MY =========*/
	ret_my = ft_printf("% c\n", 0);

	// ========== ORIGINAL ==========
	ret_org = printf("%.2c\n", NULL);


	printf("ORG %d | MY %d\n", ret_org, ret_my);
	/*========= MY =========*/
	// ft_printf("%+10.5u\n", nbr2);

	// ========== ORIGINAL ==========
	// printf("%+10.5u\n", nbr2);

	// test_42();
	// test_x_s_o();
	// failed_tests();
	return (0);
}