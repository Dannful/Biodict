#ifndef BIODICT_BODY_C
#define BIODICT_BODY_C

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../header/constants.h"
#include "../header/functions.h"

void game_updates(GAME *game) {
    if (game->temp_data.selected == START) {
        HideCursor();
        game->temp_data.game_time++;

        update_player(game);
        shoot(game);
        update_spiders(game);
        check_mushroom_collision(game);
        check_millipede_bullet_collision(game);
        check_millipede_player_collision(game);
        animate_millipede(game);
    } else {
        ShowCursor();
    }
}

void game_drawing(GAME *game, NAME_EDIT *name_edit) {
    BeginDrawing();
    draw_menu(game, name_edit);
    if (game->temp_data.selected == START) {
        draw_spiders(game->spiders, game->temp_data.game_textures.spider);
        draw_crosshair(game->temp_data.game_textures.crosshair);
        draw_player(&game->player, game->temp_data.game_textures.player);
        draw_mushrooms(game->mushrooms, game->temp_data.game_textures.mushroom);
        draw_millipede(&game->millipede, game->temp_data.game_textures.millipede);
        draw_segments(game);
        draw_bottom_info(*game);
    }
    ClearBackground(BLACK);
    EndDrawing();
}

void game_loop(GAME *game) {
    NAME_EDIT name_edit = {};

    while (!WindowShouldClose()) {
        on_menu_click(game);
        game_updates(game);
        game_drawing(game, &name_edit);
    }
}

static inline float min(float a, float b) {
    if (a > b)
        return a;
    return b;
}

static inline float max(float a, float b) {
    if (a < b)
        return a;
    return b;
}

static inline int menu_gap(GAME_TEXTURES game_textures) {
    int widths = game_textures.start_game.width + game_textures.load_game.width + game_textures.pause_game.width +
                 game_textures.game_ranking.width + game_textures.exit_game.width;
    return (GetScreenWidth() - widths) / (MENU_OPTION_COUNT + 1);
}

static inline int min_screen_height(GAME game) {
    return game.temp_data.game_textures.start_game.height + menu_gap(game.temp_data.game_textures) * 3 / 4;
}

