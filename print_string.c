/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:09:24 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/06/26 15:09:26 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*output(t_box info, char *string)
{
	while (info.sum_zeroes-- > 0)
		string = ft_strjoin("0", string);
	if (info.minus)
		while (info.start-- > 0)
			string = ft_strjoin(string, " ");
	else
		while (info.start-- > 0)
			string = ft_strjoin(" ", string);
	ft_putstr(string);
	return (string);
}

int		print_string(va_list arg, t_box info)
{
	char *temp;
	char *string;

	if (ft_strequ(info.length, "l"))
		return (print_uni_string(arg, info));
	temp = va_arg(arg, char*);
	string = ft_strdup(temp);
	if (temp == 0)
		string = ft_strdup("(null)");
	// maybe work with precision 0
	if (info.precision == -1)
		string = ft_strdup("");
	if (info.precision > 0)
	{
		temp = ft_strsub(string, 0, info.precision);
		free(string);
		string = temp;
	}
	info.start = info.width - ft_strlen(string);
	if (info.zero == 1 && info.minus == 0)
	{
		info.sum_zeroes += info.start;
		info.start = 0;
	}
	string = output(info, string);
	return (ft_strlen(string));
}
