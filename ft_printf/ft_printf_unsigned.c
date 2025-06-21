/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:28:37 by molapoug          #+#    #+#             */
/*   Updated: 2025/05/12 17:07:28 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	len_num(unsigned int nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

char	*my_itoa(unsigned int src)
{
	int		len;
	char	*dst;

	len = len_num(src);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	while (src != 0)
	{
		dst[len - 1] = src % 10 + 48;
		src = src / 10;
		len--;
	}
	return (dst);
}

int	convert_to_unsigned(unsigned int nb)
{
	unsigned int	len;
	char			*num;

	len = 0;
	if (nb == 0)
		len += write(1, "0", 1);
	else
	{
		num = my_itoa(nb);
		if (!num)
			return (-1);
		len += ft_putstrp(num);
		free(num);
	}
	return (len);
}
