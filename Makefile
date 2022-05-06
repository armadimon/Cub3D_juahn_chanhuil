SRCS			=	srcs/main.c \
					srcs/parser/map_parser.c \
					srcs/parser/map_parser_2.c \
					srcs/parser/get_map_arr.c \
					srcs/parser/get_map_content.c \
					srcs/parser/load_image.c \
					srcs/parser/get_F_C_color.c \
					srcs/loop.c \
					srcs/init_game.c \
					srcs/engine/draw_2D_map.c \
					srcs/engine/draw_3D_map.c \
					srcs/engine/draw_one_col.c \
					srcs/check_map.c \
					srcs/vectors/vector.c \
					srcs/vectors/vector2.c \
					srcs/vectors/vector3.c \
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

NAME			= cub3D

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
