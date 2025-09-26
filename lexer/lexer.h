
#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	VARIABLE,
	AND
}	t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	struct s_token			*next;
}	t_token;

typedef struct s_segment
{
	int					type;
	char				*word;
	struct s_segment	*next;
}	t_segment;

// Forward declaration
typedef struct s_env	t_env;

// lexer.c
t_token		*ft_tokenize(char *line);
void		free_tokens(t_token **head);
char		*expand_token_value(char *value, t_env *env);

// Function from execution/expand.c
char		*expand_variables(char *str, t_env *env);

// lexer_utils.c
char		*get_word(char **line);

// extract_word.c
char		*extract_word_without_quotes(char **l);
char		*extract_word_simple_quotes(char **l);
char		*extract_word_double_quotes(char **l);
char		*extract_operator(char **l);
char		*extract_variable(char **l);

// extract_word_utils.c
char		*get_word_expand(char *line, size_t len);
char		*get_word_in_double_quotes(char *line, size_t len);

// segments.c
t_segment	*create_segments(char *word);
char		*convert_segments_to_str(t_segment *segments);
void		free_segments(t_segment *segments);

// segments_utils.c
char		*convert_segments_to_str(t_segment *segments);
t_segment	*create_new_segment(t_segment *head, char *current, size_t len);
void		set_word_and_type_segment(t_segment *segment, char *word,
				size_t len);
size_t		get_len_segment_word(char *word);
size_t		get_len_from_segments(t_segment *segments);

// utils.c
int			is_space(int c);
int			is_quotes(int c);
int			is_operator(char *line);
void		remove_space(char **line);
char		*ft_strndup(char *str, size_t len);

// manage_memory.c
void		free_segments(t_segment *segments);

#endif