static inline float coerce_in(float value, float min, float max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

static inline Rectangle entity_to_rect(Vector2 position, Texture2D texture) {
    Rectangle rectangle = {position.x, position.y, (float) texture.width, (float) texture.height};
    return rectangle;
}

int CheckCollisionLineRec(Vector2 origin, Vector2 end, Rectangle rectangle) {
    Vector2 point;
    int x, y;

    for (x = (int) rectangle.x; x <= (int) rectangle.x + (int) rectangle.width; x++) {
        for (y = (int) rectangle.y; y <= (int) rectangle.y + (int) rectangle.height; y++) {
            point.x = (float) x;
            point.y = (float) y;
            if (CheckCollisionPointLine(point, origin, end, 1))
                return 1;
        }
    }
    return 0;
}

static inline MOVEMENT calculate_movement(Vector2 origin, Vector2 target) {
    MOVEMENT movement;

    float adjacent_cathetus = target.x - origin.x;
    float opposite_cathetus = origin.y - target.y;
    float hypotenuse = sqrtf(powf(adjacent_cathetus, 2) + powf(opposite_cathetus, 2));

    movement.sinus = opposite_cathetus / hypotenuse;
    movement.cosinus = adjacent_cathetus / hypotenuse;

    return movement;
}

void move(Vector2 *position, MOVEMENT movement, float speed) {
    position->y -= speed * movement.sinus;
    position->x += speed * movement.cosinus;
}

void heal_player(PLAYER *player) {
    if (player->state == FARMER_PARALYSED) {
        player->sick--;
        if (player->sick == 0)
            player->state = FARMER_ACTIVE;
    }
}

void check_mushroom_bullet_collision(GAME *game, int mushroom_index, Rectangle mushroom_rect) {
    if (game->player.shot.frame == game->temp_data.game_time &&
        CheckCollisionLineRec(game->player.position, game->player.shot.target, mushroom_rect)) {
        game->mushrooms[mushroom_index].mushroom_state = MUSHROOM_HARVESTED;
        game->player.harvested++;
        game->mushroom_count--;
        heal_player(&game->player);
    }
}

void check_spider_mushroom_collision(Rectangle mushroom_rect, GAME *game, int mushroom_index) {
    int i;

    for (i = 0; i < SPIDERS; i++) {
        if (!game->spiders[i].dead &&
            CheckCollisionRecs(mushroom_rect,
                               entity_to_rect(game->spiders[i].position, game->temp_data.game_textures.spider))) {
            game->mushrooms[mushroom_index].mushroom_state = MUSHROOM_EATEN;
            game->mushroom_count--;
        }
    }
}

void increase_millipede_size(MILLIPEDE *millipede) {
    if (millipede->size < MAX_SIZE_MILLIPEDE)
        millipede->size++;
}

int check_whole_millipede_collision(MILLIPEDE millipede, Texture2D millipede_texture, Rectangle other) {
    Rectangle milli;

    milli.x = millipede.position.x;
    milli.y = millipede.position.y;

    milli.width = (float) millipede_texture.width;
    milli.height = (float) millipede_texture.height;

    milli.width += (float) millipede_texture.height * (float) millipede.size;

    if (millipede.direction == RIGHT) {
        milli.x += (float) millipede_texture.width;
        milli.x -= milli.width;
    }

    return CheckCollisionRecs(milli, other);
}

void check_millipede_mushroom_collision(Rectangle mushroom_rect, GAME *game, int mushroom_index) {
    if (check_whole_millipede_collision(game->millipede, game->temp_data.game_textures.millipede, mushroom_rect)) {
        game->mushrooms[mushroom_index].mushroom_state = MUSHROOM_EATEN;
        game->millipede.position.y += MILLIPEDE_STEP;
        increase_millipede_size(&game->millipede);
        game->mushroom_count--;
    }
}

void initialize_millipede(GAME *game) {
    int i = GetRandomValue(0, MAX_SIZE_MILLIPEDE);

    game->millipede.position.x = (float) GetRandomValue((int) MILLIPEDE_SPEED,
                                                        GetScreenWidth() - (int) MILLIPEDE_SPEED);
    game->millipede.position.y = (float) min_screen_height(*game);
    game->millipede.size = GetRandomValue(MIN_SIZE_MILLIPEDE, MAX_SIZE_MILLIPEDE);

    if (i <= MAX_SIZE_MILLIPEDE / 2) {
        game->millipede.direction = LEFT;
    } else {
        game->millipede.direction = RIGHT;
    }
}

void kill_millipede(GAME *game) {
    if (game->millipede.size == 0)
        initialize_millipede(game);
}

void kill_player(GAME *game) {
    game->player.lives--;
    game->player.state = FARMER_ACTIVE;
    game->player.sick = 0;
    if (game->player.lives == 0) {
        game->player.state = FARMER_DEAD;
        unload_textures(game->temp_data.game_textures);
        initialize_game(game);
    }
}

void check_mushroom_count(GAME *game) {
    if (game->mushroom_count < game->player.sick)
        kill_player(game);
}

void player_hit(GAME *game, unsigned int sick) {
    if (game->player.state == FARMER_ACTIVE) {
        game->player.state = FARMER_PARALYSED;
        game->player.sick = sick;
        check_mushroom_count(game);
    } else {
        kill_player(game);
    }
    game->player.invulnerability_frames = PLAYER_INVULNERABILITY_SECONDS * GetFPS();
}

void check_millipede_player_collision(GAME *game) {
    if (game->player.invulnerability_frames == 0 &&
        check_whole_millipede_collision(game->millipede, game->temp_data.game_textures.millipede,
                                        entity_to_rect(game->player.position, game->temp_data.game_textures.player))) {
        player_hit(game, game->millipede.size);
        initialize_millipede(game);
    }
}

void check_millipede_bullet_collision(GAME *game) {
    if (game->player.shot.frame == game->temp_data.game_time &&
        CheckCollisionLineRec(game->player.position, game->player.shot.target,
                              entity_to_rect(game->millipede.position, game->temp_data.game_textures.millipede))) {
        game->millipede.size--;
        kill_millipede(game);
    }
}

Vector2 get_segment_position(MILLIPEDE millipede, int index, Texture2D millipede_texture) {
    Vector2 segment_position;
    segment_position.x = millipede.position.x + (float) millipede_texture.width / 2;
    segment_position.y = millipede.position.y + (float) millipede_texture.height / 2;

    float segments_radius = (float) millipede_texture.height / 2;

    if (millipede.direction == LEFT) {
        segment_position.x += 2 * segments_radius * ((float) index + 1.0f);
    } else {
        segment_position.x -= 2 * segments_radius * ((float) index + 1.0f);
    }

    return segment_position;
}

void end_game(GAME *game) {
    if (game->mushroom_count == 0) {
        unload_textures(game->temp_data.game_textures);
        initialize_game(game);
    }
}

void check_mushroom_collision(GAME *game) {
    int i;

    for (i = 0; i < MUSHROOMS; i++) {
        Rectangle mushroom_rec;
        mushroom_rec.x = game->mushrooms[i].position.x;
        mushroom_rec.y = game->mushrooms[i].position.y;
        mushroom_rec.width = (float) game->temp_data.game_textures.mushroom.width;
        mushroom_rec.height = (float) game->temp_data.game_textures.mushroom.height;

        if (game->mushrooms[i].mushroom_state == MUSHROOM_ACTIVE) {
            check_mushroom_bullet_collision(game, i, mushroom_rec);
            check_spider_mushroom_collision(mushroom_rec, game, i);
            check_millipede_mushroom_collision(mushroom_rec, game, i);
            end_game(game);
        }
    }
}

void shoot_animation(PLAYER *player, Texture2D player_texture) {
    if (IsKeyDown(KEY_SPACE)) {
        player->frame_rectangle.y = (float) player_texture.height / 2;
        player->frame_rectangle.height = (float) player_texture.height / 2;
    } else {
        player->frame_rectangle.y = 0;
        player->frame_rectangle.height = (float) player_texture.height / 2;
    }
}

void animate_player(PLAYER *player, Texture2D player_texture) {
    if (player->state == FARMER_ACTIVE) {
        if (IsKeyDown(KEY_UP) && player->position.y >= (float) GetScreenHeight() * 3 / 4)
            player->position.y -= PLAYER_SPEED;
        if (IsKeyDown(KEY_DOWN) && player->position.y <= (float) GetScreenHeight()) player->position.y += PLAYER_SPEED;
        if (IsKeyDown(KEY_LEFT) && player->position.x >= 0) player->position.x -= PLAYER_SPEED;
        if (IsKeyDown(KEY_RIGHT) && player->position.x <= (float) GetScreenWidth()) player->position.x += PLAYER_SPEED;

        shoot_animation(player, player_texture);
    }
}

void maximize_target(SPIDER *spider) {
    if (spider->target.x > spider->target.y) {
        if (spider->target.x < spider->position.x) {
            spider->target.x = 0;
        } else {
            spider->target.x = INFINITY;
        }
    } else {
        if (spider->target.y < spider->position.y) {
            spider->target.y = 0;
        } else {
            spider->target.y = INFINITY;
        }
    }
}

void set_new_spider_target(GAME *game, int index) {
    SPIDER *spider = game->spiders + index;

    spider->target.x = spider->position.x + (float) GetRandomValue(-SPIDER_STEP, SPIDER_STEP);
    spider->target.y = spider->position.y + (float) GetRandomValue(-SPIDER_STEP, SPIDER_STEP);

    maximize_target(spider);

    spider->target.x = coerce_in(spider->target.x, 0,
                                 (float) GetScreenWidth() - (float) game->temp_data.game_textures.spider.width);
    spider->target.y = coerce_in(spider->target.y, (float) min_screen_height(*game),
                                 (float) GetScreenHeight() - (float) game->temp_data.game_textures.spider.height);

    spider->movement = calculate_movement(spider->position, spider->target);
}

void initialize_spider(GAME *game, int index) {
    SPIDER *spider = &game->spiders[index];

    spider->dead = 0;
    spider->position.x = (float) GetScreenWidth() / 2;
    spider->position.y = (float) min_screen_height(*game);
    set_new_spider_target(game, index);
}

void spawn_spider(GAME *game, int index) {
    if (game->temp_data.game_time % (FPS * SPIDER_SPAWN_PERIOD_SECONDS) == 0)
        if (game->spiders[index].dead)
            if (GetRandomValue(0, 100) <= SPIDER_SPAWN_CHANCE)
                initialize_spider(game, index);
}

void draw_spiders(SPIDER spiders[], Texture2D spider_texture) {
    int i;

    for (i = 0; i < SPIDERS; i++)
        if (!spiders[i].dead)
            DrawTextureV(spider_texture, spiders[i].position, WHITE);
}

void move_spider(GAME *game, int index) {
    SPIDER *spider = &game->spiders[index];
    Texture2D spider_texture = game->temp_data.game_textures.spider;

    Rectangle spider_rec = {spider->position.x, spider->position.y, (float) spider_texture.width,
                            (float) spider_texture.height};
    Rectangle target_rec = {spider->target.x, spider->target.y, (float) spider_texture.width,
                            (float) spider_texture.height};

    if (!spider->dead) {
        move(&spider->position, spider->movement, SPIDER_SPEED);
        if (CheckCollisionRecs(target_rec, spider_rec))
            set_new_spider_target(game, index);
    }
}

void check_bullet_spider_collision(unsigned int time, SPIDER *spider, Texture2D spider_texture, PLAYER player) {
    if (!spider->dead &&
        time == player.shot.frame &&
        CheckCollisionLineRec(player.position, player.shot.target, entity_to_rect(spider->position, spider_texture)))
        spider->dead = 1;
}

void check_spider_player_collision(SPIDER spider, GAME *game) {
    if (CheckCollisionRecs(entity_to_rect(spider.position, game->temp_data.game_textures.spider),
                           entity_to_rect(game->player.position, game->temp_data.game_textures.player)) &&
        game->player.invulnerability_frames <= 0)
        player_hit(game, PLAYER_HEAL_AMOUNT);
}

void update_player(GAME *game) {
    if (game->player.invulnerability_frames > 0)
        game->player.invulnerability_frames--;
    animate_player(&game->player, game->temp_data.game_textures.player);
}

void update_spiders(GAME *game) {
    int i = 0;

    SPIDER_WITH_TEXTURE spider_with_texture;
    spider_with_texture.spider_texture = game->temp_data.game_textures.spider;

    while (i < SPIDERS) {
        spider_with_texture.spider = game->spiders[i];
        spawn_spider(game, i);
        move_spider(game, i);
        check_spider_player_collision(game->spiders[i], game);
        check_bullet_spider_collision(game->temp_data.game_time, game->spiders + i,
                                      game->temp_data.game_textures.spider, game->player);
        i++;
    }
}

void shoot(GAME *game) {
    if (IsKeyDown(KEY_SPACE) &&
        (float) game->temp_data.game_time - (float) game->player.shot.last_bullet_frame >=
        (float) GetFPS() * PLAYER_SHOOT_COOLDOWN_SECONDS) {
        game->player.shot.target = GetMousePosition();
        game->player.shot.frame = game->temp_data.game_time;
        DrawLineV(game->player.position, game->player.shot.target, PLAYER_SHOT_COLOR);
        game->player.shot.last_bullet_frame = game->temp_data.game_time;
        game->player.remaining_bullets--;
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

    for (i = 0; i < MUSHROOMS; i++)
        if (mushrooms[i].mushroom_state == MUSHROOM_ACTIVE)
            DrawTextureV(mushroom_texture, mushrooms[i].position, WHITE);
}

void unload_textures(GAME_TEXTURES game_textures) {
    int i;
    int n = sizeof(GAME_TEXTURES) / sizeof(Texture2D);

    Texture2D *textures = (Texture2D *) &game_textures;

    for (i = 0; i < n; i++)
        UnloadTexture(textures[i]);
}

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

void enable_editing(NAME_EDIT *name_edit, Rectangle text_box) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), text_box))
        name_edit->editing = 1;
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

