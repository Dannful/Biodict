#include "raylib.h"

#include "body/body.h"

#define GAME_TITLE "Biodict"

int main() {
    int screen_width, screen_height;

    Image icon;

    Player player;

    Image bullet_image;
    Texture2D bullet_texture;

    InitWindow(800, 800, GAME_TITLE);

    icon = LoadImage("resources/green_spider.png");
    ImageResize(&icon, 96, 69);

    screen_width =  GetMonitorWidth(GetCurrentMonitor()) / 2;
    screen_height = GetMonitorHeight(GetCurrentMonitor()) / 2;

    SetWindowSize(screen_width, screen_height);
    LoadTextureFromImage(icon);
    SetWindowIcon(icon);
    UnloadImage(icon);
//    ToggleFullscreen();
    MaximizeWindow();

    SetTargetFPS(60);

    initialize_player(&player, screen_width, screen_height);
    initialize_bullet_textures(&bullet_image, &bullet_texture);

    // Main game loop
    while (!WindowShouldClose()) {
        move_farmer(&player, screen_width, screen_height);
        shoot(&player);
        update_bullets(&player, bullet_image, bullet_texture);

        BeginDrawing();
        DrawTextureV(player.player_texture, player.position, WHITE);
        DrawLine(0, screen_height * 3 / 4, screen_width, screen_height * 3 / 4, RED);
        ClearBackground(BLACK);
        EndDrawing();
    }
    UnloadTexture(player.player_texture);
    UnloadTexture(bullet_texture);

    CloseWindow();
    return 0;
}
