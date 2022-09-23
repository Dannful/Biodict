#ifndef BIODICT_COLLISION_H
#define BIODICT_COLLISION_H

#include "structures.h"

/**
 * Checks if there was a collision between the given spider
 * and the player's bullet
 * @param time current game time
 * @param spider the reference to the spider
 * @param spider_texture the spider's sprite
 * @param player the player
 */
void check_bullet_spider_collision(unsigned int time, SPIDER *spider, Texture2D spider_texture, PLAYER player);

/**
 * Checks if there was a collision between
 * the millipede and the bullet
 * @param game the reference to the game structure containing the player's bullet and the millipede
 */
void check_millipede_bullet_collision(GAME *game);

/**
 * Checks if there was a collision between the given mushroom collider
 * and the millipede
 * @param mushroom_rect the mushroom's collider
 * @param game the reference to the game structure containing the mushroom collection and the millipede
 * @param mushroom_index the index of the mushroom
 */
void check_millipede_mushroom_collision(Rectangle mushroom_rect, GAME *game, int mushroom_index);

/**
 * Checks if there was a collision between the player
 * and the millipede
 * @param game the reference to the game structure containing the player and the millipede
 */
void check_millipede_player_collision(GAME *game);

/**
 * Checks if there was collision between a mushroom and
 * the player's bullet
 * @param game the reference to the game structure containing the player's bullet and the mushroom collection
 * @param mushroom_index the index of the mushroom
 * @param mushroom_rect the collider of the mushroom
 */
void check_mushroom_bullet_collision(GAME *game, int mushroom_index, Rectangle mushroom_rect);

/**
 * Checks collision between the entities and the mushrooms
 * @param game the reference to the structure containing all the entities and the mushrooms
 */
void check_mushroom_collision(GAME *game);

/**
 * Checks if there was a collision between a spider and
 * a mushroom
 * @param mushroom_rect the collider of the mushroom
 * @param game the reference to the game structure containing the mushroom collection
 * @param mushroom_index the index of the mushroom
 */
void check_spider_mushroom_collision(Rectangle mushroom_rect, GAME *game, int mushroom_index);

/**
 * Checks if there was a collision between a spider
 * and the player
 * @param spider the spider
 * @param game the reference to the game structure containing the player and the spider collection
 */
void check_spider_player_collision(SPIDER spider, GAME *game);

/**
 * Checks if the given collider hit any part of the millipede, including segments
 * @param millipede the millipede
 * @param millipede_texture the sprite of the millipede
 * @param other the collider
 * @return
 */
int check_whole_millipede_collision(MILLIPEDE millipede, Texture2D millipede_texture, Rectangle other);

/**
 * Checks if there was a collision between a line and
 * a collider
 * @param origin the starting point of the line
 * @param end the ending point of the line
 * @param rectangle the collider
 * @return true if there was a collision
 */
int CheckCollisionLineRec(Vector2 origin, Vector2 end, Rectangle rectangle);

/**
 * Checks if there was a collision between the millipede
 * and any wall
 * @param millipede the reference to the millipede
 * @return the direction the millipede must currently face
 */
DIRECTION collision_millipede(MILLIPEDE *millipede);

/**
 * Converts a position and a texture to a collider
 * @param position the position of the entity
 * @param texture the sprite of the entity
 * @return the collider
 */
static inline Rectangle entity_to_rect(Vector2 position, Texture2D texture);

#endif
