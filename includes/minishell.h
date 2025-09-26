
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../parser/parser.h"
# include "../execution/execution.h"

// signals.c
void	handle_sigint(int sig);
void	setup_signals(void);

// env_init.c
t_env	*init_env(char **envp);

// process.c
void	expand_tokens(t_token *tokens, t_env *env);
void	expand_tokens_with_shell(t_token *tokens, t_env *env, t_shell *shell);
void	process_line(char *line, t_shell *shell);

// readline_utils.c
char	*simple_readline(char *prompt);
void	cleanup_readline(void);
void	setup_readline(void);

// utils.c
void	ft_itoa_buf(int n, char *buf);

#endif
