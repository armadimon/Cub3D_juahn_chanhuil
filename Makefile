SRCS			=	mandatory/main.c \
					mandatory/loop.c \
					mandatory/init_game.c \
					mandatory/handle_key.c \
					mandatory/parser/map_parser.c \
					mandatory/parser/map_parser_2.c \
					mandatory/parser/get_map_arr.c \
					mandatory/parser/get_map_content.c \
					mandatory/parser/load_image.c \
					mandatory/parser/get_F_C_color.c \
					mandatory/parser/check_map.c \
					mandatory/parser/utils.c \
					mandatory/engine/draw_2D_map.c \
					mandatory/engine/draw_2D_ray.c \
					mandatory/engine/draw_3D_map.c \
					mandatory/engine/draw_one_col.c \
					mandatory/engine/draw_floor_ceiling.c \
					mandatory/vectors/vector.c \
					mandatory/vectors/vector2.c \
					mandatory/vectors/vector3.c \
					mandatory/gnl/get_next_line.c \
					mandatory/gnl/get_next_line_utils.c \

BONUS			=	bonus/main.c \
					bonus/loop.c \
					bonus/init_game.c \
					bonus/init_texture.c \
					bonus/handle_key.c \
					bonus/parser/map_parser.c \
					bonus/parser/map_parser_2.c \
					bonus/parser/get_map_arr.c \
					bonus/parser/get_map_content.c \
					bonus/parser/load_image.c \
					bonus/parser/get_F_C_color.c \
					bonus/parser/check_map.c \
					bonus/parser/check_map_2.c \
					bonus/parser/utils.c \
					bonus/engine/door.c \
					bonus/engine/draw_2D_map.c \
					bonus/engine/draw_2D_ray.c \
					bonus/engine/draw_3D_map.c \
					bonus/engine/draw_3D_map_2.c \
					bonus/engine/draw_one_col.c \
					bonus/engine/draw_sprite.c \
					bonus/engine/draw_floor_ceiling.c \
					bonus/vectors/vector.c \
					bonus/vectors/vector2.c \
					bonus/vectors/vector3.c \
					bonus/gnl/get_next_line.c \
					bonus/gnl/get_next_line_utils.c \

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

fclean:
				@$(MAKE) -C libft fclean
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS) $(MLX)
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus
