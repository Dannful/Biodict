#ifndef BIODICT_HEADER_C
#define BIODICT_HEADER_C

#include "raylib.h"
#include "structures.h"

/**
 *
 * @param player the player to be moved
 * Moves the player, restricting the y and x
 * within the screen bounds
 */
void move_player(Player *player);

/**
 *
 * @param mushrooms the collection of mushrooms
 * Randomly distributes mushrooms across the screen
 */
void initialize_mushrooms(Mushroom *mushrooms);

void initialize_player(Player *player);

/**
 *
 * @param mushrooms the collection of mushrooms
 * Draws the mushrooms on the screen
 */
void draw_mushrooms(Mushroom *mushrooms, Texture2D mushroom_texture);

void draw_player(Player *player);

#endif

