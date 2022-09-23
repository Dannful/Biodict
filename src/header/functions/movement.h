#ifndef BIODICT_MOVEMENT_H
#define BIODICT_MOVEMENT_H

#include "structures.h"

/**
 * Handles the millipede's animation
 * @param millipede the reference to the millipede
 * @param game_textures the structure holding the game's textures
 */
void animate_millipede(MILLIPEDE *millipede, GAME_TEXTURES game_textures);

/**
 * Handles the player's animation
 * @param player the reference to the player
 * @param player_texture the player's texture
 */
void animate_player(PLAYER *player, Texture2D player_texture);

/**
 * Calculates the required delta x and y for an object to go from origin to target
 * @param origin the starting position
 * @param target the ending position
 * @return a structure containing the sinus (y-axis movement) and cosinus (x-axis movement)
 */
MOVEMENT calculate_movement(Vector2 origin, Vector2 target);

/**
 * Moves the given position with the values given by the movement at the provided speed
 * @param position the current position
 * @param movement the movement that will be performed on the position
 * @param speed the speed for the movement
 */
void move(Vector2 *position, MOVEMENT movement, float speed);

/**
 * Handles the given spider's movement
 * @param spiders the collection of spiders
 * @param game_textures the structure holding the game's textures
 * @param index the index of the spider
 */
void move_spider(SPIDER spiders[], GAME_TEXTURES game_textures, int index);

/**
 * Handles the player's shooting animation
 * @param player the reference to the player
 * @param player_texture the player's texture
 */
void shoot_animation(PLAYER *player, Texture2D player_texture);

#endif
