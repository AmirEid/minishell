/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaic <rpaic@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:58:55 by rpaic             #+#    #+#             */
/*   Updated: 2024/08/07 18:02:39 by rpaic            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_iswhite(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	numeric_arg_required(char *str, t_data *data)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_status = 2;
	free_all(data);
	exit(exit_status);
}

long long int	ft_atoll(char *str, int i, t_data *data)
{
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	if (ft_strchr(str, '-'))
		sign = -1;
	while (ft_isdigit(str[i]))
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			numeric_arg_required(str, data);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	check_exit_argument(char *str, int *begin, t_data *data)
{
	int	i;
	int	end;

	i = 0;
	while (ft_iswhite(str[i]))
		i++;
	if ((str[i] == '-' && ft_isdigit(str[i + 1])) || (str[i] == '+'
			&& ft_isdigit(str[i + 1])))
		i++;
	*begin = i;
	while (ft_isdigit(str[i]))
		i++;
	end = i;
	if (end - (*begin) > 19)
		numeric_arg_required(str, data);
	while (str[i])
	{
		if (!ft_iswhite(str[i]))
			numeric_arg_required(str, data);
		i++;
	}
}