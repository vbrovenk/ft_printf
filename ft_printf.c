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

	info.sum_zeroes = info.precision - ft_strlen(number);
	if (info.sum_zeroes < 0)
		info.sum_zeroes = 0;
	info.start = info.width - info.sum_zeroes - ft_strlen(number);
	if (info.start < 0)
		info.start = 0;
	if (info.hash == 1)
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
}

int print_char(va_list arg, t_box info)
{
	char c;

	c = va_arg(arg, int);
	info.start = info.width - 1;
	if (info.start < 0)
		info.start = 0;
	
	if (info.minus == 0)
	{
		while (info.start-- > 0)
			write(1, " ", 1);
		write(1, &c, 1);
	}
	else
	{
		write(1, &c, 1);
		while (info.start-- > 0)
			write(1, " ", 1);
	}
}

int print_string(va_list arg, t_box info)
{
	char *temp;
	char *string;

	temp = va_arg(arg, char*);
	string = ft_strdup(temp);
	if (temp == 0)
		string = ft_strdup("(null)");
	
	info.start = info.width - ft_strlen(string);
	if (info.minus)
		while (info.start-- > 0)
			string = ft_strjoin(string, " ");
	else
		while (info.start-- > 0)
			string = ft_strjoin(" ", string);
	ft_putstr(string);

}

int print(va_list arg, t_box info)
{
	if (info.type == 'd' || info.type == 'i')
	{
		print_dec(arg, info);
	}
	else if (info.type == 'u')
	{
		print_unsigned(arg, info);
	}
	else if (info.type == 'x' || info.type == 'X')
	{
		print_hex(arg, info);
	}
	else if (info.type == 'o' || info.type == 'O')
	{
		print_octal(arg, info);
	}
	else if (info.type == 'c')
	{
		print_char(arg, info);
	}
	else if (info.type == 's')
	{
		print_string(arg, info);
	}
	return (1);
}

int ft_printf(const char *format, ...)
{
	va_list arg;
	t_box info;
	int i;
	int start;
	va_start(arg, format);
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
				print(arg, info);
			}
			// print_struct(info);
		}
		else
			write(1, &format[i], 1);
		i++;
	}
	return (1);
}

