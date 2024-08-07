/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anomourn <anomourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:50:04 by aeid              #+#    #+#             */
/*   Updated: 2024/08/09 11:27:32 by anomourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "../Libft/libft.h"
# include "../Printft/ft_printf.h"
# include <readline/readline.h>
#include <readline/history.h>
# include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <termios.h>
#include <limits.h>
//#include <linux/limits.h>


# define PATH_MAX 4096

typedef struct	s_data
{
	t_list	*mini_env;
	t_list	*tokens;
	int		list_size;
	int		current;
	int 	exit_code;
	int		tmp_fd;
	int 	tmp_fd2;
	int		start;
	int 	exp_var;
	char 	*buffer_heredoc;
	int		here_doc;
	int 	process_num;
	char	*pwd;
	char	*old_pwd;
	char	*args; //needs to be freed, result of readline//
	char	**env;
}	t_data;

extern int		exit_status;

void	ft_exit(t_list *args, t_data *data);
void	printTokens(t_list *tokens);
void	ft_signals();
void	ft_sig_term(t_data *data);
int		ft_pwd(t_data *data);
int		ft_cd(t_list *tokens, t_data *data, t_list *mini_env);
void	ft_heredoc_handler(int sig);
void	free_env_list(t_list **env_list);
void	sigint_exec(int sig);
void	free_env_list(t_list **env_list);
void	ft_sign_back_slash(int sig);
void	sigint_handler(int sig);
char	*find_path(char *curr_content, char *variable);
//void free_env_new(t_list **env_list);

# include "lexer.h"
# include "builtins.h"
# include "parsing.h"
# include "execution.h"
# include "utils.h"
# include "get_next_line.h"

#endif