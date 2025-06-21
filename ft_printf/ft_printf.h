/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:09:10 by molapoug          #+#    #+#             */
/*   Updated: 2025/06/21 14:27:38 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>

/* ---------------------- */
/* | functions with int | */
/* ---------------------- */
int	ft_putnbrp(int nbr);
int	ft_putstrp(char *str);
int	ft_putcharp(char c);
int	ft_putnbr_base(unsigned long nbr, char *base);
int	ft_base16(char *str);
int	ft_putnbrpi(long nb);
int	convert_to_unsigned(unsigned int nb);
int	ft_base_hex_low(unsigned int nbr);
int	ft_base_hex_upp(unsigned int nbr);
int	ft_printf(const char *format, ...);

#endif
