###############################################################################
######                            PROPERTIES                             ######
###############################################################################

NAME		= pipex
NAME_BONUS	= pipex_bonus
CFLAGS		= -Wall -Wextra -Werror -MP -MD -g
LIBFT_DIR	= src/libft/
LIBFT		= ft

SRCS_DIR	= src
UTILS_DIR	= src/utils
TEST_DIR	= tests

SRCS		= \
	${SRCS_DIR}/main.c

BONUS_SRCS	= \
	${SRCS_DIR}/main_bonus.c

SRCS_UTILS	= \
	${UTILS_DIR}/command.c \
	${UTILS_DIR}/data.c \
	${UTILS_DIR}/error.c \
	${UTILS_DIR}/freer.c \
	${UTILS_DIR}/pipe.c \
	${UTILS_DIR}/utils.c

OBJS_DIR	= ${SRCS_DIR}/objs
OBJS		= \
	${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o} \
	${SRCS_UTILS:${UTILS_DIR}/%.c=${OBJS_DIR}/%.o}

BONUS_OBJS		= \
	${BONUS_SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o} \
	${SRCS_UTILS:${UTILS_DIR}/%.c=${OBJS_DIR}/%.o}

###############################################################################
######                               RULES                               ######
###############################################################################

all: ${NAME}

${NAME}: ${OBJS}
	@make -C ${LIBFT_DIR}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} -L${LIBFT_DIR} -l${LIBFT}

bonus: ${BONUS_OBJS}
	@make -C ${LIBFT_DIR}
	${CC} ${CFLAGS} -o ${NAME_BONUS} ${BONUS_OBJS} -L${LIBFT_DIR} -l${LIBFT}

clean:
	@make -C ${LIBFT_DIR} clean
	@rm -rf ${OBJS_DIR}

fclean: clean
	@make -C ${LIBFT_DIR} fclean
	@rm -f ${NAME}

run: ${NAME}
	./${NAME}

re: fclean all

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p $(dir $@)
	@cc ${CFLAGS} -c $< -o $@

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p $(dir $@)
	@cc ${CFLAGS} -c $< -o $@

${OBJS_DIR}/%.o: ${UTILS_DIR}/%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: all clean fclean re
