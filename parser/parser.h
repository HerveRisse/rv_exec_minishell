
#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_PIPE,
	NODE_AND,
	NODE_INVALID
} t_node_type;

typedef struct s_command
{
	char **args;
} t_command;

typedef struct s_ast_node
{
	t_node_type type;
	t_command *cmd;
	char *filename;
	struct s_ast_node *left;
	struct s_ast_node *right;
} t_ast_node;

t_ast_node *parse_command(t_token *tokens, t_token *stop);

// parser_utils.c:
t_token *find_redirections_token(t_token *tokens, t_token *stop);
t_token *find_pipe_token(t_token *tokens, t_token *stop);
t_token *find_and_token(t_token *tokens, t_token *stop);
t_node_type get_type_node(t_token *token);
int has_redirections(t_token *tokens, t_token *stop);
int has_pipe(t_token *tokens, t_token *stop);
int has_and(t_token *tokens, t_token *stop);
t_ast_node *parse_command_with_and(t_token *tokens, t_token *stop);

// parser_tools.c:
void init_ast_node(t_ast_node *node);
size_t count_token_words(t_token *tokens, t_token *stop);
char **create_args(t_token *tokens, size_t nb_words);
t_command *create_command(t_token *tokens, t_token *stop);

// manage_memory.c:
void free_ast(t_ast_node *node);
void free_command(t_command *cmd);

#endif