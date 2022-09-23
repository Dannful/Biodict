#include <time.h>
#include "raylib.h"

#include "header/functions/game.h"
#include "header/functions/initialization.h"
#include "header/functions/graphics.h"
#include "header/constants.h"

#define GAME_TITLE "Biodict"

int main(void) {
    int screen_width = 800, screen_height = 640;

    GAME game;

    InitWindow(screen_width, screen_height, GAME_TITLE);
    SetTargetFPS(FPS);

    /*screen_width = GetMonitorWidth(GetCurrentMonitor());
    screen_height = GetMonitorHeight(GetCurrentMonitor());
    SetWindowSize(screen_width, min_screen_height);
    MaximizeWindow();
    ToggleFullscreen();
*/
    SetRandomSeed(time(0));

    initialize_game(&game);

    game_loop(&game);

    unload_textures(game.temp_data.game_textures);
    CloseWindow();
    return 0;
}
