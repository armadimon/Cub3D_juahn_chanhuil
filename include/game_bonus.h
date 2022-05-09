/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:04:01 by juahn             #+#    #+#             */
/*   Updated: 2022/05/09 16:11:05 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_BONUS_H
# define GAME_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "./get_next_line.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "./vector.h"
# include "./key_macos.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17 //Exit program key code
# define KEY_ESC			53

# define TEXWIDTH 64
# define TEXHEIGHT 64
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

typedef struct s_door
{
	t_vec	pos;
	double	open_rate;
}				t_door;

typedef struct s_map_data
{
	int	f_red;
	int	f_green;
	int	f_blue;
	int	c_red;
	int	c_green;
	int	c_blue;
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
	int		w;
	int		a;
	int		s;
	int		d;
	int		al;
	int		ar;
}				t_key;

typedef struct s_render
{
	int		wall_start;
	int		wall_end;
	int		x;
	int		length;
}				t_render;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	p;
	t_map_data	map_data;
	t_render	r;
	t_vec		ray;
	t_door		*door;
	t_img		img;
	t_key		key;
	int			map_width;
	int			map_height;
	int			screen_width;
	int			screen_height;
	int			side;
	char		**map;
	int			**texture;
	int			map_flag;
}				t_game;

/* PARSE & CHECK */
int		read_and_parse_map(t_game *game, t_list *map_buffer, char *argv);
int		parse_map(t_game *game, t_list *map_list);
int		check_map(t_game *game);
int		get_map_arr(t_game *game, t_list *map_list);
int		get_map_contents(t_game *game, char **buf, t_valid *valid);
int		set_f_c_color(t_game *game, char *str, int flag);
int		load_image(t_game *game, int *texture, char *path, t_img *img);
void	free_strs(char **strs);

/* INIT */
void	init_game(t_game *game);
void	init_window(t_game *game);
void	init_img(t_game *game);
int		init_texture(t_game *game);
void	init_valid(t_valid *valid);

/* DRAW 2D MAP */
void	draw_2d_map(t_game *game);
void	draw_ray(t_game *game, int w);

void	draw_3d_map(t_game *game);
void	draw_one_column(t_game *game, int x, double len, t_vec ray);
int		fill_ceiling_color(t_game *game);
int		fill_floor_color(t_game *game);

/* DOOR */
void	cast_ray_and_check_door(t_game *game);

/* KEY */
int		user_stop(int key, t_game *game);
int		user_move(int key, t_game *game);
int		key_press_exit(t_game *game);

int		main_loop(t_game *game);

#endif