
# VAR DECLARATION
NAME			:= philo
CC				:= cc
FLAGS			:= -Wall -Wextra -Werror -g -lpthread #-fsanitize=thread
RM				:= rm -f

# SOURCE FILES
SRCS        :=  philo.c srcs/init_input.c srcs/utils.c srcs/init_philo.c srcs/action.c srcs/print.c

# OBJS FILES
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} -c $< -o ${<:.c=.o}

# COLORS
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m


# EXECUTION
${NAME}:	${OBJS} ${LIBFT}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all
