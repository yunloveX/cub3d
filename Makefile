# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 10:56:39 by yunlovex          #+#    #+#              #
#    Updated: 2025/02/17 08:24:42 by iestero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Miscellanea

NAME				=	cub3d
BONUS				=	cub3d_bonus

GREEN 				= 	\033[0;32m
LIGHT_GRAY 			= 	\033[90m
BLUE 				= 	\033[0;34m
NC 					= 	\033[0m
YELLOW				=	\033[93m

MANDATORY_PART 		=	"\n ******************************************************\n				\
						*                                                    *\n					\
						*                                                    *\n					\
						*                   $(YELLOW)MANDATORY PART$(NC)                   *\n		\
						*                                                    *\n					\
						*                                                    *\n					\
						******************************************************\n\n"
BONUS_PART 			=	"\n ******************************************************\n				\
						*                                                    *\n					\
						*                                                    *\n					\
						*                     $(YELLOW)BONUS PART$(NC)                     *\n		\
						*                                                    *\n					\
						*                                                    *\n					\
						******************************************************\n\n"					\

SMILEY				=	😀
CHECK				=	🚀

# Libraries

LIBS_DIR			=	libs
LIBCUB3D			=	$(LIBS_DIR)/libcub3d.a
LIBCUB3D_BONUS		=	$(LIBS_DIR)/libcub3dbonus.a

LIBFT_DIR			=	./libft
LIBFT				=	$(LIBFT_DIR)/libft.a

QUAT_DIR		=	./quatlib
QUAT_INCLUDE	=	$(QUAT_DIR)/inc
QUAT_BUILD		=	$(QUAT_DIR)/build
QUAT			=	$(QUAT_DIR)/quatlib.a

MINILIBX_DIR		=	./MLX42
MINILIBX_INCLUDE	=	$(MINILIBX_DIR)/include
MINILIBX_BUILD		=	$(MINILIBX_DIR)/build
MINILIBX			=	$(MINILIBX_BUILD)/libmlx42.a

#Directories

OBJ_DIR				=	build
OBJBNS_DIR			=	buildbonus

SRC_DIR				=	src
SRCBNS_DIR			= 	srcbonus

TESTS_DIR			=	test
TESTS_DIR_BIN		=	$(TESTS_DIR)/bin
TESTS_DIR_SRC		=	$(TESTS_DIR)/src
TESTS_DIR_OBJ		=	$(TESTS_DIR)/obj

INC_DIR				=	inc
INCBONUS_DIR		=	incbonus

MAIN_DIR			=	main
UTILS_DIR			=	utils
PARSE_DIR			=	parse
RENDER_DIR			=	render
EVENT_DIR			=	events
INIT_DIR			=	init

# Compilation Options

LDLIBS				=	$(LIBCUB3D) $(LIBFT) $(MINILIBX) $(QUAT)
LDLIBS_BONUS		=	$(LIBCUB3D_BONUS) $(LIBFT) $(MINILIBX) $(QUAT)

CC					=	gcc

CFLAGS				=	-g  -Wall -Werror -Wextra -I/usr/include -O3 $(INCLUDES) 
CFLAGS_BONUS		=	-g -Wall -Werror -Wextra -I/usr/include -O3 $(INCLUDES_BONUS)
LDFLAGS				=   $(LDLIBS) -L$(MINILIBX_DIR) -L$(QUAT_DIR) -L/usr/lib -I$(MINILIBX_DIR) -I$(QUAT_DIR) -lglfw -ldl -lXext -lX11 -lm -lz
LDFLAGS_BONUS		=	$(LDLIBS_BONUS) -L$(MINILIBX_DIR) -L$(QUAT_DIR) -L/usr/lib -I$(MINILIBX_DIR) -I$(QUAT_DIR) -lglfw -ldl -lXext -lX11 -lm -lz
INCLUDES			=	-I$(INC_DIR) -I$(addsuffix $(INC_DIR), $(LIBFT_DIR)/) -I$(addsuffix $(INC_DIR), $(QUAT_DIR)/) -I$(QUAT_INCLUDE) -I$(MINILIBX_INCLUDE)
INCLUDES_BONUS		=	-I$(INCBONUS_DIR) -I$(addsuffix $(INC_DIR), $(LIBFT_DIR)/) -I$(addsuffix $(INC_DIR), $(QUAT_DIR)/) -I$(QUAT_INCLUDE) -I$(MINILIBX_INCLUDE)

SANITIZE			=	-fsanitize=address

MKDIR				=	mkdir -p
RM					=	rm -f
AR					= 	ar

ARFLAGS 			= 	rsc

# Source Files

MAIN_FILES		=	cub3d.c					\

INIT_FILES		=	systemInit.c			\

PARSE_FILES		=	configParser.c			\
					mapParser.c				\
					dataParser.c			\
					playerConfig.c			\

RENDER_FILES	=	graphicsRenderer.c		\

UTILS_FILES		=	camera.c				\
					colorUtils.c			\
					errorHandler.c			\
					stringUtils.c			\
					imageLoader.c			\
					eventHandler.c			\
					mapUtils.c				\
					raycastUtils.c			\
					wallUtils.c				\
					drawUtils.c				\

EVENT_FILES 	= 	gameLoop.c				\
					keyboardInput.c			\
					windowClose.c			\


SRCS_FILES	= 	$(addprefix $(MAIN_DIR)/, $(MAIN_FILES)) 		\
				$(addprefix $(RENDER_DIR)/, $(RENDER_FILES)) 	\
				$(addprefix $(UTILS_DIR)/, $(UTILS_FILES)) 		\
				$(addprefix $(PARSE_DIR)/, $(PARSE_FILES)) 		\
				$(addprefix $(EVENT_DIR)/, $(EVENT_FILES)) 		\
				$(addprefix $(INIT_DIR)/, $(INIT_FILES)) 		\

SRCS 		=	$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS 		=	$(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
DIRS		=	$(OBJ_DIR)  $(addprefix $(OBJ_DIR)/, \
					$(MAIN_DIR) $(UTILS_DIR) $(PARSE_DIR) \
					$(RENDER_DIR) $(EVENT_DIR) $(INIT_DIR))

OBJ_MAIN	=	$(addprefix $(OBJ_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_FILES:.c=.o)))

# Source Bonus Files

MAIN_FILES_BONUS		=	cub3d_bonus.c				\

INIT_FILES_BONUS		=	systemInit_bonus.c			\

PARSE_FILES_BONUS		=	configParser_bonus.c		\
							mapParser_bonus.c			\
							dataParser_bonus.c			\
							playerConfig_bonus.c		\

RENDER_FILES_BONUS		=	graphicsRenderer_bonus.c	\

UTILS_FILES_BONUS		=	camera_bonus.c				\
							colorUtils_bonus.c			\
							errorHandler_bonus.c		\
							stringUtils_bonus.c			\
							imageLoader_bonus.c			\
							eventHandler_bonus.c		\
							mapUtils_bonus.c			\
							raycastUtils_bonus.c		\
							wallUtils_bonus.c			\
							drawUtils_bonus.c			\

EVENT_FILES_BONUS 		= 	gameLoop_bonus.c			\
							keyboardInput_bonus.c		\
							mouseInput_bonus.c			\
							windowClose_bonus.c			\

SRCSBONUS_FILES		=	$(addprefix $(MAIN_DIR)/, $(MAIN_FILES_BONUS)) 			\
						$(addprefix $(RENDER_DIR)/, $(RENDER_FILES_BONUS)) 		\
						$(addprefix $(UTILS_DIR)/, $(UTILS_FILES_BONUS)) 		\
						$(addprefix $(PARSE_DIR)/, $(PARSE_FILES_BONUS)) 		\
						$(addprefix $(EVENT_DIR)/, $(EVENT_FILES_BONUS)) 		\
						$(addprefix $(INIT_DIR)/, $(INIT_FILES_BONUS)) 			\

SRCSBONUS 			=	$(addprefix $(SRCBNS_DIR)/, $(SRCSBONUS_FILES))
OBJSBONUS 			=	$(addprefix $(OBJBNS_DIR)/, $(SRCSBONUS_FILES:.c=.o))
DIRSBONUS			=	$(OBJBNS_DIR)  $(addprefix $(OBJBNS_DIR)/, 				\
							$(MAIN_DIR) $(UTILS_DIR) $(PARSE_DIR) 				\
							$(RENDER_DIR) $(EVENT_DIR) $(INIT_DIR))
						
OBJBONUS_MAIN		=	$(addprefix $(OBJBNS_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_BONUS_FILES:.c=.o)))

# Tests

TESTS_FILES				=	TestParseMap.c		\

TESTS					=	$(addprefix $(TESTS_DIR_SRC)/, $(TESTS_FILES:.c))
TESTS_BINARIES			=	$(addprefix $(TESTS_DIR_BIN)/, $(TESTS_FILES:.c=))
TESTSOBJS				=	$(addprefix $(TESTS_DIR_OBJ)/, $(TESTS_FILES:.c=.o))

# Rules

all:	$(NAME)

bonus:	$(BONUS)

test:	$(TESTS_BINARIES)

tclean:
	@$(RM) $(TESTS_BINARIES)
	@$(RM) $(TESTSOBJS)
	

clean:
	@make -s clean -C $(LIBFT_DIR)
	@make -s clean -C $(QUAT_DIR)
	@$(RM) -r $(LIBS_DIR)
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJBNS_DIR)
	@echo "---- $(YELLOW)Object files deleted. $(CHECK)$(NC) ----"

fclean:				clean
	@make -s fclean -C $(LIBFT_DIR)
	@make -s fclean -C $(QUAT_DIR)
	$(RM) $(NAME)
	$(RM) $(BONUS)
	@echo "---- $(YELLOW)Binary files deleted. $(CHECK)$(NC) ----"

re:		fclean all

sre:	clean all

# Mandatory Part Targets

$(NAME):			$(OBJ_MAIN) $(LIBCUB3D) $(LIBFT) $(QUAT) $(MINILIBX)
	@$(CC) $(OBJ_MAIN) $(LDFLAGS) -o $@
	@echo "\n$(GREEN)The program is ready.$(SMILEY) $(CHECK)$(NC)"

$(OBJ)/%.o:		$(SRC_DIR)/%.c | $(DIRS) $(LIBS_DIR)
	@printf "\r\r\t---> $(BLUE)Compiling:\t$(LIGHT_GRAY)$<$(NC)\033[K"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBCUB3D): 		$(OBJS)
	@$(AR) $(ARFLAGS) $@ $?
	@echo "\n   $(CHECK) $(GREEN)Library created.$(NC)"

$(DIRS):
	@clear
	@echo $(MANDATORY_PART)
	@echo "\n   ---> $(BLUE)Creating:\t$(LIGHT_GRAY)libCub3D$(NC)"
	@$(MKDIR) $(DIRS)


# Bonus Part Targets

$(BONUS):				$(OBJBONUS_MAIN) $(LIBCUB3D_BONUS) $(LIBFT) $(QUAT) $(MINILIBX)
	@$(CC) $(OBJBONUS_MAIN) $(LDFLAGS_BONUS) -o $@
	@echo "\n$(GREEN)The program is ready.$(SMILEY) $(CHECK)$(NC)"

$(OBJBNS_DIR)/%.o:		$(SRCBNS_DIR)/%.c | $(DIRSBONUS) $(LIBS_DIR)
	@printf "\r\r\t---> $(BLUE)Compiling:\t$(LIGHT_GRAY)$<$(NC)\033[K"
	@$(CC) $(CFLAGS_BONUS) -c $< -o $@				

$(LIBCUB3D_BONUS): 		$(OBJSBONUS)
	@$(AR) $(ARFLAGS) $@ $?
	@echo "\n   $(CHECK) $(GREEN)Library created.$(NC)"

$(DIRSBONUS):
	@clear
	@echo $(BONUS_PART)
	@echo "\n   ---> $(BLUE)Creating:\t$(LIGHT_GRAY)libCub3D_bonus$(NC)"
	@$(MKDIR) $(DIRSBONUS)

# Tests Targets

$(TESTS_DIR_OBJ)/%.o:	$(TESTS_DIR_SRC)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_BINARIES):	$(TESTSOBJS)
	@$(CC) $< $(LDFLAGS) -o $@ 
	@echo "---------- $(CHECK) $(GREEN)Binary created.$(NC) ----------"


# Additional Rules

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(QUAT):
	@make -s -C $(QUAT_DIR)

$(MINILIBX):
	echo "\n   ---> $(BLUE)Creating:\t$(LIGHT_GRAY)MLX42$(NC)"
	cmake -S $(MINILIBX_DIR) -B $(MINILIBX_BUILD)
	make -C $(MINILIBX_BUILD) -j4
	echo "   $(CHECK) $(GREEN)Library created.$(NC)"

$(LIBS_DIR):
	@$(MKDIR) $@
	

.SILENT:			clean fclean
.PHONY:				all clean fclean re sre bonus tclean test
