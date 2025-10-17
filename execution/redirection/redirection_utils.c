
#include "../execution.h"
#include <string.h>

/* Vérifie si un noeud AST est un noeud de redirection (<, >, >>, <<) */
int	is_redirection_node(t_ast_node *node)
{
	return (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT
		|| node->type == NODE_APPEND || node->type == NODE_HEREDOC);
}

/* Configure les descripteurs standard avec les descripteurs de fichier fournis */
void	setup_std_descriptors(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
}

/* Restaure les descripteurs standard à partir des descripteurs temporaires */
void	setup_tmp_descriptors(int tmp_in, int tmp_out)
{
	if (tmp_in != STDIN_FILENO)
	{
		dup2(tmp_in, STDIN_FILENO);
		close(tmp_in);
	}
	if (tmp_out != STDOUT_FILENO)
	{
		dup2(tmp_out, STDOUT_FILENO);
		close(tmp_out);
	}
}

/* Traite un noeud de redirection en configurant les descripteurs appropriés */
int	process_redirection_node(t_ast_node *node, t_shell *shell)
{
	int	fd;
	int	flags;

	/* Gérer les redirections d'entrée */
	if (node->type == NODE_REDIR_IN)
	{
		fd = open(node->filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(node->filename, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			shell->exit_status = 1;
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	/* Gérer les redirections de sortie */
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_APPEND)
	{
		flags = O_WRONLY | O_CREAT;
		if (node->type == NODE_APPEND)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(node->filename, flags, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(node->filename, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			shell->exit_status = 1;
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	/* Gérer heredoc */
	else if (node->type == NODE_HEREDOC)
	{
		int tmp_in = STDIN_FILENO;
		int ret = setup_redirection(node, &tmp_in, NULL, shell);
		if (ret == 0 && tmp_in != STDIN_FILENO)
		{
			dup2(tmp_in, STDIN_FILENO);
			close(tmp_in);
		}
		else if (ret != 0)
		{
			shell->exit_status = 1;
			return (1);
		}
	}
	return (0);
}
