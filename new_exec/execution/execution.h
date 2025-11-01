/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:57:09 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:57:13 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parser/parser.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
	int		running;
	pid_t	main_pid;
}	t_shell;

void	add_env_var(t_env **env, char *key, char *value);
t_env	*get_env_var(t_env *env, char *key);
void	set_env_var(t_env **env, char *key, char *value);
void	unset_env_var(t_env **env, char *key);
void	free_env(t_env *env);
char	**env_to_array(t_env *env);
void	parse_env_var(char *env_str, char **key, char **value);

void	execute_ast(t_ast_node *ast, t_shell *shell);
void	execute_command(t_ast_node *ast, t_shell *shell, int in_fd, int out_fd);
void	execute_pipe(t_ast_node *ast, t_shell *shell);
void	execute_and(t_ast_node *ast, t_shell *shell);
void	execute_builtin(t_command *cmd, t_shell *shell, int in_fd, int out_fd);
void	execute_external(t_command *cmd, t_shell *shell, int in_fd, int out_fd);
int		is_builtin(char *cmd);

void	execute_redirection(t_ast_node *ast, t_shell *shell);
int		setup_redirection(t_ast_node *ast, int *in_fd, int *out_fd,
			t_shell *shell);

int		builtin_echo(t_command *cmd, t_shell *shell);
int		builtin_cd(t_command *cmd, t_shell *shell);
int		builtin_pwd(t_command *cmd, t_shell *shell);
int		builtin_export(t_command *cmd, t_shell *shell);
int		builtin_unset(t_command *cmd, t_shell *shell);
int		builtin_env(t_command *cmd, t_shell *shell);
int		builtin_exit(t_command *cmd, t_shell *shell);
int		builtin_cat_heredoc(t_command *cmd, t_shell *shell);
int		is_valid_identifier(char *str);

void	error_msg(char *msg);
void	free_array(char **array);

char	*find_command_path(char *cmd, t_env *env);
char	*get_path_value(t_env *env);

char	*expand_variables(char *str, t_env *env);
char	*expand_variables_with_shell(char *str, t_env *env, t_shell *shell);
char	*expand_filename(char *filename, t_env *env);
char	*expand_filename_special(char *filename, t_env *env);

#endif
