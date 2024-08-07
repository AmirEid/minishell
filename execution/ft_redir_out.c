/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:53:42 by aeid              #+#    #+#             */
/*   Updated: 2024/08/09 00:45:22 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

void	ft_redir_out(t_list *file, int *redi_num, t_data *data)
{
	t_tkn_data	*tokendata;
	int			p_errno;
	int			fd;

	tokendata = (t_tkn_data *)file->content;
	fd = open (tokendata->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		p_errno = errno;
		open_files_errors_manager(fd, tokendata->token, p_errno);
		data->exit_code = -1;
		return ;
	}
	if ((*redi_num) - 1 == 0)
	{
		dup2(fd, 1);
		if (fd == -1)
		{
			p_errno = errno;
			ft_dup2_error_manager(fd, p_errno);
			data->exit_code = -1;
			close(fd);
			return ;
		}	
	}
	(*redi_num)--;
	close(fd);
}
