/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:05:44 by vbrovenk          #+#    #+#             */
/*   Updated: 2018/04/30 16:05:48 by vbrovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF

#include "libft/libft.h"
#include <inttypes.h>  // for linux

typedef	struct s_box
{
	int			minus;
	int			plus;
	int			space;
	int			zero;
	int			hash;
	int			width;
	int			precision;
	char		*length;
	char		type;
	int start;
	int sum_zeroes;
	char *prefix;
}				t_box;

int	my_countdigits(intmax_t n);
char			*my_itoa(intmax_t number);

#endif
