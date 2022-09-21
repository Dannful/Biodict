#ifndef BIODICT_HEADER_C
#define BIODICT_HEADER_C

#include "raylib.h"
#include "structures.h"

void animate_millipede(GAME *game);

void check_millipede_bullet_collision(GAME *game);

void check_millipede_player_collision(GAME *game);

void check_mushroom_collision(GAME *game);

void draw_bottom_info(GAME game);

void draw_crosshair(Texture2D crosshair_texture);

void draw_menu(GAME *game, NAME_EDIT *name_edit);

void draw_millipede(MILLIPEDE *millipede, Texture2D millipede_texture);

void draw_mushrooms(MUSHROOM *mushrooms, Texture2D mushroom_texture);

void draw_player(PLAYER *player, Texture2D player_texture);

void draw_segments(GAME *game);

void draw_spiders(SPIDER spiders[], Texture2D spider_texture);

void game_loop(GAME *game);

void initialize_game(GAME *game);

void on_menu_click(GAME *game);

void shoot(GAME *game);

void unload_textures(GAME_TEXTURES game_textures);

void update_player(GAME *game);

void update_spiders(GAME *game);

#endif

