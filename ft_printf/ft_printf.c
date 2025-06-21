/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:56:01 by molapoug          #+#    #+#             */
/*   Updated: 2025/05/22 19:30:01 by molapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_output(char specifier, va_list args)
{
	if (specifier == 's')
		return (ft_putstrp(va_arg(args, char *)));
	else if (specifier == 'c')
		return (ft_putcharp(va_arg(args, int)));
	else if (specifier == 'd')
		return (ft_putnbrp(va_arg(args, int)));
	else if (specifier == 'i')
		return (ft_putnbrpi(va_arg(args, int)));
	else if (specifier == 'p')
		return (ft_base16(va_arg(args, char *)));
	else if (specifier == 'u')
		return (convert_to_unsigned(va_arg(args, int)));
	else if (specifier == 'x')
		return (ft_base_hex_low(va_arg(args, int)));
	else if (specifier == 'X')
		return (ft_base_hex_upp(va_arg(args, int)));
	else
		return (ft_putcharp('%'));
}

int	ft_parse_printf(const char *str, va_list args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			count += ft_handle_output(str[i], args);
		}
		else
		{
			count += ft_putcharp(str[i]);
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	if (!str)
		return (-1);
	va_start(args, str);
	count = ft_parse_printf(str, args);
	va_end(args);
	return (count);
}
/*
#include <stdio.h>
int main(){
	printf("%d", printf("%s\n", "test"));
}*/
/*
#include <stdio.h>

int main() {
    int a = 42;

    printf("Vrai printf : %c\n", 'A');
    ft_printf("ft_printf   : %c\n", 'A');

    printf("Vrai printf : %c\n", 'Z');
    ft_printf("ft_printf   : %c\n", 'Z');

    printf("Vrai printf : %c\n", '\n');
    ft_printf("ft_printf   : %c\n", '\n');

    printf("Vrai printf : %s\n", "Hello");
    ft_printf("ft_printf   : %s\n", "Hello");

    printf("Vrai printf : %s\n", "42 Paris");
    ft_printf("ft_printf   : %s\n", "42 Paris");

    printf("Vrai printf : %s\n", "");
    ft_printf("ft_printf   : %s\n", "");

    printf("Vrai printf : %d\n", 42);
    ft_printf("ft_printf   : %d\n", 42);

    printf("Vrai printf : %d\n", -42);
    ft_printf("ft_printf   : %d\n", -42);

    printf("Vrai printf : %i\n", 0);
    ft_printf("ft_printf   : %i\n", 0);

    printf("Vrai printf : %u\n", 42);
    ft_printf("ft_printf   : %u\n", 42);

    printf("Vrai printf : %u\n", 429496729);
    ft_printf("ft_printf   : %u\n", 429496729);

    printf("Vrai printf : %u\n", 42);
    ft_printf("ft_printf   : %u\n", 42);

    printf("Vrai printf : %x\n", 255);
    ft_printf("ft_printf   : %x\n", 255);

    printf("Vrai printf : %x\n", 0);
    ft_printf("ft_printf   : %x\n", 0);

    printf("Vrai printf : %X\n", 4096);
    ft_printf("ft_printf   : %X\n", 4096);

    printf("Vrai printf : %p\n", &a);
    ft_printf("ft_printf   : %p\n", &a);

    printf("Vrai printf : %p\n", NULL);
    ft_printf("ft_printf   : %p\n", NULL);

    printf("Vrai printf : %p\n", &ft_printf);
    ft_printf("ft_printf   : %p\n", &ft_printf);
}

#include <stdio.h>
int	main()
{
	char	*str = NULL;
	printf("%s\n", str);
	ft_printf("%s\n", str);
}*/