void save_to_leaderboard_position(GAME *game, int position) {
    strcpy(game->temp_data.records[position].name, game->player.name);
    game->temp_data.records[position].score = game->player.harvested;
}

void check_last_position(GAME *game, int inserted) {
    if (!inserted && game->temp_data.records[PLAYER_RECORD_COUNT - 1].score < game->player.harvested)
        save_to_leaderboard_position(game, PLAYER_RECORD_COUNT - 1);
}

void switch_positions(RECORD records[], int i, int j) {
    char name_aux[MAX_STRING_LENGTH];
    unsigned int score_aux;

    strcpy(name_aux, records[i].name);
    score_aux = records[i].score;

    strcpy(records[i].name, records[j].name);
    records[i].score = records[j].score;
    strcpy(records[j].name, name_aux);
    records[j].score = score_aux;
}

void sort_records(GAME *game) {
    int i, j;

    for (i = 0; i < PLAYER_RECORD_COUNT; i++)
        for (j = 0; j < PLAYER_RECORD_COUNT - i - 1; j++)
            if (game->temp_data.records[j].name[0] * game->temp_data.records[j + 1].name[0] != 0 &&
                game->temp_data.records[j].score < game->temp_data.records[j + 1].score)
                switch_positions(game->temp_data.records, j, j + 1);
}

