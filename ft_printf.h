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

typedef	struct s_box
{
	int			minus;
	int			plus;
	int			space;
	int			zero;
	int			width;
	int			hash;
	int			precision;
	char		type;
}				t_box;

#endif
