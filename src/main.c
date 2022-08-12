#include "raylib.h"

#include "body/functions.c"
#include "header/constants.h"

#define GAME_TITLE "Biodict"

int main(void) {
    int screen_width = 800, screen_height = 640;

    Player player;

    Mushroom mushrooms[MUSHROOMS];

    Bullet *bullet = NULL;

    InitWindow(screen_width, screen_height, GAME_TITLE);
    SetTargetFPS(60);

    initialize_mushrooms(mushrooms);
    initialize_player(&player);

    Texture2D bullet_texture = LoadTextureFromImage(LoadImage("resources/bullet.png"));

    // Main game loop
    while (!WindowShouldClose()) {
        move_player(&player);
        shoot(&player, &bullet);
        update_bullets(&bullet);

        BeginDrawing();
        draw_bullet(bullet, bullet_texture);
        draw_player(&player);
        draw_mushrooms(mushrooms);
        ClearBackground(BLACK);
        EndDrawing();
    }
    unload_textures(mushrooms, &player);
    CloseWindow();
    return 0;
}
