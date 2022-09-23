#include <math.h>

#include "functions/game.h"
#include "functions/graphics.h"
#include "functions/initialization.h"
#include "functions/events.h"
#include "functions/collision.h"
#include "functions/movement.h"
#include "functions/calculations.h"

void check_mushroom_count(GAME *game) {
    if (game->mushroom_count < game->player.sick)
        kill_player(game);
}

void end_game(GAME *game) {
    if (game->mushroom_count == 0) {
        unload_textures(game->temp_data.game_textures);
        initialize_game(game);
    }
}

void game_loop(GAME *game) {
    NAME_EDIT name_edit = {};

    while (!WindowShouldClose()) {
        on_menu_click(game);
        game_updates(game);
        game_drawing(game, &name_edit);
    }
}

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
        animate_millipede(&game->millipede, game->temp_data.game_textures);
    } else {
        ShowCursor();
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

void heal_player(PLAYER *player) {
    if (player->state == FARMER_PARALYSED) {
        player->sick--;
        if (player->sick == 0)
            player->state = FARMER_ACTIVE;
    }
}

void increase_millipede_size(MILLIPEDE *millipede) {
    if (millipede->size < MAX_SIZE_MILLIPEDE)
        millipede->size++;
}

void kill_millipede(MILLIPEDE *millipede, GAME_TEXTURES game_textures) {
    if (millipede->size == 0)
        initialize_millipede(millipede, game_textures);
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

void millipede_out_of_bounds(MILLIPEDE *millipede, GAME_TEXTURES game_textures) {
    if (millipede->position.y + (float) game_textures.millipede.height >=
        (float) GetScreenHeight())
        initialize_millipede(millipede, game_textures);
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

void set_new_spider_target(SPIDER spiders[], GAME_TEXTURES game_textures, int index) {
    SPIDER *spider = spiders + index;

    spider->target.x = spider->position.x + (float) GetRandomValue(-SPIDER_STEP, SPIDER_STEP);
    spider->target.y = spider->position.y + (float) GetRandomValue(-SPIDER_STEP, SPIDER_STEP);

    maximize_target(spider);

    spider->target.x = coerce_in(spider->target.x, 0,
                                 (float) GetScreenWidth() - (float) game_textures.spider.width);
    spider->target.y = coerce_in(spider->target.y, (float) min_screen_height(game_textures),
                                 (float) GetScreenHeight() - (float) game_textures.spider.height);

    spider->movement = calculate_movement(spider->position, spider->target);
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

void spawn_spider(SPIDER spiders[], GAME_TEXTURES game_textures, int index, unsigned int game_time) {
    if (game_time % (FPS * SPIDER_SPAWN_PERIOD_SECONDS) == 0)
        if (spiders[index].dead)
            if (GetRandomValue(0, 100) <= SPIDER_SPAWN_CHANCE)
                initialize_spider(spiders, game_textures, index);
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
        spawn_spider(game->spiders, game->temp_data.game_textures, i, game->temp_data.game_time);
        move_spider(game->spiders, game->temp_data.game_textures, i);
        check_spider_player_collision(game->spiders[i], game);
        check_bullet_spider_collision(game->temp_data.game_time, game->spiders + i,
                                      game->temp_data.game_textures.spider, game->player);
        i++;
    }
}
