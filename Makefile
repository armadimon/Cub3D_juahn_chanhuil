SRCS			=	srcs/main.c \
					srcs/map_parser.c \
					srcs/map_parser_2.c \
					srcs/loop.c \
					srcs/init_game.c \
					gnl/get_next_line_bonus.c \

BONUS			=	main.c \

OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS:.c=.o)

CC				=	gcc
RM				=	rm -f

LIBFTNAME		=	libft.a
LIBFTDIR		=	libft
LIBFT			=	$(LIBFTDIR)/$(LIBFTNAME)

MLXNAME			=	libmlx.a
MLXDIR			=	mlx
MLX				=	$(MLXDIR)/$(MLXNAME)

CFLAGS			=	-g -Wall -Wextra -Werror 
LIBS			=	-L$(LIBFTDIR) $(patsubst lib%,-l%,$(basename $(LIBFTNAME))) \
					-L$(MLXDIR) $(patsubst lib%,-l%,$(basename $(MLXNAME))) -framework OpenGL -framework AppKit
MLX				= libmlx.a

NAME			= Cub3D

ifdef WITH_BONUS
	OBJ_FILES = $(BONUS_OBJS)
else
	OBJ_FILES = $(OBJS)
endif

all:			$(NAME)

$(NAME):		$(OBJ_FILES) $(LIBFT) $(MLX)
				gcc ${CFLAGS} -o $(NAME) $(OBJ_FILES) ${LIBS}

bonus :
				@$(MAKE) WITH_BONUS=1 all

$(LIBFT):
				@$(MAKE) -C libft

$(MLX):
				@$(MAKE) -C mlx

clean:
				@$(MAKE) -C libft clean
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS) $(MLX)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus
