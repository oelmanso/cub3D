/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:12:31 by zhassna           #+#    #+#             */
/*   Updated: 2026/01/03 00:39:40 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MINI_TILE 20
# define MINI_X 10
# define MINI_Y 10
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307
# define ROT_SPEED 0.03
# define MOVE_SPEED 0.09
# define FOV_DEG 50
# define TILE_SIZE 100
# define WIDTH 2000
# define HEIGHT 2000
# define NO 0
# define SO 1
# define WE 2
# define EA 3

typedef struct s_box
{
	double						camerax;
	double						raydirx;
	double						raydiry;
	int							mapx;
	int							mapy;
	double						deltadistx;
	double						deltadisty;
	int							stepx;
	int							stepy;
	double						sidedistx;
	double						sidedisty;
	int							hit;
	int							side;
	double						perpwalldist;
	int							lineheight;
	int							drawstart;
	int							drawend;
	double						wallx;
	double						step;
	double						texpos;
	int							color;
	int							texnum;
	int							texx;
	int							texy;
}								t_box;

typedef struct s_garbage_collector
{
	int							already_free;
	void						*ptr;
	struct s_garbage_collector	*next;
}								t_garbage_collector;

typedef struct s_keys
{
	int							w;
	int							a;
	int							s;
	int							d;
	int							left;
	int							right;
}								t_keys;

typedef struct s_color
{
	int							flage;
	int							r;
	int							g;
	int							b;
	int							value;
}								t_color;

typedef struct s_texture
{
	void						*img;
	char						*addr;
	int							w;
	int							h;
	int							bpp;
	int							line_len;
	int							endian;
	int							flag;
	char						*path;
}								t_texture;

typedef struct s_img
{
	void						*mlx;
	void						*win;
	void						*img;
	char						*addr;
	int							bpp;
	int							line_len;
	int							endian;
}								t_img;

typedef struct s_player
{
	double						posx;
	double						posy;
	double						dirx;
	double						diry;
	double						planex;
	double						planey;
	double						fov;
}								t_player;

typedef struct s_game
{
	t_img						frame;
	char						**all_map;
	char						**map;
	int							width_map;
	int							length_map;
	int							map_start;
	int							flag_pos;
	t_texture					textures[4];
	t_color						floor_color;
	t_color						ceiling_color;
	t_player					player;
	double						rot_speed;
	double						move_speed;
	t_keys						keys;
}								t_game;

void							turn_left_right(t_game *g, double angle);
void							key_a_d(t_game *g, double sx, double sy);
void							key_move2(t_game *g);
int								ft_handler(int keycode, t_game *g);
int								key_move(t_game *g);
int								ft_moving(char direction, t_game *g);
void							ft_finish(t_game *g);
/// this one below must be declared as static later !!
void							my_mlx_pixel_put(t_img *img, int x, int y,
									int color);
int								raycaster(t_game *g);
int								key_press(int keycode, t_game *g);
int								key_release(int keycode, t_game *g);
int								load_textures(t_game *game);
void							get_texture_color(t_game *g, t_box *box, int x,
									int y);
void							texture(t_game *g, t_box *box);
void							distance(t_game *g, t_box *box);
void							init_player(t_game *game, char **map);
char							*strdup_map(char *s1, int len);
int								close_window(void *param);
char							*get_next_line(int fd);
char							*ft_remember(char *remb);
char							*ft_get_line(char *remb);
char							*ft_read_buffer(char *remb, int fd);
char							*ft_strjoin(char *s1, char *s2);
void							*ft_calloc(size_t count, size_t size);
void							ft_bzero(void *s, size_t n);
int								ft_strncmp(char *s1, char *s2, size_t n);
char							*ft_strdup(char *s1);
int								ft_strlen(char *s1);
int								ft_atoi(char *str);
char							*ft_strtrim(char *s1, char *set);
char							*ft_substr(char *s, int start, int len);
void							*ft_free(char **a, int j);
char							**ft_split(char *s, char c);
t_garbage_collector				**gc_instance(void);
void							is_already_free(t_garbage_collector **gc,
									void *ptr);
void							free_all(t_garbage_collector **lst);
void							gc_add_node_back(t_garbage_collector **lst,
									t_garbage_collector *new);
t_garbage_collector				*gc_last_node(t_garbage_collector *lst);
t_garbage_collector				*gc_new_node(void *ptr);
void							draw_square(t_game *g, int x, int y, int c);
int								render(t_game *g);
void							draw_player_dir(t_game *g);
void							draw_player_minimap(t_game *g);
void							game_loop(t_game *g);
void							draw_minimap(t_game *g);
int								check_name(char *av, char *p);
void							error_textur(char *msg, char *s);
int								whitespace(char c);
void							print_error(char *msg);
int								valide_elem(char c);
void							pos_player(t_game *game);
int								check_player(char c);
int								calcul_long(t_game *game, char **map);
void							alloc_map(t_game *game, int len, int lng);
void							full_map(t_game *game);
int								is_allowed(char c);
int								is_invalid(char c);
int								close_up_down(char *map);
int								close_left(char **map);
int								close_right(char **map);
int								valid_way(char **map);
void							is_map_last(t_game *game, int i);
int								valid_number(char *line);
int								is_num(char *str);
int								parse_color(t_color *color, char *s);
int								check_texture_path(char *path);
void							parse_textur(t_texture *t, char *map);
int								texture_color(t_game *game, char *m, char c,
									int i);
int								check_parse_file(t_game *game);
void							parse_cub_file(t_game *game);
void							read_map(t_game *game, char **av);
void							parse_cub(t_game *game, int ac, char **av);
void							init(t_game *game);
void							print_error1(char *msg);
int								ft_close(t_game *g);
int								ft_color(int c);
int								ft_size(int c);

#endif
