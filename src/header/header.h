#ifndef BIODICT_HEADER_H
#define BIODICT_HEADER_H
#include "raylib.h"
#define INITIAL_BULLET_SIZE 240

typedef struct Bullet {

    Vector2 position;
    Rectangle collider;
    struct Bullet *previous_bullet;
} Bullet;

typedef struct {

    int facing_right;
    int remaining_bullets;
    int lives;
    Vector2 position;
    Image player_image;
    Texture2D player_texture;
    Rectangle collider;
    Bullet *airborne_bullets;
} Player;

void initialize_player(Player *player, int screen_width, int screen_height);
void initialize_bullet_textures(Image *bullet_image, Texture2D *bullet_texture);
void flip_farmer(Player *player);
void move_farmer(Player *player, int screen_width, int screen_height);
void update_bullets(Player *player, Image bullet_image, Texture2D bullet_texture);
void shoot(Player *player);
#endif

