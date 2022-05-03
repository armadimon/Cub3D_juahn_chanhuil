#ifndef GAME_H
# define GAME_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "../gnl/get_next_line_bonus.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "./vector.h"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17 //Exit program key code

#define KEY_ESC			53


# define texWidth 64
# define texHeight 64
# define TILE_SIZE 64
# define ROWS 11
# define COLS 15
# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_map_data
{
	int	F_red;
	int	F_green;
	int	F_blue;
	int	C_red;
	int	C_green;
	int	C_blue;
}				t_map_data;

typedef struct s_player
{
	int		player_x;
	int		player_y;
	int		pos_left;
	int		size_l;
	int		bpp;
	int		endian;
}				t_player;

typedef struct s_enemy
{
	int		*enemy_xy;
	int		enemy_cnt;
	int		enemy_cnt_ori;
}				t_enemy;

typedef struct s_vaild
{
	int		valid_no;
	int		valid_so;
	int		valid_we;
	int		valid_ea;
}				t_valid;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			score;
	char		*str_score;
	t_map_data	map_data;
	t_img		img;
	t_player	player;
	t_enemy		enemy;
	int			map_width;
	int			map_height;
	char		*map;

	int			**texture;
}				t_game;

int		read_and_parse_map(t_game *game, t_list *map_buffer, char *argv);
int		parse_map(t_game *game, t_list *map_list);

/* INIT */
void	init_game(t_game *game);
void	init_window(t_game *game);
void	init_img(t_game *game);
int		init_texture(t_game *game);

int		main_loop(t_game *game);

#endif