void save_to_leaderboard(GAME *game) {
    int i = 0;
    int inserted = 0;

    while (i < PLAYER_RECORD_COUNT && !inserted) {
        if (game->temp_data.records[i].name[0] == '\0' ||
            strcmp(game->player.name, game->temp_data.records[i].name) == 0 &&
            game->temp_data.records[i].score < game->player.harvested) {
            save_to_leaderboard_position(game, i);
            inserted = 1;
        }
        i++;
    }
    check_last_position(game, inserted);
    sort_records(game);
}

void print_to_file(FILE *file, RECORD records[]) {
    int i = 0;

    while (i < PLAYER_RECORD_COUNT && records[i].name[0] != '\0') {
        if (i == 0)
            fprintf(file, "%s;%d", records[i].name, records[i].score);
        else
            fprintf(file, "\n%s;%d", records[i].name, records[i].score);
        i++;
    }
}

void save_to_leaderboard_file(RECORD records[]) {
    FILE *file = fopen(RECORDS_FILE_NAME, "w");

    if (file) {
        print_to_file(file, records);
        fclose(file);
    }
}

int save_game(GAME *game) {
    int saved = 0;
    char file_name[MAX_STRING_LENGTH + sizeof(DATA_FILE_EXTENSION)];
    FILE *file;

    sprintf(file_name, "%s.%s", game->player.name, DATA_FILE_EXTENSION);
    file = fopen(file_name, "wb");

    if (file) {
        saved = (int) fwrite(game, sizeof(GAME) - sizeof(TEMP_DATA), 1,
                             file);
        fclose(file);
    }
    save_to_leaderboard(game);
    save_to_leaderboard_file(game->temp_data.records);
    return saved;
}

