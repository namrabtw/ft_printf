/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikoyan <anikoyan@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:55:00 by anikoyan          #+#    #+#             */
/*   Updated: 2024/03/20 19:09:18 by anikoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_str_toupper(char **str, char c)
{
	char	*tmp;

	tmp = *str;
	if (c == 'X')
	{
		while (*tmp)
		{
			*tmp = ft_toupper(*tmp);
			tmp++;
		}
	}
}

static void	ft_add_sign_to_string(char **number, int *len)
{
	char	*new_number;
	int		new_len;

	new_len = *len + 2;
	new_number = malloc(sizeof(char) * (new_len + 1));
	ft_strlcpy(new_number, "0x", (sizeof(char) * (new_len + 1)));
	ft_strlcat(new_number, *number, (sizeof(char) * (new_len + 1)));
	free(*number);
	*number = new_number;
	*len = new_len;
}

static int	ft_process_flags(char **hex, unsigned int *u_nbr,
	int *padding_width, t_flags *flags)
{
	int	result;
	int	len;

	result = 0;
	len = ft_strlen(*hex);
	if (!(*u_nbr) && !flags->precision)
	{
		free(*hex);
		*hex = NULL;
		if (flags->width)
			(*padding_width)++;
	}
	if (flags->precision != -1 && flags->zero)
		ft_printf_putchar(3, ' ', &result, padding_width);
	flags->precision -= len;
	ft_printf_putchar(3, '0', &result, &flags->precision);
	if (flags->zero)
		ft_printf_putchar(3, '0', &result, padding_width);
	else if (flags->space)
		ft_printf_putchar(2, '0', &result);
	else if (flags->plus)
		ft_printf_putchar(2, '+', &result);
	else if (flags->hash && *u_nbr)
		ft_add_sign_to_string(hex, &len);
	return (result);
}

int	ft_printf_hex(unsigned int u_nbr, t_flags flags, char c)
{
	char	*hex;
	int		result;
	int		padding_width;

	result = 0;
	hex = ft_uitoa_base(u_nbr, 16);
	if (!hex)
		return (0);
	ft_strrev(hex);
	padding_width = ft_calculate_padding(ft_strlen(hex), &flags);
	result += ft_process_flags(&hex, &u_nbr, &padding_width, &flags);
	if (!flags.minus)
		ft_printf_putchar(3, ' ', &result, &padding_width);
	if (hex)
	{
		ft_str_toupper(&hex, c);
		ft_printf("%s", hex);
		result += ft_strlen(hex);
		free(hex);
	}
	if (flags.minus == 1)
		ft_printf_putchar(3, ' ', &result, &padding_width);
	return (result);
}
