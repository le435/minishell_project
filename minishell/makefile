NAME = minishell

CC =cc
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
RM = rm -f
USER := $(USER)
SRC = src
BUILTIN = builtins
LIBFT_DIR = libft

READLINE_LIB = -lreadline
READLINE_INCLUDE = -I/usr/include/readline
READLINE=/mnt/homes/$(USER)/homebrew/opt/readline

SRC_LIBFT = $(LIBFT_DIR)/ft_strlen.c \
 			$(LIBFT_DIR)/ft_atoi.c \
 			$(LIBFT_DIR)/ft_strncmp.c \
 			$(LIBFT_DIR)/ft_strdup.c \
 			$(LIBFT_DIR)/ft_split.c \
			$(LIBFT_DIR)/ft_strdup.c\
			$(LIBFT_DIR)/ft_strchr.c\
			$(LIBFT_DIR)/ft_strjoin.c\
			$(LIBFT_DIR)/ft_split.c\
			$(LIBFT_DIR)/ft_strcmp.c \

			
SRC_MANDATORY = nodes/basic_nodes.c \
				nodes/files_tools.c \
				nodes/files.c \
				nodes/node_splite.c \
				nodes/words_helper.c \
				nodes/words.c \
				main.c \
				ft_en.c \
				tokens/lexer.c \
				tokens/qauth_tools.c \
				tokens/syntax_handler.c \
				tokens/file_to_string.c\
				tokens/store.c \
				tokens/remove.c\
				tokens/fake.c\
				tokens/herdoc_counter.c\
				tools/basic.c \
				tools/tools.c \
				tools/herdoc_tool.c\
				tools/herdoc.c \
				dup/c_joiner.c \
				dup/copy.c \
				dup/ft_trim.c \
				garbage/collector.c \
				garbage/free_colector.c \
				garbage/store_garbage.c \
				expand/expnad_word.c \
				expand/_export.c\
				expand/expand.c\
				expand/expand_files.c\
				tools/tools2.c \
				src/builtins/all.c\
                src/builtins/ft_cd.c\
                src/builtins/ft_echo.c\
                src/builtins/ft_exit.c\
                src/builtins/ft_export_handled.c\
                src/builtins/ft_export_handled1.c\
                src/builtins/ft_export_handled2.c\
                src/builtins/ft_export.c\
                src/builtins/ft_pwd.c\
                src/builtins/ft_unset.c\
                src/builtins/ft_env.c\
                src/exec/start.c \
                src/exec/first_child.c \
                src/exec/mid_child.c \
                src/exec/last_child.c \
                src/exec/redir.c \
                src/exec/cmd.c \
                src/exec/cmd_tool.c \
                src/signals/signals.c \
                src/signals/signal_tools.c \
                src/exec/gc.c \

				

HEADERS_MANDATORY = parse.h
LIBFT_HEADER = $(LIBFT_DIR)/libft.h


OBJS_MANDATORY = $(SRC_MANDATORY:.c=.o)

LIBFT = libft/libft.a

all: $(NAME) clean

$(NAME): $(OBJS_MANDATORY) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS_MANDATORY) $(LIBFT) $(READLINE_LIB) -L ${READLINE}/lib  


$(LIBFT): $(SRC_LIBFT) $(LIBFT_HEADER)
	$(MAKE) -C $(LIBFT_DIR) 

%.o: %.c $(HEADERSwe_MANDATORY) $(LIBFT_HEADER)
	$(CC) $(FLAGS) -I ${READLINE}/include $(READLINE_INCLUDE) -c $< -o  $@  

clean:
	$(RM) $(OBJS_MANDATORY)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY:clean