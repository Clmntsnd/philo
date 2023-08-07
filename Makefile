
# -- Executable's name -- #
NAME		=	philo

# -- Compilation Flag -- #
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -pthread
# CFLAGS	=	-Wall -Wextra -Werror -g -Wunreachable-code -fsanitize=address
# CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

# -- Remove -- #
RM			=	rm -rf

# -- SRC Files -- #
SRCS_DIR	=	./srcs/
SRCS_LST	= 	main.c \
				lib.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST))

# -- OBJ Files -- #
OBJS_DIR	=	./obj/
OBJS_LST	=	$(patsubst %.c, %.o, $(SRCS_LST))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LST))

# -- HEADER Files -- #
HEADER_DIR	=	./includes/
HEADER_LST	=	philo.h
HEADER	 	=	$(addprefix $(HEADER_DIR), $(HEADER_LST))


# -- Colors -- #
RESET		= 	\033[0m
RED			= 	\033[0;31m
GREEN		= 	\033[0;32m
YELLOW		= 	\033[0;33m
BLUE		= 	\033[0;34m
PURPLE		= 	\033[0;35m
CYAN		= 	\033[0;36m
ERASE_LINE 	= 	\033[2K\r

EVALUATOR = $(shell whoami)

# -- Executable's creation -- #
all : dir $(NAME)

# -- Compile library -- #
$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(RLINE) -lncurses -o $(NAME) -D EVALUATOR=\"$(EVALUATOR)\" -D BANNER=\"$(TIME)\"
	@echo "✅ $(GREEN)$(NAME)'s exectuable successfully created.		✅$(RESET)"

# -- Create all files .o (object) from files .c (source code) -- #
$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADER)
	@printf "$(ERASE_LINE)🎛️  $(PURPLE)Compiling $(YELLOW)$(notdir $<)\r$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

run: all
	@./$(NAME)

# -- Create directory for *.o files -- #
dir :
	@mkdir -p $(OBJS_DIR)

leak: CFLAGS += -g
leak: all
	@reset
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supp.txt ./$(NAME)

leaks: all
	@reset
	leaks --atExit -- ./$(NAME)

# -- Removes objects -- #
clean :
	@printf "💥 $(RED)Removing $(NAME)'s objects...$(RESET)\t\t\t\t💥\n"
	@$(RM) $(OBJS_DIR)
	@printf "🗑️  $(CYAN)$(NAME)'s object successfully deleted.$(RESET)\t\t\t🗑️\n"

# -- Removes objects (with clean) and executable -- #
fclean : clean
	@printf "💥 $(RED)Removing executable(s)...$(RESET)				💥\n"
	@$(RM) $(NAME)
	@printf "🗑️  $(CYAN)Executable(s) and archive(s) successfully deleted.$(RESET)	🗑️\n\n"
				
# -- Removes objects and executable then remakes all -- #
re : clean all

#Open the subject
pdf : 
	@open https://cdn.intra.42.fr/pdf/pdf/66944/en.subject.pdf

# Run norminette
norm :
	@echo "\n$W>>>>>>>>>>>>>>>>>>>>>>>>>> $YNORMINETTE $W<<<<<<<<<<<<<<<<<<<<<<<<<<$Z\n"
	@norminette $(SRCS) $(HEADER)
	@echo "\n$W>>>>>>>>>>>>>>>>>>>>>>>> $YNORMINETTE ✅ $W<<<<<<<<<<<<<<<<<<<<<<<<<<"

# -- Avoid file-target name conflicts -- #
.PHONY : all bonus clean fclean re pdf