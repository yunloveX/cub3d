### FILES AND DIRECTORIES ###
NAME = quatlib.a
GC = gcc
CFLAGS = -std=c89 -g #-Wall -Werror -Wextra # -Imlx # -fsanitize=address

DIR_SRC = src
DIR_OBJ = obj

FILES_QUATLIB = quat_ops1 quat_ops2

FILES_SRC += $(addprefix $(DIR_SRC)/, $(FILES_QUATLIB))
FILES_OBJ = $(addprefix $(DIR_OBJ)/, $(addsuffix .o, $(FILES_QUATLIB)))

MKDIR	= mkdir -p
RM		= rm -rf

INCLUDES = -I ./inc

#####################
### PROGRAM RULES ###
#####################

all: $(NAME)

${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	@${MKDIR} $(DIR_OBJ) 2> /dev/null
	@${GC} ${CFLAGS} ${INCLUDES} -c $< -o $@
	@echo "COMPILED OBJECT $@"

$(NAME): ${FILES_OBJ}
	@ar rcs $(NAME) ${FILES_OBJ}
	@echo "SUCCESSFULLY COMPILED $(NAME)"

bonus: all

###################
### CLEAN RULES ###
###################

clean:
	@${RM} ${DIR_OBJ}
	@echo "-QUATLIB- OBJECTS DELETED. CLEAN SUCCESSFUL!"

fclean: clean
	@${RM} ${NAME}
	@echo "-QUATLIB- LIBRARY DELETED. CLEAN SUCCESSFUL!"

re:	fclean all

.PHONY:	clean re fclean all
