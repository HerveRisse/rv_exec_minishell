
#include "execution.h"

/* Exécute la commande à gauche du pipe en redirigeant sa sortie vers le pipe */
static void	execute_left_command(int *pipe_fd, t_ast_node *left,
		t_shell *shell)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	signal(SIGPIPE, SIG_DFL);
	execute_ast(left, shell);
	exit(shell->exit_status);
}

/* Exécute la commande à droite du pipe en prenant son entrée depuis le pipe */
static void	execute_right_command(int *pipe_fd, t_ast_node *right,
		t_shell *shell)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	signal(SIGPIPE, SIG_DFL);
	execute_ast(right, shell);
	exit(shell->exit_status);
}

/* Configure le pipe et crée les processus enfants pour les commandes gauche et droite */
static void	setup_pipe(int *pipe_fd, t_ast_node *ast, t_shell *shell,
		int *saved_stdin, pid_t *pid1, pid_t *pid2)
{
	*saved_stdin = dup(STDIN_FILENO);
	*pid1 = fork();
	if (*pid1 == 0)
		execute_left_command(pipe_fd, ast->left, shell);
	*pid2 = fork();
	if (*pid2 == 0)
		execute_right_command(pipe_fd, ast->right, shell);
}

/* Exécute deux commandes reliées par un pipe, connectant la sortie de la première à l'entrée de la seconde */
void	execute_pipe(t_ast_node *ast, t_shell *shell)
{
	int		pipe_fd[2];
	int		status;
	int		saved_stdin;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		// error_msg("pipe error");
		return ;
	}
	setup_pipe(pipe_fd, ast, shell, &saved_stdin, &pid1, &pid2);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	// Attendre les deux processus
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	// Restaurer stdin 
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	// Le code de sortie du pipe est celui de la dernière commande (pid2)
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}
