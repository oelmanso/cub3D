#include "cub.h"


static void     init_player(t_game *game, char **map)
{
        int     y = 0;
        int x = 0;
        while (map[y])
        {
                int x = 0;
                while (map[y][x])
                {
                    printf("%c", map[y][x]);
                    if (map[y][x] != '0' 
                        &&  map[y][x] != '1' && map[y][x] != ' ')
                        printf("diffrent [%c]\n", map[y][x]);
                    x++;
                }
                printf("\n");
                y++;
        }
        printf("Done ! ---------------\n");
        y = 0;
        while (map[y])
        {
                x = 0;
                while (map[y][x])
                {
                        char c = map[y][x];
                        if (map[y][x] == '\r')
                                map[y][x] = '\0';
                        printf("%c ", map[y][x]);
                        //printf("the player is at pos[%c] y[%d] x[%d]\n", map[y][x], y, x);
                        if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                        {
                                game->player.posX = x + 0.5;
                                game->player.posY = y + 0.5;
                                map[y][x] = '0';
                                if (c == 'N')
                                {
                                        game->player.dirX = 0;
                                        game->player.dirY = -1;
                                        game->player.planeX = 0.66;
                                        game->player.planeY = 0;
                                }
                                else if (c == 'S')
                                {
                                        game->player.dirX = 0;
                                        game->player.dirY = 1;
                                        game->player.planeX = -0.66;
                                        game->player.planeY = 0;
                                }
                                else if (c == 'E')
                                {
                                        game->player.dirX = 1;
                                        game->player.dirY = 0;
                                        game->player.planeX = 0;
                                        game->player.planeY = 0.66;
                                }
                                else if (c == 'W')
                                {
                                        game->player.dirX = -1;
                                        game->player.dirY = 0;
                                        game->player.planeX = 0;
                                        game->player.planeY = -0.66;
                                }
                                return ;
                        }
                        x++;
                }
                printf("\n");
                y++;
        }
}

void game_loop(t_game *g)
{
//      printf("the player is at pos[%c] y[%f] x[%f]\n", g->map[(int)(g->player.posY)][(int)(g->player.posX)], g->player.posY, g->player.posX);
    key_move(g);              // reacts to pressed keys
   // clear_image(&g->frame);      // erase previous frame
    raycaster(g);                // redraw scene
    // return 0;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}



int main (int ac, char **av) 
{
	t_game g;

//     ft_bzero(&g, sizeof(t_game));
	parse_cub(&g, ac, av);
    // ft_bzero(&g.frame, sizeof(t_img));
    ft_bzero(&g.keys, sizeof(t_keys));
    init_player(&g, g.map);
    g.frame.mlx = mlx_init();
    g.frame.win = mlx_new_window(g.frame.mlx, WIDTH, HEIGHT, "cub3d");
    g.frame.img = mlx_new_image(g.frame.mlx, WIDTH, HEIGHT);
    g.frame.addr = mlx_get_data_addr(g.frame.img, &g.frame.bpp, &g.frame.line_len, &g.frame.endian);
    //ROT_SPEED 0.02
    //# define MOVE_SPEED 6
        g.rot_speed = ROT_SPEED;
        g.move_speed = MOVE_SPEED;
     printf("the player is at pos[%c] y[%f] x[%f]\n", g.map[(int)(g.player.posY)][(int)(g.player.posX)], g.player.posY, g.player.posX);
     if (!load_textures(&g))
        print_error1("Invalid texture");
    //  mlx_loop_hook(g.frame.mlx, game_loop, &g);
     mlx_loop_hook(g.frame.mlx, render, &g);
    mlx_hook(g.frame.win, KeyPress, KeyPressMask, key_press, &g);
    mlx_hook(g.frame.win, KeyRelease, KeyReleaseMask, key_release, &g);
    mlx_hook(g.frame.win, 17, 0, ft_close, &g);
    mlx_loop(g.frame.mlx);
	free_all(gc_instance());
	return (0);
}
