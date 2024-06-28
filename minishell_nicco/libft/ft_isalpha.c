/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isaplha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:40:40 by nspinell          #+#    #+#             */
/*   Updated: 2023/12/18 11:40:45 by nspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	int	n;

	n = 1;
	if ((c > 'z' || c < 'a') && (c > 'Z' || c < 'A'))
	{
		n = 0;
	}
	return (n);
}