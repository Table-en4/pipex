/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_px.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:04:56 by molapoug          #+#    #+#             */
/*   Updated: 2025/05/17 17:38:52 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_x_num(unsigned int num, char *base_chars)
{
	int		i;
	int		count;
	char	buf[16];

	count = 0;
	i = 16;
	if (!base_chars)
		return (count);
	if (num == 0)
		return (ft_putcharp('0'));
	while (num > 0)
	{
		buf[--i] = base_chars[num % 16];
		num /= 16;
	}
	while (i < 16)
		count += ft_putcharp(buf[i++]);
	return (count);
}

int	ft_base_hex_low(unsigned int nbr)
{
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = ft_print_x_num(nbr, base);
	return (count);
}

int	ft_base_hex_upp(unsigned int nbr)
{
	char	*base;
	int		count;

	base = "0123456789ABCDEF";
	count = ft_print_x_num(nbr, base);
	return (count);
}
