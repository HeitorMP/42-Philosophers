
# VAR DECLARATION
NAME			:= philo
CC				:= cc
FLAGS			:= -Wall -Wextra -Werror -g -pthread -fsanitize=thread
RM				:= rm -f
SRCDIR			:= srcs
OBJSDIR			:= objs

# SOURCE FILES
SRCS        :=  philo.c init_input.c utils.c init_philo.c action.c print.c init_threads.c
OBJS		= $(SRCS:%.c=$(OBJSDIR)/%.o)

# COLORS
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m


# EXECUTION
${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

# CREATE OBJS
${OBJS}: $(OBJSDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	${CC} ${FLAGS} -c $< -o $@

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all
