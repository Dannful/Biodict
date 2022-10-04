#ifndef BIODICT_GAME_H
#define BIODICT_GAME_H

#include "structures.h"

/**
 * Checks if the player can manage to heal with the remaining mushrooms or kills it
 * @param game the reference to the structure containing the mushroom collection and the player
 */
void check_mushroom_count(GAME *game);

/**
 * Checks if the game should end, and, if positive, ends it
 * @param game the reference to the game structure
 */
void end_game(GAME *game);

/**
 * The main game loop
 * @param game the reference to the game structure
 */
void game_loop();

/**
 * The main game updates
 * @param game the reference to the game structure
 */
void game_updates(GAME *game);

/**
 * Returns the center of the millipede's segment circle at the given index
 * @param millipede the millipede
 * @param index the offset
 * @param millipede_texture the millipede's texture
 * @return the position
 */
Vector2 get_segment_position(MILLIPEDE millipede, int index, Texture2D millipede_texture);

/**
 * Decreases the player's sickness and restores it to full health if possible
 * @param player the reference to the player
 */
void heal_player(PLAYER *player);

/**
 * Increases the millipede's amount of segments, if possible
 * @param millipede the reference to the millipede
 */
void increase_millipede_size(MILLIPEDE *millipede);

/**
 * Checks if the millipede has no segments and, if positive, kills it
 * @param millipede the reference to the millipede
 * @param game_textures the structure holding the game's textures
 */
void kill_millipede(MILLIPEDE *millipede, GAME_TEXTURES game_textures);

/**
 * Kills the player and ends the game if it ran out of lives
 * @param game the reference to the game structure for re-initialization upon game end
 */
void kill_player(GAME *game);

/**
 * Updates of the spider's coordinates to be a wall
 * @param spider the reference to the spider
 */
void maximize_target(SPIDER *spider);

/**
 * Checks if the millipede is out of bounds and, if positive, re-initializes it
 * @param millipede the reference to the millipede
 * @param game_textures the structure holding the game's textures
 */
void millipede_out_of_bounds(MILLIPEDE *millipede, GAME_TEXTURES game_textures);

/**
 * Updates player's sickness and ends the game if it's unrecoverable
 * @param game the reference to the game structure for game re-initialization
 * @param sick the player's sickness
 */
void player_hit(GAME *game, unsigned int sick);

/**
 * Randomly generates a new position to which the spider must travel
 * @param game the reference to the structure containing the spider collection and their textures
 * @param index the index of the spider
 */
void set_new_spider_target(SPIDER spiders[], GAME_TEXTURES game_textures, int index);

/**
 * Player shooting action
 * @param game the reference to the structure containing the game time and the player
 */
void shoot(GAME *game);

/**
 * Spawns a new spider at the given index
 * @param spiders the collection of spiders
 * @param game_textures the structure holding all the game's textures
 * @param index the index of the new spider
 * @param game_time the current game time
 */
void spawn_spider(SPIDER spiders[], GAME_TEXTURES game_textures, int index, unsigned int game_time);

/**
 * Handles player updates
 * @param game the reference to the structure containing the player and its texture
 */
void update_player(GAME *game);

/**
 * Handles spiders updates
 * @param game the reference to the structure containing the spider collection and their textures
 */
void update_spiders(GAME *game);

#endif
