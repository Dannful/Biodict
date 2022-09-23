#include "functions/events.h"
#include "functions/graphics.h"

void on_exit_click(GAME_TEXTURES game_textures) {
    Rectangle box;
    int gap = menu_gap(game_textures);

    box.x = (float) gap * 5 + (float) game_textures.start_game.width + (float) game_textures.load_game.width +
            (float) game_textures.pause_game.width + (float) game_textures.game_ranking.width;
    box.y = (float) gap / 2;
    box.width = (float) game_textures.exit_game.width;
    box.height = (float) game_textures.exit_game.height;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), box)) {
        unload_textures(game_textures);
        CloseWindow();
    }
}

void on_load_click(GAME *game) {
    GAME_TEXTURES game_textures = game->temp_data.game_textures;
    Rectangle box;
    int gap = menu_gap(game_textures);

    box.x = (float) gap * 2 + (float) game_textures.start_game.width;
    box.y = (float) gap / 2;
    box.width = (float) game_textures.load_game.width;
    box.height = (float) game_textures.load_game.height;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), box)) {
        game->temp_data.selected = LOAD;
    }
}

void on_menu_click(GAME *game) {
    on_start_click(game);
    on_load_click(game);
    on_pause_click(game);
    on_ranking_click(game);
    on_exit_click(game->temp_data.game_textures);
}

void on_pause_click(GAME *game) {
    Rectangle box;
    GAME_TEXTURES game_textures = game->temp_data.game_textures;
    int gap = menu_gap(game_textures);

    box.x = (float) gap * 3 + (float) game_textures.start_game.width + (float) game_textures.load_game.width;
    box.y = (float) gap / 2;
    box.width = (float) game_textures.pause_game.width;
    box.height = (float) game_textures.pause_game.height;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), box)) {
        game->temp_data.selected = PAUSE;
    }
}

void on_ranking_click(GAME *game) {
    GAME_TEXTURES game_textures = game->temp_data.game_textures;
    Rectangle box;
    int gap = menu_gap(game_textures);

    box.x = (float) gap * 4 + (float) game_textures.start_game.width + (float) game_textures.load_game.width +
            (float) game_textures.pause_game.width;
    box.y = (float) gap / 2;
    box.width = (float) game_textures.game_ranking.width;
    box.height = (float) game_textures.game_ranking.height;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), box)) {
        game->temp_data.selected = RANKING;
    }
}

void on_start_click(GAME *game) {
    GAME_TEXTURES game_textures = game->temp_data.game_textures;
    Rectangle box;
    int gap = menu_gap(game_textures);

    box.x = (float) gap;
    box.y = (float) gap / 2;
    box.width = (float) game_textures.start_game.width;
    box.height = (float) game_textures.start_game.height;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), box)) {
        game->temp_data.selected = START;
    }
}
