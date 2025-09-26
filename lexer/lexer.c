#include "lexer.h"
#include <stdio.h>
#include "../execution/execution.h"

/* Détermine le type de token en fonction de sa valeur (>, >>, <, <<, |, &&, etc.) */
t_token_type	get_token_type(char *word)
{
	if (!ft_strncmp(word, ">>", 2) && ft_strlen(word) == 2)
		return (APPEND);
	else if (!ft_strncmp(word, "<<", 2) && ft_strlen(word) == 2)
		return (HEREDOC);
	else if (!(ft_strncmp(word, ">", 1)) && ft_strlen(word) == 1)
		return (REDIR_OUT);
	else if (!ft_strncmp(word, "<", 1) && ft_strlen(word) == 1)
		return (REDIR_IN);
	else if (!ft_strncmp(word, "|", 1) && ft_strlen(word) == 1)
		return (PIPE);
	else if (!ft_strncmp(word, "&&", 2) && ft_strlen(word) == 2)
		return (AND);
	else
		return (WORD);
}

/* Crée un nouveau token et l'ajoute à la liste chaînée de tokens */
int	create_token(t_token **tokens, char *word)
{
	t_token	*new;
	t_token	*curr;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->value = word;
	if (!new->value)
	{
		free(new);
		return (0);
	}
	new->type = get_token_type(new->value);
	new->next = NULL;
	if (!(*tokens))
		(*tokens) = new;
	else
	{
		curr = (*tokens);
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (1);
}

/* Analyse lexicale d'une ligne de commande et crée une liste de tokens */
t_token	*ft_tokenize(char *line)
{
	t_token	*tokens;

	if (!line)
		return (NULL);
	tokens = NULL;
	while (*line)
	{
		if (!create_token(&tokens, get_word(&line)))
		{
			free_tokens(&tokens);
			ft_putstr_fd("minishell: syntax error\n", 2);
			return (NULL);
		}
	}
	return (tokens);
}

/* Convertit un type de token en chaîne de caractères pour le débogage */
const char	*token_type_to_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == AND)
		return ("AND");
	return ("UNKNOWN");
}

/* Effectue l'expansion des variables d'environnement dans la valeur d'un token */
char	*expand_token_value(char *value, t_env *env)
{
	char	*expanded;

	if (!value || !env)
		return (ft_strdup(value));
	
	// Vérifier si la valeur contient une variable
	if (ft_strchr(value, '$'))
	{
		// Utiliser expand_variables_with_shell avec shell = NULL
		expanded = expand_variables_with_shell(value, env, NULL);
		if (!expanded)
			return (ft_strdup(value));
		return (expanded);
	}
	return (ft_strdup(value));
}

/* Commented out to avoid conflict with main.c
int	main(int argc, char *argv[])
{
	t_token	*token;
	t_token	*current;

	if (argc != 2)
		return (0);
	token = ft_tokenize(argv[1]);
	if (!token)
		return (1);
	current = token;
	while (current)
	{
		printf("token type: %s\n", token_type_to_str(current->type));
		printf("token word: %s\n\n", current->value);
		current = current->next;
	}
	free_tokens(&token);
	return (0);
}
*/
