#include "cub3d.h"
#include "gun.h"
#include "hash.h"
#include "libft.h"
#include "menu.h"
#include "network/net.h"
#include "render/font.h"
#include "render/render.h"
#include "mlx.h"
#include "scene.h"
#include "sound/sound.h"

#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>

static void	close_hook(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
}

suseconds_t	getms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	print_fps(t_vars *vars, suseconds_t delta, suseconds_t frame_time)
{
	float	f;
	char	buf[128];

	f = (1.0 / (delta / 16.0)) * 60.0;
	ft_sprintf(buf, "fps: %d, delta: %d ms", (int) f, (int) frame_time);
	font_draw_str(&vars->r3d, &vars->font, buf, (t_v2i){0, 0}, 3);
}

#define LIMIT_HIGH 0.0167
#define LIMIT_LOW  0.0100

static void	print_scoreboard(t_vars *vars)
{
	const float		step = 0.1;
	int				i;
	float			y;
	char			buf[128];

	i = 0;
	y = -1.0;
	while (i < MAX_CLIENT + 1)
	{
		if (vars->scoreboard.entries[i].present)
		{
			ft_sprintf(buf, "%s | %d | %d", vars->scoreboard.entries[i].username, vars->scoreboard.entries[i].kills, vars->scoreboard.entries[i].death);
			// r3d_draw_text(vars->r3d, vars->font, buf, (t_v2){r3d_get_text_size(vars->r3d, vars->font, buf) / 2.0, y});
		}
		y += step;
		i++;
	}
}

static void	loop_hook(t_vars *vars)
{
	suseconds_t	delta;

	delta = getms() - vars->last_update;
	if (delta < 16)
		return ;
	vars->last_update = getms();
	vars->delta_sec = delta / 1000.0;

	if (vars->delta_sec < LIMIT_LOW)
		vars->delta_sec = LIMIT_LOW;
	else if (vars->delta_sec > LIMIT_HIGH)
		vars->delta_sec = LIMIT_HIGH;

	r3d_clear_color_buffer(&vars->r3d, hex(0x0));
	r3d_clear_depth_buffer(&vars->r3d);

	if (!vars->menu_open)
		map_tick(vars, &vars->map);
	else
		menu_tick(&vars->menu, vars);

	if (vars->is_server)
	{
		netserv_poll(&vars->server, vars);
		netserv_broadcast_scoreboard(&vars->server, &vars->scoreboard);
	}
	else if (vars->client.has_send_connect)
	{
		netclient_poll(&vars->client, vars);
		netclient_pulse(&vars->client);
	}

	if (!vars->menu_open)
	{
		r3d_raycast_world(&vars->r3d, &vars->map, vars);
		draw_gun(&vars->map.player->gun[vars->map.player->gun_index], &vars->r3d);
		minimap_draw(&vars->minimap, &vars->r3d, vars);
	}
	else
		menu_draw(&vars->menu, &vars->r3d, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->r3d.canvas, 0, 0);
}

