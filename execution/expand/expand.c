
#include "../execution.h"
#include "../../includes/minishell.h"

char	*get_var_name(char *str, int *i);
char	*get_var_value(t_env *env, char *name);
char	*replace_var(char *str, int start, int end, char *value);
int		is_in_quotes(char *str, int pos, int *in_single, int *in_double);

/* Ajoute un caractère à la chaîne de résultat en gérant la mémoire */
static char	*add_char_to_result(char *result, char c)
{
	char	*tmp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	tmp = result;
	result = ft_strjoin(result, buf);
	free(tmp);
	return (result);
}

/* Gère l'expansion de $? (code de retour de la dernière commande) */
static char	*handle_question_mark(char *result, t_shell *shell)
{
	char	*tmp;
	char	*exit_status_str;

	exit_status_str = ft_itoa(shell->exit_status);
	tmp = result;
	result = ft_strjoin(result, exit_status_str);
	free(tmp);
	free(exit_status_str);
	return (result);
}

/* Traite l'expansion d'une variable d'environnement ($VAR) */
static char	*process_variable(char *result, char *str, int *i, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		j;
	char	*tmp;

	start = *i + 1;
	j = 0;
	while (str[start + j] && (ft_isalnum(str[start + j]) || str[start + j] == '_'))
		j++;
	if (j > 0)
	{
		var_name = ft_strndup(str + start, j);
		if (!var_name)
			return (result);
		var_value = get_var_value(env, var_name);
		free(var_name);
		tmp = result;
		result = ft_strjoin(result, var_value);
		free(tmp);
		free(var_value);
		*i += j + 1;
	}
	else
	{
		result = add_char_to_result(result, str[*i]);
		(*i)++;
	}
	return (result);
}

static char	*process_char(char *result, char *str, int *i, t_shell *shell, t_env *env)
{
	if (str[*i] == '$')
	{
		if (!str[*i + 1])
		{
			result = add_char_to_result(result, str[*i]);
			(*i)++;
		}
		else if (str[*i + 1] == '?' && shell)
		{
			result = handle_question_mark(result, shell);
			(*i) += 2;
		}
		else if (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
		{
			result = process_variable(result, str, i, shell ? shell->env : env);
		}
		else
		{
			result = add_char_to_result(result, str[*i]);
			(*i)++;
		}
	}
	else
	{
		result = add_char_to_result(result, str[*i]);
		(*i)++;
	}
	return (result);
}

/* Fonction simplifiée pour l'expansion des variables d'environnement */
char	*expand_variables(char *str, t_env *env)
{
	return (expand_variables_with_shell(str, env, NULL));
}

/* Fonction principale d'expansion des variables avec accès au contexte shell ($?) */
char	*expand_variables_with_shell(char *str, t_env *env, t_shell *shell)
{
	char	*result;
	int		i;
	int		in_single_quotes;
	t_env	*env_to_use;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	in_single_quotes = 0;
	env_to_use = shell ? shell->env : env;
	while (str[i])
	{
		if (str[i] == '\'')
			in_single_quotes = !in_single_quotes;
		if (str[i] == '$' && !in_single_quotes)
			result = process_char(result, str, &i, shell, env_to_use);
		else
			result = add_char_to_result(result, str[i++]);
	}
	return (result);
}