void test_42(void)
{
   	    ft_printf("%d\n", 2147483648);                  //-> "-2147483648"
   	       printf("%d\n", 2147483648);
    	ft_printf("%d\n", -2147483648);                 //-> "-2147483648"
    	   printf("%d\n", -2147483648);
    	ft_printf("%d\n", -2147483649);                 //-> "2147483647"
    	   printf("%d\n", -2147483649);
    	ft_printf("% d\n", 42);                         //-> " 42"
    	   printf("% d\n", 42);
    	ft_printf("% d\n", -42);                        //-> "-42"
    	   printf("% d\n", -42);
    	ft_printf("%+d\n", 42);                         //-> "+42"
    	   printf("%+d\n", 42);
    	ft_printf("%+d\n", -42);                        //-> "-42"
    	   printf("%+d\n", -42);
    	ft_printf("%+d\n", 0);                          //-> "+0"
    	   printf("%+d\n", 0);
    	// ft_printf("%+d\n", 4242424242424242424242);     //-> "-1"
    	   // printf("%+d\n", 4242424242424242424242);
    	ft_printf("% +d\n", 42);                        //-> "+42"
    	   printf("% +d\n", 42);
    	ft_printf("% +d\n", -42);                       //-> "-42"
    	   printf("% +d\n", -42);
    	ft_printf("%+ d\n", 42);                        //-> "+42"
    	   printf("%+ d\n", 42);
    	ft_printf("%+ d\n", -42);                       //-> "-42"
    	   printf("%+ d\n", -42);
    	ft_printf("%  +d\n", 42);                       //-> "+42"
    	   printf("%  +d\n", 42); 
    	ft_printf("%  +d\n", -42);                      //-> "-42"
    	   printf("%  +d\n", -42);
    	ft_printf("%+  d\n", 42);                       //-> "+42"
    	   printf("%+  d\n", 42);
    	ft_printf("%+  d\n", -42);                      //-> "-42"
    	   printf("%+  d\n", -42);
    	ft_printf("% ++d\n", 42);                       //-> "+42"
    	   printf("% ++d\n", 42);
    	ft_printf("% ++d\n", -42);                      //-> "-42"
    	   printf("% ++d\n", -42);
    	ft_printf("%++ d\n", 42);                       //-> "+42"
    	   printf("%++ d\n", 42);
    	ft_printf("%++ d\n", -42);                      //-> "-42"
    	   printf("%++ d\n", -42);
    	ft_printf("%0d\n", -42);                        //-> "-42"
    	   printf("%0d\n", -42);
    	ft_printf("%00d\n", -42);                       //-> "-42"
    	   printf("%00d\n", -42);
    	ft_printf("%5d\n", 42);                         //-> "   42"
    	   printf("%5d\n", 42);
    	ft_printf("%05d\n", 42);                        //-> "00042"
    	   printf("%05d\n", 42);
    	ft_printf("%0+5d\n", 42);                       //-> "+0042"
    	   printf("%0+5d\n", 42); 
    	ft_printf("%5d\n", -42);                        //-> "  -42"
    	   printf("%5d\n", -42); 
    	ft_printf("%05d\n", -42);                       //-> "-0042"
    	   printf("%05d\n", -42);
    	ft_printf("%0+5d\n", -42);                      //-> "-0042"
    	   printf("%0+5d\n", -42); 
    	ft_printf("%-5d\n", 42);                        //-> "42   "
    	   printf("%-5d\n", 42); 
    	ft_printf("%-05d\n", 42);                       //-> "42   "
    	   printf("%-05d\n", 42);
    	ft_printf("%-5d\n", -42);                       //-> "-42  "
    	   printf("%-5d\n", -42); 
    	ft_printf("%-05d\n", -42);                      //-> "-42  "
    	   printf("%-05d\n", -42);
	    ft_printf("%hd\n", 32767);                        //-> "32767"
	       printf("%hd\n", 32767);
        // ft_printf("%hd\n", −32768);                       //-> "0"
           // printf("%hd\n", −32768);
        ft_printf("%hd\n", 32768);                        //-> "-32768"
           printf("%hd\n", 32768);
        // ft_printf("%hd\n", −32769);                       //-> "0"
           // printf("%hd\n", −32769);
        ft_printf("%hhd\n", 127);                         //-> "127"
           printf("%hhd\n", 127);
        ft_printf("%hhd\n", 128);                         //-> "-128"
           printf("%hhd\n", 128);
        ft_printf("%hhd\n", -128);                        //-> "-128"
           printf("%hhd\n", -128);
        ft_printf("%hhd\n", -129);                        //-> "127"
           printf("%hhd\n", -129);
        ft_printf("%ld\n", 2147483647);                   //-> "2147483647"
           printf("%ld\n", 2147483647);
        ft_printf("%ld\n", -2147483648);                  //-> "-2147483648"
           printf("%ld\n", -2147483648);
        ft_printf("%ld\n", 2147483648);                   //-> "2147483648"
           printf("%ld\n", 2147483648);
        ft_printf("%ld\n", -2147483649);                  //-> "-2147483649"
           printf("%ld\n", -2147483649);
        ft_printf("%lld\n", 9223372036854775807);         //-> "9223372036854775807"
           printf("%lld\n", 9223372036854775807);
        ft_printf("%lld\n", -9223372036854775808);        //-> "-9223372036854775808"
           printf("%lld\n", -9223372036854775808);
        ft_printf("%jd\n", 9223372036854775807);          //-> "9223372036854775807"
           printf("%jd\n", 9223372036854775807);
        ft_printf("%jd\n", -9223372036854775808);         //-> "-9223372036854775808"
           printf("%jd\n", -9223372036854775808);
        ft_printf("%zd\n", 4294967295);                   //-> "4294967295"
           printf("%zd\n", 4294967295);
        ft_printf("%zd\n", 4294967296);                   //-> "4294967296"
           printf("%zd\n", 4294967296);
        ft_printf("%zd\n", -0);                           //-> "0"
           printf("%zd\n", -0);
        ft_printf("%zd\n", -1);                           //-> "-1"
           printf("%zd\n", -1);
        ft_printf("%d\n", 1);                             //-> "1"
           printf("%d\n", 1);
        ft_printf("%d %d\n", 1, -2);                      //-> "1 -2"
           printf("%d %d\n", 1, -2);
        ft_printf("%d %d %d\n", 1, -2, 33);               //-> "1 -2 33"
           printf("%d %d %d\n", 1, -2, 33);
        ft_printf("%d %d %d %d\n", 1, -2, 33, 42);        //-> "1 -2 33 42"
           printf("%d %d %d %d\n", 1, -2, 33, 42);
        ft_printf("%d %d %d %d gg!\n", 1, -2, 33, 42, 0); //-> "1 -2 33 42 gg!"
           printf("%d %d %d %d gg!\n", 1, -2, 33, 42, 0);
        ft_printf("%4.15d\n", 42);                        //-> "000000000000042"
           printf("%4.15d\n", 42);
        ft_printf("%.2d\n", 4242);                        //-> "4242"
           printf("%.2d\n", 4242); 
        ft_printf("%.10d\n", 4242);                       //-> "0000004242"
           printf("%.10d\n", 4242);
        ft_printf("%10.5d\n", 4242);                      //-> "     04242"
           printf("%10.5d\n", 4242);
        ft_printf("%-10.5d\n", 4242);                     //-> "04242     "
           printf("%-10.5d\n", 4242);
        ft_printf("% 10.5d\n", 4242);                     //-> "     04242"
           printf("% 10.5d\n", 4242);
        ft_printf("%+10.5d\n", 4242);                     //-> "    +04242"
           printf("%+10.5d\n", 4242);
        ft_printf("%-+10.5d\n", 4242);                    //-> "+04242    "
           printf("%-+10.5d\n", 4242); 
        ft_printf("%03.2d\n", 0);                         //-> " 00"
           printf("%03.2d\n", 0);
        ft_printf("%03.2d\n", 1);                         //-> " 01"
           printf("%03.2d\n", 1);
        ft_printf("%03.2d\n", -1);                        //-> "-01"
           printf("%03.2d\n", -1);
        ft_printf("@moulitest: %.10d\n", -42);            //-> "@moulitest: -0000000042"
           printf("@moulitest: %.10d\n", -42);
        ft_printf("@moulitest: %.d %.0d\n", 42, 43);      //-> "@moulitest: 42 43"
           printf("@moulitest: %.d %.0d\n", 42, 43);
        ft_printf("@moulitest: %.d %.0d\n", 0, 0);        //-> "@moulitest:  "
           printf("@moulitest: %.d %.0d\n", 0, 0);
        ft_printf("@moulitest: %5.d %5.0d\n", 0, 0);      //-> "@moulitest:            "
           printf("@moulitest: %5.d %5.0d\n", 0, 0);
}

int main()
{
	char *str = "Hello";
	int nbr = 842;

	int nbr2 = -42;

	/*========= MY =========*/
	ft_printf("%10s\n", str);

	// ========== ORIGINAL ==========
	printf("%10s\n", str);


	/*========= MY =========*/
	// ft_printf("%+10.5u\n", nbr2);

	// ========== ORIGINAL ==========
	// printf("%+10.5u\n", nbr2);

	// test_42();
	return (0);
}