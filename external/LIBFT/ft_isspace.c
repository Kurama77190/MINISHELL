/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:09:28 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/12 22:11:51 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\r'
		|| c == '\v' || c == '\f');
}