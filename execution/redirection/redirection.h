
#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../../parser/parser.h"

typedef struct s_env t_env;
typedef struct s_shell t_shell;

int		handle_redir_in(char *filename, int *in_fd);
int		handle_redir_out(char *filename, int *out_fd, int append);
int		handle_heredoc(char *delimiter, int *in_fd);
int		setup_redirection(t_ast_node *ast, int *in_fd, int *out_fd,
			t_shell *shell);
void	execute_redirection(t_ast_node *ast, t_shell *shell);

/* Redirection utils */
int		is_redirection_node(t_ast_node *node);
void	setup_std_descriptors(int in_fd, int out_fd);
void	setup_tmp_descriptors(int tmp_in, int tmp_out);
int		process_redirection_node(t_ast_node *node, t_shell *shell);

#endif
