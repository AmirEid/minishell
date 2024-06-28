/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                          :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: nspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:32:27 by nspinell          #+#    #+#             */
/*   Updated: 2023/12/18 12:32:30 by nspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	int	n;

	n = c;
	if ((c <= 'z' && c >= 'a'))
	{
		n = c - 32;
	}
	return (n);
}