void draw_save_menu(GAME *game, NAME_EDIT *name_edit) {
    if (game->temp_data.selected == PAUSE)
        draw_input_requirement(game, name_edit, (void (*)(GAME *)) &save_game);
}

int read_game(GAME *game) {
    int read = 0;
    char file_name[MAX_STRING_LENGTH + sizeof(DATA_FILE_EXTENSION)];
    FILE *file;

    sprintf(file_name, "%s.%s", game->player.name, DATA_FILE_EXTENSION);
    file = fopen(file_name, "rb");

    if (file) {
        read = (int) fread(game,
                           sizeof(GAME) - sizeof(MENU_OPTION) - sizeof(GAME_TEXTURES) - sizeof(int) -
                           PLAYER_RECORD_COUNT * sizeof(RECORD),
                           1, file); // Exclude last five fields from structure
        fclose(file);
    }
    return read;
}

void draw_load_menu(GAME *game, NAME_EDIT *name_edit) {
    if (game->temp_data.selected == LOAD)
        draw_input_requirement(game, name_edit, (void (*)(GAME *)) &read_game);
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

void draw_ranking(GAME game) {
    int i = 0;
    char text[MAX_STRING_LENGTH];

    if (game.temp_data.selected == RANKING) {
        while (i < PLAYER_RECORD_COUNT && game.temp_data.records[i].name[0] != '\0') {
            sprintf(text, "%d. %s: %d", i + 1, game.temp_data.records[i].name, game.temp_data.records[i].score);
            DrawText(text, menu_gap(game.temp_data.game_textures), min_screen_height(game) + i * MENU_FONT, MENU_FONT,
                     WHITE);
            i++;
        }
    }
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

void draw_player(PLAYER *player, Texture2D player_texture) {
    float angle = atan2f(GetMousePosition().y - player->position.y, GetMousePosition().x - player->position.x);
    angle = angle / PI * 180;

    Rectangle source = {player->frame_rectangle.x, player->frame_rectangle.y, player->frame_rectangle.width,
                        player->frame_rectangle.height};
    Rectangle destination = {player->position.x, player->position.y, (float) player->frame_rectangle.width,
                             (float) player->frame_rectangle.height};
    Vector2 origin = {(float) player->frame_rectangle.width, (float) player->frame_rectangle.height};
    DrawTexturePro(player_texture, source, destination, origin,
                   angle,
                   player->state == FARMER_PARALYSED ? RED : WHITE);
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

void initialize_mushrooms(GAME *game) {
    int i;

    for (i = 0; i < MUSHROOMS; i++) {
        game->mushrooms[i].mushroom_state = MUSHROOM_ACTIVE;

        game->mushrooms[i].position.x = (float) GetRandomValue(min_screen_height(*game),
                                                               GetScreenWidth() -
                                                               game->temp_data.game_textures.mushroom.width);
        game->mushrooms[i].position.y = (float) GetRandomValue(min_screen_height(*game),
                                                               GetScreenHeight() -
                                                               game->temp_data.game_textures.mushroom.height);
    }
}

void initialize_spiders(GAME *game) {
    game->spiders[0].dead = 1;
    game->spiders[1].dead = 1;
}

void read_record_lines(FILE *file, GAME *game) {
    int i = 0;
    char buffer[MAX_STRING_LENGTH];
    char *token;

    while (fgets(buffer, MAX_STRING_LENGTH, file)) {
        token = strtok(buffer, RECORDS_SEPARATOR);
        strcpy(game->temp_data.records[i].name, token);
        game->temp_data.records[i].score = strtol(strtok(NULL, RECORDS_SEPARATOR), &token, 10);
        i++;
    }
}

void load_records(GAME *game) {
    FILE *f = fopen(RECORDS_FILE_NAME, "r");

    if (f) {
        read_record_lines(f, game);
        fclose(f);
    }
}

void initialize_records(RECORD records[]) {
    int i;

    for (i = 0; i < PLAYER_RECORD_COUNT; i++) {
        records[i].score = 0;
        records[i].name[0] = '\0';
    }
}

void initialize_game(GAME *game) {
    game->temp_data.selected = NONE;
    game->temp_data.game_time = 0;
    game->mushroom_count = MUSHROOMS;

    initialize_records(game->temp_data.records);
    initialize_textures(&game->temp_data.game_textures);
    load_records(game);
    initialize_player(&game->player, game->temp_data.game_textures.player);
    initialize_mushrooms(game);
    initialize_millipede(game);
    initialize_spiders(game);
}

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

void on_menu_click(GAME *game) {
    on_start_click(game);
    on_load_click(game);
    on_pause_click(game);
    on_ranking_click(game);
    on_exit_click(game->temp_data.game_textures);
}

DIRECTION collision_millipede(MILLIPEDE *millipede) {
    if (millipede->position.x <= 0) {
        return RIGHT;
    } else if (millipede->position.x >= (float) GetScreenWidth()) {
        return LEFT;
    }
    return millipede->direction;
}

void millipede_out_of_bounds(GAME *game) {
    if (game->millipede.position.y + (float) game->temp_data.game_textures.millipede.height >=
        (float) GetScreenHeight())
        initialize_millipede(game);
}

void animate_millipede(GAME *game) {
    DIRECTION collision = collision_millipede(&game->millipede);

    millipede_out_of_bounds(game);
    if (collision == game->millipede.direction) {
        if (game->millipede.direction == LEFT) {
            game->millipede.position.x -= MILLIPEDE_SPEED;
        } else if (game->millipede.direction == RIGHT) {
            game->millipede.position.x += MILLIPEDE_SPEED;
        }
    } else {
        game->millipede.position.y += MILLIPEDE_STEP;
        game->millipede.direction = collision;
    }
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

void draw_segments(GAME *game) {
    int i;
    float segments_radius = (float) game->temp_data.game_textures.millipede.height / 2;

    for (i = 0; i < game->millipede.size; i++)
        DrawCircleV(get_segment_position(game->millipede, i, game->temp_data.game_textures.millipede), segments_radius,
                    GREEN);
}

#endif