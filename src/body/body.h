#ifndef BIODICT_BODY_H
#define BIODICT_BODY_H
#define STEP 2.0f

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "header/header.h"

void initialize_player(Player *player, int screen_width, int screen_height) {
    player->player_image = LoadImage("resources/FarmerSprite.png");
    ImageResize(&player->player_image, player->player_image.width * 2, player->player_image.height * 2);
    player->player_texture = LoadTextureFromImage(player->player_image);

    player->facing_right = 1;
    player->remaining_bullets = INITIAL_BULLET_SIZE;
    player->lives = 3;
    Vector2 player_position = {screen_width / 2, screen_height * 3 / 4};
    Rectangle player_rectangle = {player_position.x, player_position.y, player->player_image.width, player->player_image.height};
    player->position = player_position;
    player->collider = player_rectangle;
    player->airborne_bullets = NULL;
}

void initialize_bullet_textures(Image *bullet_image, Texture2D *bullet_texture) {
    *bullet_image = LoadImage("resources/Bullet.png");
    ImageResize(bullet_image, bullet_image->width / 30, bullet_image->height / 30);
    *bullet_texture = LoadTextureFromImage(*bullet_image);
    UnloadImage(*bullet_image);
}

void flip_farmer(Player *player) {
    if (player->facing_right && IsKeyDown(KEY_LEFT) || !player->facing_right && IsKeyDown(KEY_RIGHT)) {
        player->facing_right = !player->facing_right;
        ImageFlipHorizontal(&player->player_image);
        UnloadTexture(player->player_texture);
        player->player_texture = LoadTextureFromImage(player->player_image);
    }
}

void move_farmer(Player *player, int screen_width, int screen_height) {
    if (IsKeyDown(KEY_UP) && player->position.y >= screen_height * 3 / 4) player->position.y -= STEP;
    if (IsKeyDown(KEY_DOWN) && player->position.y < screen_height) player->position.y += STEP;
    if (IsKeyDown(KEY_LEFT) && player->position.x > 0) player->position.x -= STEP;
    if (IsKeyDown(KEY_RIGHT) && player->position.x < screen_width) player->position.x += STEP;
    flip_farmer(player);
}

void update_bullets(Player *player, Image bullet_image, Texture2D bullet_texture) {
    Bullet *bullet;
    Bullet *aux;

    bullet = player->airborne_bullets;
    while (bullet != NULL) {
        bullet->collider.x = bullet->position.x;
        bullet->collider.y = bullet->position.y;
        bullet->collider.width = bullet_image.width;
        bullet->collider.height = bullet_image.height;
        bullet->position.y -= 20;
        DrawTextureV(bullet_texture, bullet->position, WHITE);
        if (bullet->position.y + bullet_image.height <= 0) {
            player->airborne_bullets = bullet->previous_bullet;
            aux = bullet;
            bullet = bullet->previous_bullet;
            free(aux);
        } else {
            bullet = bullet->previous_bullet;
        }
    }
}

void shoot(Player *player) {
    Bullet *bullet = player->airborne_bullets;

    if (IsKeyPressed(KEY_SPACE)) {
        player->remaining_bullets--;
        if (bullet == NULL) {
            bullet = calloc(1, sizeof(Bullet));
            player->airborne_bullets = bullet;
        } else {
            while (bullet->previous_bullet != NULL) {
                bullet = bullet->previous_bullet;
            }
            bullet->previous_bullet = calloc(1, sizeof(Bullet));
            bullet = bullet->previous_bullet;
        }
        bullet->position = player->position;
    }
}

#endif