NAME = minishell

CC = cc
CFLAGS = -g -fsanitize=address -fsanitize=leak -Wall -Wextra -Werror -I.
LDFLAGS = -lreadline

RM = rm -f

# Directories
SRC_DIR_LEXER = ./lexer
SRC_DIR_PARSER = ./parser
SRC_DIR_EXECUTION = ./execution
SRC_DIR_BUILTINS = $(SRC_DIR_EXECUTION)/builtins
SRC_DIR_ENV = $(SRC_DIR_EXECUTION)/env
SRC_DIR_EXPAND = $(SRC_DIR_EXECUTION)/expand
SRC_DIR_REDIRECTION = $(SRC_DIR_EXECUTION)/redirection
SRC_DIR_CD = $(SRC_DIR_BUILTINS)/cd
SRC_DIR_CORE = ./core
SRC_DIR_INCLUDES = ./includes

# Source files
SRC_MAIN = main.c

SRC_CORE = \
	  $(SRC_DIR_CORE)/signals.c \
	  $(SRC_DIR_CORE)/env_init.c \
	  $(SRC_DIR_CORE)/process.c \
	  $(SRC_DIR_CORE)/readline_utils.c \
	  $(SRC_DIR_CORE)/utils.c

SRC_LEXER = \
	  $(SRC_DIR_LEXER)/lexer.c \
	  $(SRC_DIR_LEXER)/lexer_utils.c \
	  $(SRC_DIR_LEXER)/extract_word.c \
	  $(SRC_DIR_LEXER)/extract_word_utils.c \
	  $(SRC_DIR_LEXER)/utils.c \
	  $(SRC_DIR_LEXER)/manage_memory.c \
	  $(SRC_DIR_LEXER)/segments.c \
	  $(SRC_DIR_LEXER)/segments_utils.c

SRC_PARSER = \
	  $(SRC_DIR_PARSER)/parser.c \
	  $(SRC_DIR_PARSER)/parser_utils.c \
	  $(SRC_DIR_PARSER)/parser_tools.c \
	  $(SRC_DIR_PARSER)/parser_and.c \
	  $(SRC_DIR_PARSER)/manage_memory.c

SRC_REDIRECTION = \
	  $(SRC_DIR_REDIRECTION)/setup_redirection.c \
	  $(SRC_DIR_REDIRECTION)/execute_redirection.c \
	  $(SRC_DIR_REDIRECTION)/redirection_utils.c

SRC_EXECUTION = \
	  $(SRC_DIR_EXECUTION)/execution.c \
	  $(SRC_DIR_EXECUTION)/path_utils.c \
	  $(SRC_DIR_EXECUTION)/execute_and.c \
	  $(SRC_DIR_EXECUTION)/execute_command.c \
	  $(SRC_DIR_EXECUTION)/execute_pipe.c \
	  $(SRC_DIR_EXECUTION)/execute_external.c \
	  $(SRC_DIR_EXECUTION)/execution_utils.c

SRC_CD = \
	  $(SRC_DIR_CD)/cd_utils.c \
	  $(SRC_DIR_CD)/cd_cases.c \
	  $(SRC_DIR_CD)/cd_env.c

SRC_BUILTINS = \
	  $(SRC_DIR_BUILTINS)/builtins.c \
	  $(SRC_DIR_BUILTINS)/builtins_echo.c \
	  $(SRC_DIR_BUILTINS)/builtins_cd.c \
	  $(SRC_DIR_BUILTINS)/builtins_pwd.c \
	  $(SRC_DIR_BUILTINS)/builtins_env.c \
	  $(SRC_DIR_BUILTINS)/builtins_export.c \
	  $(SRC_DIR_BUILTINS)/builtins_unset.c \
	  $(SRC_DIR_BUILTINS)/builtins_exit.c \
	  $(SRC_DIR_BUILTINS)/builtins_cat_heredoc.c \
	  $(SRC_DIR_BUILTINS)/builtins_utils.c

SRC_ENV = \
	  $(SRC_DIR_ENV)/env.c \
	  $(SRC_DIR_ENV)/env_utils.c \
	  $(SRC_DIR_ENV)/env_var.c \
	  $(SRC_DIR_ENV)/env_unset.c \
	  $(SRC_DIR_ENV)/env_array.c

SRC_EXPAND = \
	  $(SRC_DIR_EXPAND)/expand.c \
	  $(SRC_DIR_EXPAND)/expand_utils.c \
	  $(SRC_DIR_EXPAND)/expand_filename.c

# All sources
SRC = $(SRC_MAIN) $(SRC_CORE) $(SRC_LEXER) $(SRC_PARSER) $(SRC_EXECUTION) $(SRC_BUILTINS) $(SRC_ENV) $(SRC_EXPAND) $(SRC_REDIRECTION) $(SRC_CD)

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re