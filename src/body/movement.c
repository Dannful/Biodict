#include "functions/movement.h"
#include "functions/game.h"
#include "functions/collision.h"

#include <math.h>

void animate_millipede(MILLIPEDE *millipede, GAME_TEXTURES game_textures) {
    DIRECTION collision = collision_millipede(millipede);

    millipede_out_of_bounds(millipede, game_textures);
    if (collision == millipede->direction) {
        if (millipede->direction == LEFT) {
            millipede->position.x -= MILLIPEDE_SPEED;
        } else if (millipede->direction == RIGHT) {
            millipede->position.x += MILLIPEDE_SPEED;
        }
    } else {
        millipede->position.y += MILLIPEDE_STEP;
        millipede->direction = collision;
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

MOVEMENT calculate_movement(Vector2 origin, Vector2 target) {
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

void move_spider(SPIDER spiders[], GAME_TEXTURES game_textures, int index) {
    SPIDER *spider = spiders + index;

    Rectangle spider_rec = {spider->position.x, spider->position.y, (float) game_textures.spider.width,
                            (float) game_textures.spider.height};
    Rectangle target_rec = {spider->target.x, spider->target.y, (float) game_textures.spider.width,
                            (float) game_textures.spider.height};

    if (!spider->dead) {
        move(&spider->position, spider->movement, SPIDER_SPEED);
        if (CheckCollisionRecs(target_rec, spider_rec))
            set_new_spider_target(spiders, game_textures, index);
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
