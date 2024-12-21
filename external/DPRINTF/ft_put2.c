/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:30:45 by sben-tay          #+#    #+#             */
/*   Updated: 2024/04/17 00:03:43 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(\
		unsigned long long nbr, int fd, int *compteur, char c)
{
	char	*base;

	base = "0123456789abcdef";
	if (c == 'p')
	{
		if (nbr != 0)
			ft_putstr("0x", fd, compteur);
		if (nbr == 0)
		{
			ft_putstr("(nil)", fd, compteur);
			return ;
		}
		c++;
	}
	if (c != 'p')
	{
		if (nbr >= 16)
			ft_putnbr_base(nbr / 16, fd, compteur, c);
		ft_putchar(base[nbr % 16], fd, compteur);
	}
}
