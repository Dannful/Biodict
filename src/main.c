#include <time.h>
#include "raylib.h"

#include "header/functions.h"
#include "header/constants.h"

#define GAME_TITLE "Biodict"

int main(void) {
    int screen_width = 800, screen_height = 640;

    PLAYER player;
    MUSHROOM mushrooms[MUSHROOMS];
    GAME_TEXTURES game_textures;

    BULLET *head_bullet = (void *) 0;
    unsigned int last_bullet_time = 0;
    int frames_counter = 0;

    InitWindow(screen_width, screen_height, GAME_TITLE);
    SetTargetFPS(FPS);
    HideCursor();

    screen_width = GetMonitorWidth(GetCurrentMonitor());
    screen_height = GetMonitorHeight(GetCurrentMonitor());
    SetWindowSize(screen_width, screen_height);
    MaximizeWindow();
    ToggleFullscreen();

    SetRandomSeed(time(0));

    initialize_textures(&game_textures);
    initialize_player(&player, game_textures.player);
    initialize_mushrooms(mushrooms, game_textures.mushroom);


    while (!WindowShouldClose()) {
        frames_counter++;
        animate_player(&player, game_textures.player);
        shoot(&player, &head_bullet, game_textures.bullet, &last_bullet_time, frames_counter);
        update_bullets(&head_bullet);

        BeginDrawing();
        draw_crosshair(game_textures.crosshair);
        draw_bullet(head_bullet, game_textures.bullet);
        draw_player(&player, game_textures.player);
        draw_mushrooms(mushrooms, game_textures.mushroom);
        ClearBackground(BLACK);
        EndDrawing();
    }
    unload_textures(game_textures);
    CloseWindow();
    return 0;
}
