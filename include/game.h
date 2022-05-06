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
# include "./key_macos.h"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17 //Exit program key code

#define KEY_ESC			53


# define texWidth 64
# define texHeight 64
# define TILE_SIZE 64
# define WIDTH 960
# define HEIGHT 640

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
	t_vec		pos;
	t_vec		dir;
	t_vec		plane;
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
	int		valid_c;
	int		valid_f;
}				t_valid;

typedef struct s_key
{
	int		W;
	int		A;
	int		S;
	int		D;
	int		AL;
	int		AR;
}				t_key;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	p;
	t_map_data	map_data;
	int			map_width;
	int			map_height;
	int			screen_width;
	int			screen_height;
	int			side;
	char		**map;
	t_img		img;
	int			**texture;
	int			map_flag;
	t_key		key;
}				t_game;

/* PARSE & CHECK */
int		read_and_parse_map(t_game *game, t_list *map_buffer, char *argv);
int		parse_map(t_game *game, t_list *map_list);
int		check_map(t_game *game);
int		get_map_arr(t_game *game, t_list *map_list);
int		get_map_contents(t_game *game, char **buf, t_valid *valid);
int		set_F_C_color(t_game *game, char *str, int flag);
int		load_image(t_game *game, int *texture, char *path, t_img *img);

/* INIT */
void	init_game(t_game *game);
void	init_window(t_game *game);
void	init_img(t_game *game);
int		init_texture(t_game *game);
void	init_valid(t_valid *valid);

void	draw_2D_map(t_game *game);
int		main_loop(t_game *game);

#endif