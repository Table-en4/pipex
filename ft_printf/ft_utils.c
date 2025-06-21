/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:09:10 by molapoug          #+#    #+#             */
/*   Updated: 2025/05/14 09:54:03 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrp(int nbr)
{
	unsigned int	i;
	long			nb;

	nb = nbr;
	i = 0;
	if (nb < 0)
	{
		i += ft_putcharp('-');
		nb = -nb;
	}
	if (nb >= 10)
		i += ft_putnbrp(nb / 10);
	i += ft_putcharp(nb % 10 + '0');
	return (i);
}

int	ft_putnbrpi(long nb)
{
	unsigned int	i;

	i = 0;
	if (nb < 0)
	{
		i += ft_putcharp('-');
		nb = -nb;
	}
	if (nb >= 10)
		i += ft_putnbrpi(nb / 10);
	i += ft_putcharp(nb % 10 + '0');
	return (i);
}

int	ft_putnbr_base(unsigned long nbr, char *base)
{
	char	buf[16];
	int		i;
	int		count;

	i = 15;
	count = 0;
	if (!base)
		return (count);
	while (nbr > 0 || i == 15)
	{
		buf[i] = base[nbr % 16];
		nbr /= 16;
		i--;
	}
	count += write(1, "0x", 2);
	while (++i < 16)
		count += ft_putcharp(buf[i]);
	return (count);
}

int	ft_base16(char *str)
{
	int	count;

	if (!str)
		return (write(1, "(nil)\n", 5));
	count = ft_putnbr_base((unsigned long)str, "0123456789abcdef");
	return (count);
}
