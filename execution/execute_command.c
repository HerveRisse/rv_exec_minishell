
#include "execution.h"

/* Exécute une commande simple, qu'elle soit builtin ou externe */
void	execute_command(t_ast_node *ast, t_shell *shell, int in_fd, int out_fd)
{
	if (!ast || !ast->cmd || !ast->cmd->args || !ast->cmd->args[0])
		return ;
	if (is_builtin(ast->cmd->args[0]))
		execute_builtin(ast->cmd, shell, in_fd, out_fd);
	else
		execute_external(ast->cmd, shell, in_fd, out_fd);
}
