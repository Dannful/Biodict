#ifndef BIODICT_INITIALIZATION_H
#define BIODICT_INITIALIZATION_H

#include "structures.h"

/**
 * Initializes the game structure
 * @param game the reference to the game structure
 */
void initialize_game(GAME *game);

/**
 * Initializes the millipede structure
 * @param millipede the reference to the millipede
 * @param game_textures the structure holding the game's textures
 */
void initialize_millipede(MILLIPEDE *millipede, GAME_TEXTURES game_textures);

/**
 * Initializes the mushrooms
 * @param game the reference to the structure containing the mushroom collection and their textures
 */
void initialize_mushrooms(GAME *game);

/**
 * Initializes the player
 * @param player the reference to the player
 * @param player_texture the player's texture
 */
void initialize_player(PLAYER *player, Texture2D player_texture);

/**
 * Initializes the last players' records
 * @param records the reference to the records collection
 */
void initialize_records(RECORD records[]);

/**
 * Initializes the spider at the given index
 * @param spiders the collection of spiders
 * @param game_textures the structure holding all the game's textures
 * @param index the index of the spider
 */
void initialize_spider(SPIDER spiders[], GAME_TEXTURES game_textures, int index);

/**
 * Initializes the spiders collection
 * @param spiders the spiders collection
 */
void initialize_spiders(SPIDER spiders[]);

/**
 * Initializes the game's textures
 * @param game_textures the reference to the structure holding the game's textures
 */
void initialize_textures(GAME_TEXTURES *game_textures);

/**
 * Initializes the game's window and sets the fps
 */
void initialize_window();

#endif
