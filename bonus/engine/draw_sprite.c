/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juahn <juahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:29:14 by juahn             #+#    #+#             */
/*   Updated: 2022/05/10 14:57:44 by juahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/game_bonus.h"

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

int	 draw_sprite(t_game *game)
{
int		spriteOrder[game->r.sp_cnt];
double	spriteDistance[game->r.sp_cnt];
	//SPRITE CASTING
    //sort sprites from far to close
    for(int i = 0; i < game->r.sp_cnt; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = (( game->p.pos.x - game->sp[i].pos.x) * ( game->p.pos.x - game->sp[i].pos.x) + (game->p.pos.y - game->sp[i].pos.y) * (game->p.pos.y - game->sp[i].pos.y)); //sqrt not taken, unneeded
    }
    sortSprites(spriteOrder, spriteDistance, game->r.sp_cnt);

    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < game->r.sp_cnt; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = game->sp[spriteOrder[i]].pos.x -  game->p.pos.x;
      double spriteY = game->sp[spriteOrder[i]].pos.y - game->p.pos.y;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (game->p.plane.x * game->p.dir.y - game->p.dir.x * game->p.plane.y); //required for correct matrix multiplication

      double transformX = invDet * (game->p.dir.y * spriteX - game->p.dir.x * spriteY);
      double transformY = invDet * (-game->p.plane.y * spriteX + game->p.plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(HEIGHT / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + HEIGHT / 2;
      if(drawEndY >= HEIGHT) drawEndY = HEIGHT - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int)(HEIGHT / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= WIDTH) drawEndX = WIDTH - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXWIDTH / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < game->r.z_buffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * TEXHEIGHT) / spriteHeight) / 256;
          int color = game->texture[5][TEXWIDTH * texY + texX]; //get current color from the texture
			if (color != 0x980088)
		  	game->img.data[y * WIDTH + stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
    }
	return (1);
}