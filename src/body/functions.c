#ifndef BIODICT_BODY_C
#define BIODICT_BODY_C

#include "pthread.h"
#include <stdlib.h>
#include "raylib.h"
#include "../header/structures.h"
#include "../header/constants.h"

void draw_bullet(Bullet *bullet, Texture2D bullet_texture) {
    while (bullet != NULL) {
        DrawTextureV(bullet_texture, bullet->position, WHITE);
        bullet = bullet->previous_bullet;
    }
}

void draw_mushrooms(Mushroom *mushrooms) {
    int i;

    for (i = 0; i < MUSHROOMS; i++) {
        DrawTextureV(mushrooms[i].texture, mushrooms[i].position, WHITE);
    }
}

void draw_player(Player *player) {
    DrawTextureV(player->texture, player->position, WHITE);
}

void initialize_mushrooms(Mushroom *mushrooms) {
    int i;

    Image mushroom_image = LoadImage(MUSHROOM_IMAGE_PATH);
    ImageResize(&mushroom_image, mushroom_image.width * 1.5f, mushroom_image.height * 1.5f);
    Texture2D mushroom_texture = LoadTextureFromImage(mushroom_image);
    UnloadImage(mushroom_image);

    for (i = 0; i < MUSHROOMS; i++) {
        mushrooms[i].texture = mushroom_texture;
        mushrooms[i].position.x = GetRandomValue(0, GetScreenWidth());
        mushrooms[i].position.y = GetRandomValue(0, GetScreenHeight() * 3 / 4);
    }
}

void initialize_player(Player *player) {
    player->position.x = GetScreenWidth() / 2;
    player->position.y = GetScreenHeight() * 3 / 4;
    player->remaining_bullets = PLAYER_BULLETS;
    player->lives = PLAYER_LIVES;

    Image player_image = LoadImage(PLAYER_IDLE_IMAGE_PATH);
    ImageResize(&player_image, player_image.width * 3, player_image.height * 3);
    player->texture = LoadTextureFromImage(player_image);
    UnloadImage(player_image);
}

void move_player(Player *player) {
    if (IsKeyDown(KEY_UP) && player->position.y >= GetScreenHeight() * 3 / 4) player->position.y -= 2;
    if (IsKeyDown(KEY_DOWN) && player->position.y <= GetScreenHeight()) player->position.y += 2;
    if (IsKeyDown(KEY_LEFT) && player->position.x >= 0) player->position.x -= 2;
    if (IsKeyDown(KEY_RIGHT) && player->position.x <= GetScreenWidth()) player->position.x += 2;
}

void shoot(Player *player, Bullet **bullet) {
    Bullet *b = *bullet;

    if (IsKeyPressed(KEY_SPACE)) {
        /*UnloadTexture(player->texture);
        Image player_image = LoadImage(PLAYER_SHOOT_IMAGE_PATH);
        ImageResize(&player_image, player_image.width * 3, player_image.height * 3);
        player->texture = LoadTextureFromImage(player_image);
        UnloadImage(player_image);*/

        if (*bullet == NULL) {
            b = calloc(1, sizeof(Bullet));
            *bullet = b;
        } else {
            while (b->previous_bullet != NULL)
                b = b->previous_bullet;
            b->previous_bullet = calloc(1, sizeof(Bullet));
            b = b->previous_bullet;
        }
        b->position = player->position;
    }
}

void unload_textures(Mushroom *mushrooms, Player *player) {
    int i;

    for(i = 0; i < MUSHROOMS; i++)
        UnloadTexture(mushrooms[i].texture);

    UnloadTexture(player->texture);
}

void update_bullets(Bullet **bullet) {
    Bullet *b;
    Bullet *aux;

    b = *bullet;
    while (b != NULL) {
        b->position.y -= 20;
        if (b->position.y <= 0) {
            *bullet = b->previous_bullet;
            aux = b;
            b = b->previous_bullet;
            free(aux);
        } else {
            b = b->previous_bullet;
        }
    }
}

#endif