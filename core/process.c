
#include "../parser/parser.h"
#include "../execution/execution.h"
#include "../includes/minishell.h"

void	expand_tokens_with_shell(t_token *tokens, t_env *env, t_shell *shell);

/* Fonction simplifiée pour l'expansion des variables dans les tokens */
void	expand_tokens(t_token *tokens, t_env *env)
{
	expand_tokens_with_shell(tokens, env, NULL);
}

void	expand_tokens_with_shell(t_token *tokens, t_env *env, t_shell *shell)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (shell)
			expanded = expand_variables_with_shell(current->value, env, shell);
		else
			expanded = expand_token_value(current->value, env);
		if (expanded)
		{
			free(current->value);
			current->value = expanded;
		}
		current = current->next;
	}
}

/* Vérifie si la ligne est une simple requête pour le code de sortie ($?) */
static int	is_exit_status_query(char *line)
{
	while (*line && is_space(*line))
		line++;
	if (ft_strncmp(line, "$?", 2) == 0)
	{
		line += 2;
		while (*line && is_space(*line))
			line++;
		return (*line == '\0');
	}
	return (0);
}

/* Traite une ligne de commande: lexing, parsing et exécution */
void	process_line(char *line, t_shell *shell)
{
	t_token		*tokens;
	t_ast_node	*ast;
	char		exit_status_str[12];

	if (!line || !*line)
		return ;
	if (is_exit_status_query(line))
	{
		ft_itoa_buf(shell->exit_status, exit_status_str);
		ft_putendl_fd(exit_status_str, STDOUT_FILENO);
		return ;
	}
	tokens = ft_tokenize(line);
	if (!tokens)
		return ;
	expand_tokens_with_shell(tokens, shell->env, shell);
	ast = parse_command(tokens, NULL);
	if (ast)
	{
		execute_ast(ast, shell);
		free_ast(ast);
	}
	free_tokens(&tokens);
}