int	main(int argc, char *argv[])
{
	t_vars			vars;

	(void) argc;
	if (!is_valid_file_name(argv[1]))
		return (false);
	ft_bzero(&vars, sizeof(t_vars));
	vars.map.name = argv[1];
	if (!parsing(&vars, argv, &vars.at))
	{
		ft_free(&vars, &vars.at);
		return (-1);
	}
	vars.last_update = 0;
	vars.mlx = mlx_init();
	if (!vars.mlx)
	{
		ft_putstr_fd(RED"Error\nMLX pointed returned NULL\n"RESET, 2);
		ft_free(&vars, &vars.at);
		return (1);
	}
	vars.win = mlx_new_window(vars.mlx, 1280, 720, "cub3D");
	if (!vars.win)
	{
		ft_putstr_fd(RED"Error\nFailed to create the windows\n"RESET, 2);
		ft_free(&vars, &vars.at);
		return (1);
	}
	mlx_hook(vars.win, DestroyNotify, 0, (void *) close_hook, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_pressed_hook, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_released_hook, &vars);
	mlx_hook(vars.win, ButtonPress, ButtonPressMask, (void *)mouse_button_pressed_hook, &vars);
	mlx_hook(vars.win, ButtonRelease, ButtonReleaseMask, (void *)mouse_button_released_hook, &vars);

	mlx_loop_hook(vars.mlx, (void *) loop_hook, &vars);

	r3d_init(&vars.r3d, vars.mlx, 1280, 720, &vars.at);

	vars.scoreboard.entries[0].present = 1;

	vars.door = tga_load_from_file("assets/textures/DOOR2_4.tga", &vars.at);

	vars.shotgun.main_anim = sprite_create_anim(load_images(&vars.at, 6,
		"assets/textures/SHTGA0.tga",
		"assets/textures/SHTGB0.tga",
		"assets/textures/SHTGC0.tga",
		"assets/textures/SHTGD0.tga",
		"assets/textures/SHTGC0.tga",
		"assets/textures/SHTGB0.tga"
	), 6, false, 100);
	vars.shotgun.shoot_anim = sprite_create_anim(load_images(&vars.at, 2,
		"assets/textures/SHTFA0.tga",
		"assets/textures/SHTFB0.tga"
	), 2, false, 100);
	vars.shotgun.offset = (t_v2i){-18, 96};

	vars.pistol.main_anim = sprite_create_anim(load_images(&vars.at, 5,
		"assets/textures/PISGA0.tga",
		"assets/textures/PISGB0.tga",
		"assets/textures/PISGC0.tga",
		"assets/textures/PISGD0.tga",
		"assets/textures/PISGE0.tga"), 5, false, 100);
	vars.pistol.shoot_anim = sprite_create_anim(load_images(&vars.at, 2, "assets/textures/PISFA0.tga", "assets/textures/PISFA0.tga" 
		), 2, false , 100);
	vars.pistol.main_offset = (t_v2i){24, 7};
	vars.pistol.offset = (t_v2i){0, 128 * 2 + 64};

	vars.minigun.main_anim = sprite_create_anim(load_images(&vars.at, 2,
		"assets/textures/CHGGA0.tga",
		"assets/textures/CHGGB0.tga"), 2, false, 30);
	vars.minigun.shoot_anim = sprite_create_anim(load_images(&vars.at, 2, "assets/textures/CHGFA0.tga",
		"assets/textures/CHGFB0.tga"
		), 2, false , 30);
	vars.minigun.offset = (t_v2i){0, 132};


	sound_read_from_wav(&vars.shotgun.main_sound, "assets/sound/DSSHOTGN.wav", &vars.at);

	if (!font_init(&vars.font, &vars.at))
	{
		ft_free(&vars, &vars.at);
		return (1);
	}

	vars.menu.state = STATE_MAIN;
	vars.menu_open = true;
	vars.exec_hash = fnv32_hash_file("cub3D");

	load_skin(vars.skin[SKIN_MARINE], vars.skin_shoot[SKIN_MARINE], &vars.skin_death[SKIN_MARINE], "player", &vars.at);
	load_skin(vars.skin[SKIN_GUNNER], vars.skin_shoot[SKIN_GUNNER], &vars.skin_death[SKIN_GUNNER], "gunner", &vars.at);

	menu_init(&vars.menu, &vars.r3d, &vars.at);

	t_player	*player = player_new(&vars, &vars.map, next_entity_id(&vars));
	map_add_entity(&vars.map, player);
	vars.map.player = player;

	// t_fake_player	*fake_player = fake_player_new(&vars, vars.scene, next_entity_id(&vars));
	// fake_player->base.transform.position = v3(5.5, 0, 5.5);
	// scene_add_entity(vars.scene, fake_player);

	mlx_hook(vars.win, MotionNotify, PointerMotionMask, (void *) player_mouse_event, &vars);

	minimap_create(&vars.minimap, &vars.r3d, &vars.map, &vars.at);

	player->base.transform = vars.map.spawns[0];
	player->spawn_transform = vars.map.spawns[0];
	// player->gun = vars.shotgun;

	vars.r3d.camera = vars.map.player->camera;

	// t_sound	sound;
	// sound_read_from_wav(&sound, "bfg.wav");
	// sound_play(&sound);

	mlx_mouse_move(vars.mlx, vars.win, 1280 / 2, 720 / 2);
	// mlx_mouse_hide(vars.mlx, vars.win); // TODO: This may leak memory

	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_loop(vars.mlx);
	mlx_do_key_autorepeaton(vars.mlx);

	ft_free(&vars, &vars.at);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
