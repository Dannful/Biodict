#include "functions/initialization.h"
#include "functions/io.h"
#include "functions/graphics.h"
#include "functions/game.h"

#include <string.h>
#include <time.h>

void initialize_game(GAME *game) {
    SetRandomSeed(time(0));

    game->temp_data.selected = NONE;
    game->temp_data.game_time = 0;
    game->mushroom_count = MUSHROOMS;

    initialize_records(game->temp_data.records);
    initialize_textures(&game->temp_data.game_textures);
    load_records(game->temp_data.records);
    initialize_player(&game->player, game->temp_data.game_textures.player);
    initialize_mushrooms(game);
    initialize_millipede(&game->millipede, game->temp_data.game_textures);
    initialize_spiders(game->spiders);
}

void initialize_millipede(MILLIPEDE *millipede, GAME_TEXTURES game_textures) {
    int i = GetRandomValue(0, MAX_SIZE_MILLIPEDE);

    millipede->position.x = (float) GetRandomValue((int) MILLIPEDE_SPEED,
                                                   GetScreenWidth() - (int) MILLIPEDE_SPEED);
    millipede->position.y = (float) min_screen_height(game_textures);
    millipede->size = GetRandomValue(MIN_SIZE_MILLIPEDE, MAX_SIZE_MILLIPEDE);

    if (i <= MAX_SIZE_MILLIPEDE / 2) {
        millipede->direction = LEFT;
    } else {
        millipede->direction = RIGHT;
    }
}

void initialize_mushrooms(GAME *game) {
    int i;

    for (i = 0; i < MUSHROOMS; i++) {
        game->mushrooms[i].mushroom_state = MUSHROOM_ACTIVE;

        game->mushrooms[i].position.x = (float) GetRandomValue(min_screen_height(game->temp_data.game_textures),
                                                               GetScreenWidth() -
                                                               game->temp_data.game_textures.mushroom.width);
        game->mushrooms[i].position.y = (float) GetRandomValue(min_screen_height(game->temp_data.game_textures),
                                                               GetScreenHeight() -
                                                               game->temp_data.game_textures.mushroom.height);
    }
}

void initialize_player(PLAYER *player, Texture2D player_texture) {
    player->shot.target.x = player->shot.target.y = 0;
    player->shot.frame = player->shot.last_bullet_frame = 0;
    player->state = FARMER_ACTIVE;
    player->invulnerability_frames = 0;
    player->position.x = (float) GetScreenWidth() / 2;
    player->position.y = (float) GetScreenHeight() * 3 / 4;
    player->remaining_bullets = PLAYER_BULLETS;
    player->lives = PLAYER_LIVES;
    player->harvested = 0;
    strcpy(player->name, "");

    player->frame_rectangle.x = player->frame_rectangle.y = 0;
    player->frame_rectangle.width = (float) player_texture.width;
    player->frame_rectangle.height = (float) player_texture.height / 2;
}

void initialize_records(RECORD records[]) {
    int i;

    for (i = 0; i < PLAYER_RECORD_COUNT; i++) {
        records[i].score = 0;
        records[i].name[0] = '\0';
    }
}

void initialize_spider(SPIDER spiders[], GAME_TEXTURES game_textures, int index) {
    SPIDER *spider = spiders + index;

    spider->dead = 0;
    spider->position.x = (float) GetScreenWidth() / 2;
    spider->position.y = (float) min_screen_height(game_textures);
    set_new_spider_target(spiders, game_textures, index);
}

void initialize_spiders(SPIDER spiders[]) {
    spiders[0].dead = 1;
    spiders[1].dead = 1;
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
    ImageRotateCW(&player_image);
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

    /* Menu */

    Image start = ImageText(MENU_START, MENU_FONT, WHITE);
    game_textures->start_game = LoadTextureFromImage(start);
    UnloadImage(start);

    Image load = ImageText(MENU_LOAD, MENU_FONT, WHITE);
    game_textures->load_game = LoadTextureFromImage(load);
    UnloadImage(load);

    Image pause = ImageText(MENU_PAUSE, MENU_FONT, WHITE);
    game_textures->pause_game = LoadTextureFromImage(pause);
    UnloadImage(pause);

    Image ranking = ImageText(MENU_RANKING, MENU_FONT, WHITE);
    game_textures->game_ranking = LoadTextureFromImage(ranking);
    UnloadImage(ranking);

    Image exit = ImageText(MENU_EXIT, MENU_FONT, WHITE);
    game_textures->exit_game = LoadTextureFromImage(exit);
    UnloadImage(exit);

    Image paused_hint = ImageText(PAUSED_MENU_TEXT, PAUSED_MENU_FONT_SIZE, WHITE);
    game_textures->paused_hint = LoadTextureFromImage(paused_hint);
    UnloadImage(paused_hint);

    /* Spider */

    Image spider_image = LoadImage(SPIDER_IMAGE_PATH);
    game_textures->spider = LoadTextureFromImage(spider_image);
    UnloadImage(spider_image);

    /* Millipede */

    Image millipede_image = LoadImage(MILLIPEDE_IMAGE_PATH);
    ImageResize(&millipede_image, millipede_image.width / 4, millipede_image.height / 4);
    game_textures->millipede = LoadTextureFromImage(millipede_image);
    UnloadImage(millipede_image);
}

void initialize_window() {
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);
}