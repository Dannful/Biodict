#include "functions/graphics.h"
#include "functions/game.h"
#include "functions/io.h"

#include <stdio.h>
#include <math.h>

void delete_last_name_character(GAME *game, NAME_EDIT *name_edit) {
    if (IsKeyPressed(KEY_BACKSPACE))
        game->player.name[--name_edit->count] = (char) 0;
}

void disable_editing(GAME *game, NAME_EDIT *name_edit, void (*on_enter)(GAME *)) {
    if (IsKeyDown(KEY_ENTER)) {
        name_edit->editing = 0;
        if (on_enter != NULL)
            on_enter(game);
    }
}

void draw_bottom_info(GAME game) {
    char bullets[MAX_STRING_LENGTH];
    char lives[MAX_STRING_LENGTH];
    char harvested[MAX_STRING_LENGTH];
    char mushrooms[MAX_STRING_LENGTH];

    sprintf(bullets, REMAINING_BULLETS, game.player.remaining_bullets);
    sprintf(lives, REMAINING_LIVES, game.player.lives);
    sprintf(harvested, HARVESTED_MUSHROOMS, game.player.harvested);
    sprintf(mushrooms, REMAINING_MUSHROOMS, game.mushroom_count);

    DrawText(mushrooms, MENU_FONT, GetScreenHeight() - 4 * MENU_FONT, MENU_FONT, WHITE);
    DrawText(harvested, MENU_FONT, GetScreenHeight() - 3 * MENU_FONT, MENU_FONT, WHITE);
    DrawText(lives, MENU_FONT, GetScreenHeight() - 2 * MENU_FONT, MENU_FONT, WHITE);
    DrawText(bullets, MENU_FONT, GetScreenHeight() - MENU_FONT, MENU_FONT, WHITE);
}

void draw_crosshair(Texture2D crosshair_texture) {
    Vector2 crosshair_position;
    crosshair_position.x = (float) GetMouseX() - (float) crosshair_texture.width / 2;
    crosshair_position.y = (float) GetMouseY() - (float) crosshair_texture.height / 2;

    DrawTextureV(crosshair_texture, crosshair_position, WHITE);
}

void draw_input_requirement(GAME *game, NAME_EDIT *name_edit, void (*on_enter)(GAME *)) {
    float gap = (float) menu_gap(game->temp_data.game_textures);
    Vector2 text_position = {gap, (float) game->temp_data.game_textures.start_game.height + gap};
    Rectangle text_box = {gap, text_position.y + (float) game->temp_data.game_textures.paused_hint.height + gap / 4,
                          (float) GetScreenWidth() - 2 * gap,
                          2 * PAUSED_MENU_FONT_SIZE};
    if (name_edit->editing)
        DrawRectangle((int) text_box.x - 1, (int) text_box.y - 1, (int) text_box.width + 2, (int) text_box.height + 2,
                      RED);
    DrawTexture(game->temp_data.game_textures.paused_hint, (int) text_position.x, (int) text_position.y, WHITE);
    DrawRectangleRec(text_box, WHITE);
    DrawText(game->player.name, (int) text_box.x + PAUSED_MENU_FONT_SIZE / 2,
             (int) text_box.y + PAUSED_MENU_FONT_SIZE / 2, PAUSED_MENU_FONT_SIZE, MAROON);
    type_name(game, name_edit, on_enter);
    enable_editing(name_edit, text_box);
}

void draw_load_menu(GAME *game, NAME_EDIT *name_edit) {
    if (game->temp_data.selected == LOAD)
        draw_input_requirement(game, name_edit, (void (*)(GAME *)) &read_game);
}

void draw_menu(GAME *game, NAME_EDIT *name_edit) {
    GAME_TEXTURES game_textures = game->temp_data.game_textures;
    int posX = 0;
    int gap = menu_gap(game_textures);

    DrawTexture(game_textures.start_game, posX += gap, gap / 2, game->temp_data.selected == START ? RED : WHITE);
    DrawTexture(game_textures.load_game, posX += game_textures.start_game.width + gap, gap / 2,
                game->temp_data.selected == LOAD ? RED : WHITE);
    DrawTexture(game_textures.pause_game, posX += game_textures.load_game.width + gap, gap / 2,
                game->temp_data.selected == PAUSE ? RED : WHITE);
    DrawTexture(game_textures.game_ranking, posX += game_textures.pause_game.width + gap, gap / 2,
                game->temp_data.selected == RANKING ? RED : WHITE);
    DrawTexture(game_textures.exit_game, posX + game_textures.game_ranking.width + gap, gap / 2, WHITE);

    draw_load_menu(game, name_edit);
    draw_save_menu(game, name_edit);
    draw_ranking(*game);
}

