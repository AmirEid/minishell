/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:16:30 by aeid              #+#    #+#             */
/*   Updated: 2024/08/09 12:36:37 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./headers/minishell.h"

int	exit_status;

// char	*getTypeName(t_types type)
// {
// 	switch (type)
// 	{
// 		case SPECIAL_SQUOTE: return "SPECIAL_SQUOTE";
// 		case SPECIAL_DQUOTE: return "SPECIAL_DQUOTE";
// 		case META_DOL: return "META_DOL";
// 		case META_PIPE: return "META_PIPE";
// 		case META_REDIR_IN: return "META_REDIR_IN";
// 		case META_REDIR_OUT: return "META_REDIR_OUT";
// 		case META_APPEND: return "META_APPEND";
// 		case META_HEREDOC: return "META_HEREDOC";
// 		case WORD_EXPORT: return "WORD_EXPORT";
// 		case WORD_UNSET: return "WORD_UNSET";
// 		case WORD_ENV: return "WORD_ENV";
// 		case WORD_ECHO: return "WORD_ECHO";
// 		case WORD_CD: return "WORD_CD";
// 		case WORD_EXIT: return "WORD_EXIT";
// 		case WORD_PWD: return "WORD_PWD";
// 		case WORD_DOL: return "WORD_DOL";
// 		case WORD: return "WORD";
// 		case COMMAND: return "COMMAND";
// 		case WORD_WITH_DQUOTE_INSIDE: return "WORD_WITH_DQUOTE_INSIDE";
// 		case WORD_WITH_SQUOTE_INSIDE: return "WORD_WITH_SQUOTE_INSIDE";
// 		default: return "UNKNOWN_TYPE";
// 	}
// }

// void	printTokens(t_list *tokens)
// {
// 	t_list	*current;

// 	current = tokens;
// 	while (current != NULL)
// 	{
// 		t_tkn_data *tokenData = (t_tkn_data *)current->content;
// 		printf("%s - %s -- variable_len: %d\n", tokenData->token, getTypeName(tokenData->type), tokenData->variable_len);
// 		current = current->next;
// 	}
// }
//printTokens(data.tokens);

int	main (int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data = initialize_data();
	data.mini_env = get_env(data, env);
	while (1)
	{
		exit_status = 0;
		ft_signals(&data);
		prompt_loop(&data);
		ft_lexer(&data);
		ft_parsing(&data);
		ft_execution(data.tokens, data.mini_env, &data);
		printf("exit_status: %d\n", exit_status);
		rl_on_new_line();
		if (data.args)
			add_history(data.args);
		free_all(&data);
		reinitialize_data(&data);
	}
	close(data.tmp_fd2);
	close(data.tmp_fd);
	return (0);
}
