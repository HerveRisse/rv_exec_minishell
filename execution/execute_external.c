
#include "execution.h"

/* Configure les redirections d'entrée/sortie pour le processus enfant */
static void	setup_redirections(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

/* Exécute la commande externe avec execve et gère les erreurs */
static void	execute_cmd(t_command *cmd, char **env_array, char *path)
{
	execve(path, cmd->args, env_array);
	error_msg("command not found");
	free(path);
	free_array(env_array);
	exit(127);
}

/* Gère le processus enfant: redirections, recherche du chemin et exécution */
static void	child_process(t_command *cmd, t_shell *shell, int in_fd, int out_fd)
{
	char	**env_array;
	char	*path;

	setup_redirections(in_fd, out_fd);
	env_array = env_to_array(shell->env);
	path = find_command_path(cmd->args[0], shell->env);
	if (!path)
	{
		error_msg("command not found");
		free_array(env_array);
		exit(127);
	}
	execute_cmd(cmd, env_array, path);
}

/* Exécute une commande externe en créant un processus enfant */
void	execute_external(t_command *cmd, t_shell *shell, int in_fd, int out_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		child_process(cmd, shell, in_fd, out_fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}
