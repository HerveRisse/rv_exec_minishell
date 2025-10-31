/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cat_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:01:25 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:01:34 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../includes/minishell.h"

static char	*add_line_to_content(char *content, char *line)
{
	char	*temp;

	temp = content;
	content = ft_strjoin(content, line);
	free(temp);
	free(line);
	temp = content;
	content = ft_strjoin(content, "\n");
	free(temp);
	return (content);
}

static char	*read_heredoc_content(char *delimiter)
{
	char	*line;
	char	*content;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = simple_readline("");
	while (line && ft_strcmp(line, delimiter) != 0)
	{
		content = add_line_to_content(content, line);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = simple_readline("");
	}
	if (line)
		free(line);
	return (content);
}

int	builtin_cat_heredoc(t_command *cmd, t_shell *shell)
{
	char	*content;
	char	*delimiter;

	(void)shell;
	if (!cmd->args[1])
		return (1);
	delimiter = cmd->args[1];
	content = read_heredoc_content(delimiter);
	if (!content)
		return (1);
	ft_putstr_fd(content, STDOUT_FILENO);
	free(content);
	return (0);
}
