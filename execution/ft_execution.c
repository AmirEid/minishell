/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:27:04 by aeid              #+#    #+#             */
/*   Updated: 2024/07/11 00:47:09 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minishell.h"

static int ft_get_process_num(t_list *tokens)
{
	t_list *current;
	t_tkn_data *tokendata;
	int process_num;

	process_num = 0;
	current = tokens;
	while (current != NULL)
	{
		tokendata = (t_tkn_data *)current->content;
		if (tokendata->type == META_PIPE)
			process_num++;
		current = current->next;
	}
	return (process_num + 1);
}

static void ft_assign_args(t_list **args, t_list *tokens)
{
	t_list *current;
	t_tkn_data *tokendata;
	int i;

	i = 0;
	current = tokens;
	tokendata = (t_tkn_data *)current->content;
	args[i] = tokens;
	while (current != NULL)
	{
		tokendata = (t_tkn_data *)current->content;
		while (tokendata->type != META_PIPE && current != NULL)
		{
			current = current->next;
			tokendata = (t_tkn_data *)current->content;
		}
		if (tokendata->type == META_PIPE)
		{
			i++;
			args[i] = current->next;
			current = current->next;
		}
	}
}

void ft_execute_one_command_line(t_list *tokens, t_list *env)
{
	t_list *current;
	t_tkn_data *tokendata;
	//THIS IS WORK IN PROGRESS
	//in this function i should iterate over the list, until pipe or null..
	//the function will call different functions depending on the type of the token. >> > < << external, builtin
	//make sure to do invoke execve in the end of the function, execute first all builtins and redirections first, then
	//execute the external command.
	// a process can only hand one command (external or builtin) at a time, with redirections.
	current = tokens;
	tokendata = (t_tkn_data *)current->content;
	while (current != NULL && tokendata->type != META_PIPE)
	{
		if (tokendata->type == COMMAND)
			ft_command_execution(tokens, env, &current);
		current = current->next;
		if (current != NULL)
			tokendata = (t_tkn_data *)current->content;
	}
}

void ft_execution(t_list *tokens, t_list *env)
{
	t_list *current;
	t_tkn_data *tokendata;
	int process_num;
	t_list **args;
	pid_t pid;
	
	current = tokens;
	args = NULL;
	pid = 0;
	process_num = ft_get_process_num(tokens);
	if (process_num < 1)
		return ;
	else if (process_num > 1)
	{
		memory_allocator((void **)&args, sizeof(t_list *) * process_num);
		args[process_num] = NULL;
		ft_assign_args(args, tokens);
		//this function will create processes and pipes and then pass to execute one command line as well. (generic function for all the pieces of the command line)
		//while pid, then send to each fork args[i] and env
		create_pipes_and_execution(args, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			ft_execute_one_command_line(tokens, env);
	}
}
