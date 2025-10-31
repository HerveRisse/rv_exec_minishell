
#include "../execution.h"
#include "../../includes/minishell.h"

/* Gère la redirection d'entrée (<) en ouvrant le fichier spécifié */
int	handle_redir_in(char *filename, int *in_fd)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	*in_fd = fd;
	return (0);
}

/* Gère la redirection de sortie (> ou >>) en créant ou ouvrant le fichier spécifié */
int	handle_redir_out(char *filename, int *out_fd, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	*out_fd = fd;
	return (0);
}

/* Gère la redirection de type here-document (<<) en lisant l'entrée jusqu'au délimiteur */
int	handle_heredoc(char *delimiter, int *in_fd)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("minishell: pipe error\n", 2);
		return (1);
	}
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = simple_readline("");
	while (line && ft_strcmp(line, delimiter) != 0)
	{
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = simple_readline("");
	}
	if (line)
		free(line);
	close(pipe_fd[1]);
	*in_fd = pipe_fd[0];
	return (0);
}

/* Configure les redirections en fonction du type de noeud AST */
int	setup_redirection(t_ast_node *ast, int *in_fd, int *out_fd, t_shell *shell)
{
	(void)shell;
	if (ast->type == NODE_REDIR_IN)
		return (handle_redir_in(ast->filename, in_fd));
	else if (ast->type == NODE_REDIR_OUT)
		return (handle_redir_out(ast->filename, out_fd, 0));
	else if (ast->type == NODE_APPEND)
		return (handle_redir_out(ast->filename, out_fd, 1));
	else if (ast->type == NODE_HEREDOC)
		return (handle_heredoc(ast->filename, in_fd));
	return (0);
}
