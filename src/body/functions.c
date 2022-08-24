#ifndef BIODICT_BODY_C
#define BIODICT_BODY_C

#include <math.h>
#include <stdlib.h>
#include "../header/constants.h"
#include "../header/functions.h"

BULLET *allocate_bullet(BULLET **bullet) {
    BULLET *b = *bullet;
    if (*bullet == NULL) {
        b = calloc(1, sizeof(BULLET));
        b->previous_bullet = NULL;
        *bullet = b;
    } else {
        while (b->previous_bullet != NULL)
            b = b->previous_bullet;
        b->previous_bullet = calloc(1, sizeof(BULLET));
        b = b->previous_bullet;
    }
    return b;
}

void animate_player(PLAYER *player, Texture2D player_texture) {
    if (IsKeyDown(KEY_UP) && player->position.y >= (float) GetScreenHeight() * 3 / 4) player->position.y -= PLAYER_SPEED;
    if (IsKeyDown(KEY_DOWN) && player->position.y <= (float) GetScreenHeight()) player->position.y += PLAYER_SPEED;
    if (IsKeyDown(KEY_LEFT) && player->position.x >= 0) player->position.x -= PLAYER_SPEED;
    if (IsKeyDown(KEY_RIGHT) && player->position.x <= (float) GetScreenWidth()) player->position.x += PLAYER_SPEED;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        player->frame_rectangle.x = (float) player_texture.width / 2;
        player->frame_rectangle.width = (float) player_texture.width / 2;
    } else {
        player->frame_rectangle.x = 0;
        player->frame_rectangle.width = (float) player_texture.width / 2;
    }
}

float calculate_angle(float cathetusX, float cathetusY) {
    float rotation = atanf(cathetusY / cathetusX) / PI * 180.0f;
    if (cathetusX < 0 && (rotation < 0 || cathetusY < 0))
        rotation += 180.0f;
    rotation *= -1;
    return rotation;
}

void draw_bullet(BULLET *bullet, Texture2D bullet_texture) {
    while (bullet != NULL) {
        draw_texture_angle(bullet_texture, bullet->position, bullet->angle);
        bullet = bullet->previous_bullet;
    }
}

void draw_crosshair(Texture2D crosshair_texture) {
    Vector2 crosshair_position;
    crosshair_position.x = (float) GetMouseX() - (float) crosshair_texture.width / 2;
    crosshair_position.y = (float) GetMouseY() - (float) crosshair_texture.height / 2;

    DrawTextureV(crosshair_texture, crosshair_position, WHITE);
}

void draw_mushrooms(MUSHROOM *mushrooms, Texture2D mushroom_texture) {
    int i;

    for (i = 0; i < MUSHROOMS; i++) {
        DrawTextureRec(mushroom_texture, mushrooms[i].frame_rectangle, mushrooms[i].position, WHITE);
    }
}

void draw_player(PLAYER *player, Texture2D player_texture) {
    DrawTextureRec(player_texture, player->frame_rectangle, player->position, WHITE);
}

void draw_texture_angle(Texture2D texture, Vector2 position, float angle) {
    Rectangle source = {0.0f, 0.0f, (float) texture.width, (float) texture.height};
    Rectangle destination = {position.x, position.y, (float) texture.width, (float) texture.height};
    Vector2 origin = {(float) texture.width, (float) texture.height};
    DrawTexturePro(texture, source, destination, origin,
                   angle,
                   WHITE);
}

void initialize_mushrooms(MUSHROOM *mushrooms, Texture2D mushroom_texture) {
    int i;

    for (i = 0; i < MUSHROOMS; i++) {
        mushrooms[i].frame_rectangle.x = mushrooms[i].frame_rectangle.y = 0;
        mushrooms[i].frame_rectangle.width = (float) mushroom_texture.width / 2;
        mushrooms[i].frame_rectangle.height = (float) mushroom_texture.height;
        mushrooms[i].state = FULL;

        mushrooms[i].position.x = (float) GetRandomValue(0, GetScreenWidth());
        mushrooms[i].position.y = (float) GetRandomValue(0, GetScreenHeight() * 3 / 4);
    }
}

void initialize_player(PLAYER *player, Texture2D player_texture) {
    player->position.x = (float) GetScreenWidth() / 2;
    player->position.y = (float) GetScreenHeight() * 3 / 4;
    player->remaining_bullets = PLAYER_BULLETS;
    player->lives = PLAYER_LIVES;

    player->frame_rectangle.x = player->frame_rectangle.y = 0;
    player->frame_rectangle.width = (float) player_texture.width / 2;
    player->frame_rectangle.height = (float) player_texture.height;
}

void initialize_textures(GAME_TEXTURES *game_textures) {
    /* Mushroom */

    Image mushroom_image = LoadImage(MUSHROOM_IMAGE_PATH);
    ImageResize(&mushroom_image, (int) ((float) mushroom_image.width * 1.5f),
                (int) ((float) mushroom_image.height * 1.5f));
    game_textures->mushroom = LoadTextureFromImage(mushroom_image);
    UnloadImage(mushroom_image);

    /* Player */

    Image player_image = LoadImage(PLAYER_IMAGE_PATH);
    ImageResize(&player_image, player_image.width * 3, player_image.height * 3);
    game_textures->player = LoadTextureFromImage(player_image);

    /* Crosshair */

    Image crosshair_image = LoadImage(CROSSHAIR_IMAGE_PATH);
    ImageResize(&crosshair_image, crosshair_image.width / 3, crosshair_image.height / 3);
    game_textures->crosshair = LoadTextureFromImage(crosshair_image);
    UnloadImage(crosshair_image);

    /* Bullet */

    Image bullet_image = LoadImage(BULLET_IMAGE_PATH);
    ImageRotateCW(&bullet_image);
    game_textures->bullet = LoadTextureFromImage(bullet_image);
    UnloadImage(bullet_image);

}

void shoot(PLAYER *player, BULLET **bullet, Texture2D bullet_texture, unsigned int *last_bullet_time,
           unsigned int frames_counter) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (float) frames_counter - (float) *last_bullet_time >= (float) GetFPS() * 0.25f) {
        BULLET *b = allocate_bullet(bullet);

        float cathetusX = GetMousePosition().x - player->position.x;
        float cathetusY = player->position.y - GetMousePosition().y;
        float hypotenuse = sqrtf(powf(cathetusX, 2) + powf(cathetusY, 2));
        b->sinus = cathetusY / hypotenuse;
        b->cosinus = cathetusX / hypotenuse;
        b->angle = calculate_angle(cathetusX, cathetusY);

        b->position.x = (float) (player->position.x + ceilf(player->frame_rectangle.width / 2) -
                                 ceilf((float) bullet_texture.width / 2));
        b->position.y = player->position.y;

        *last_bullet_time = frames_counter;
    }
}

void unload_textures(GAME_TEXTURES game_textures) {
    UnloadTexture(game_textures.crosshair);
    UnloadTexture(game_textures.bullet);
    UnloadTexture(game_textures.mushroom);
    UnloadTexture(game_textures.player);
    /* UnloadTexture(game_textures.millipede); Not yet implemented */
    /* UnloadTexture(game_textures.spider); Not yet implemented */
}

void update_bullets(BULLET **bullet) {
    BULLET *b;
    BULLET *aux;

    b = *bullet;
    while (b != NULL) {
        b->position.y -= BULLET_SPEED * b->sinus;
        b->position.x += BULLET_SPEED * b->cosinus;
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