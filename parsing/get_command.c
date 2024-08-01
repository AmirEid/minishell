/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:08:41 by aeid              #+#    #+#             */
/*   Updated: 2024/08/01 19:08:56 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static char	*get_command(char **paths, char *cmd)
{
	int		i;
	char	*p;
	char	*command;

	i = 0;
	while (paths && paths[i])
	{
		p = ft_strjoin(paths[i], "/");
		command = ft_strjoin(p, cmd);
		free(p);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

char **get_cmd_path(t_list *mini_env, t_data *data)
{
	char *path_str;
	char **path;
	
	path_str = search_env(mini_env, "PATH", data);
	if (path_str == NULL)
		return (NULL);
	path = ft_split(path_str, ':');
	free(path_str);
	return(path);
}


void define_commands(t_list *tokens, char **path)
{
	t_list *current;
	t_tkn_data *string;
	
	current = tokens;
	string = NULL;
	while (current)
	{
		string = (t_tkn_data *)current->content;
		if (string->type == WORD)
			string->cmd_exec_path = get_command(path, string->token);
		if (string->cmd_exec_path != NULL)
			string->type = COMMAND;
		current = current->next;
	}
}