void draw_millipede(MILLIPEDE *millipede, Texture2D millipede_texture) {
    Vector2 position = millipede->position;

    if (millipede->direction == LEFT) {
        position.x += (float) millipede_texture.width;
        position.y += (float) millipede_texture.height;
        DrawTextureEx(millipede_texture, position, 180, 1, WHITE);
    } else if (millipede->direction == RIGHT) {
        DrawTextureEx(millipede_texture, millipede->position, 0, 1, WHITE);
    }
}

void draw_mushrooms(MUSHROOM mushrooms[], Texture2D mushroom_texture) {
    int i;

    for (i = 0; i < MUSHROOMS; i++)
        if (mushrooms[i].mushroom_state == MUSHROOM_ACTIVE)
            DrawTextureV(mushroom_texture, mushrooms[i].position, WHITE);
}

void draw_player(PLAYER player, Texture2D player_texture) {
    float angle = atan2f(GetMousePosition().y - player.position.y, GetMousePosition().x - player.position.x);
    angle = angle / PI * 180;

    Rectangle source = {player.frame_rectangle.x, player.frame_rectangle.y, player.frame_rectangle.width,
                        player.frame_rectangle.height};
    Rectangle destination = {player.position.x, player.position.y, (float) player.frame_rectangle.width,
                             (float) player.frame_rectangle.height};
    Vector2 origin = {(float) player.frame_rectangle.width, (float) player.frame_rectangle.height};
    DrawTexturePro(player_texture, source, destination, origin,
                   angle,
                   player.state == FARMER_PARALYSED ? RED : WHITE);
}

void draw_ranking(GAME game) {
    int i = 0;
    char text[MAX_STRING_LENGTH];

    if (game.temp_data.selected == RANKING) {
        while (i < PLAYER_RECORD_COUNT && game.temp_data.records[i].name[0] != '\0') {
            sprintf(text, "%d. %s: %d", i + 1, game.temp_data.records[i].name, game.temp_data.records[i].score);
            DrawText(text, menu_gap(game.temp_data.game_textures),
                     min_screen_height(game.temp_data.game_textures) + i * MENU_FONT, MENU_FONT,
                     WHITE);
            i++;
        }
    }
}

void draw_save_menu(GAME *game, NAME_EDIT *name_edit) {
    if (game->temp_data.selected == PAUSE)
        draw_input_requirement(game, name_edit, (void (*)(GAME *)) &save_game);
}

void draw_segments(GAME *game) {
    int i;
    float segments_radius = (float) game->temp_data.game_textures.millipede.height / 2;

    for (i = 0; i < game->millipede.size; i++)
        DrawCircleV(get_segment_position(game->millipede, i, game->temp_data.game_textures.millipede), segments_radius,
                    GREEN);
}

void draw_spiders(SPIDER spiders[], Texture2D spider_texture) {
    int i;

    for (i = 0; i < SPIDERS; i++)
        if (!spiders[i].dead)
            DrawTextureV(spider_texture, spiders[i].position, WHITE);
}

void enable_editing(NAME_EDIT *name_edit, Rectangle text_box) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), text_box))
        name_edit->editing = 1;
}

void game_drawing(GAME *game, NAME_EDIT *name_edit) {
    BeginDrawing();
    draw_menu(game, name_edit);
    if (game->temp_data.selected == START) {
        draw_spiders(game->spiders, game->temp_data.game_textures.spider);
        draw_crosshair(game->temp_data.game_textures.crosshair);
        draw_player(game->player, game->temp_data.game_textures.player);
        draw_mushrooms(game->mushrooms, game->temp_data.game_textures.mushroom);
        draw_millipede(&game->millipede, game->temp_data.game_textures.millipede);
        draw_segments(game);
        draw_bottom_info(*game);
    }
    ClearBackground(BLACK);
    EndDrawing();
}

int menu_gap(GAME_TEXTURES game_textures) {
    int widths = game_textures.start_game.width + game_textures.load_game.width + game_textures.pause_game.width +
                 game_textures.game_ranking.width + game_textures.exit_game.width;
    return (GetScreenWidth() - widths) / (MENU_OPTION_COUNT + 1);
}

int min_screen_height(GAME_TEXTURES game_textures) {
    return 4 * menu_gap(game_textures) / 3 + game_textures.start_game.height;
}

void type_name(GAME *game, NAME_EDIT *name_edit, void (*on_enter)(GAME *)) {
    int key = GetKeyPressed();

    if (name_edit->editing) {
        if ((key >= 32) && (key <= 125) && (name_edit->count < MAX_STRING_LENGTH)) {
            game->player.name[name_edit->count] = (char) key;
            game->player.name[name_edit->count + 1] = (char) 0;
            name_edit->count++;
        }
        disable_editing(game, name_edit, on_enter);
        delete_last_name_character(game, name_edit);
    }
}

void unload_textures(GAME_TEXTURES game_textures) {
    int i;
    int n = sizeof(GAME_TEXTURES) / sizeof(Texture2D);

    Texture2D *textures = (Texture2D *) &game_textures;

    for (i = 0; i < n; i++)
        UnloadTexture(textures[i]);
}
