#include "functions/collision.h"

#include "functions/game.h"
#include "functions/initialization.h"

void check_millipede_player_collision(GAME *game) {
    if (game->player.invulnerability_frames == 0 &&
        check_whole_millipede_collision(game->millipede, game->temp_data.game_textures.millipede,
                                        entity_to_rect(game->player.position, game->temp_data.game_textures.player))) {
        player_hit(game, game->millipede.size);
        initialize_millipede(&game->millipede, game->temp_data.game_textures);
    }
}

void check_millipede_bullet_collision(GAME *game) {
    if (game->player.shot.frame == game->temp_data.game_time &&
        CheckCollisionLineRec(game->player.position, game->player.shot.target,
                              entity_to_rect(game->millipede.position, game->temp_data.game_textures.millipede))) {
        game->millipede.size--;
        kill_millipede(&game->millipede, game->temp_data.game_textures);
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

void check_millipede_mushroom_collision(Rectangle mushroom_rect, GAME *game, int mushroom_index) {
    if (check_whole_millipede_collision(game->millipede, game->temp_data.game_textures.millipede, mushroom_rect)) {
        game->mushrooms[mushroom_index].mushroom_state = MUSHROOM_EATEN;
        game->millipede.position.y += MILLIPEDE_STEP;
        increase_millipede_size(&game->millipede);
        game->mushroom_count--;
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

DIRECTION collision_millipede(MILLIPEDE *millipede) {
    if (millipede->position.x <= 0) {
        return RIGHT;
    } else if (millipede->position.x >= (float) GetScreenWidth()) {
        return LEFT;
    }
    return millipede->direction;
}

static inline Rectangle entity_to_rect(Vector2 position, Texture2D texture) {
    Rectangle rectangle = {position.x, position.y, (float) texture.width, (float) texture.height};
    return rectangle;
}