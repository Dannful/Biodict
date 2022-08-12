#ifndef BIODICT_HEADER_C
#define BIODICT_HEADER_C

#include "raylib.h"
#include "structures.h"

/**
 * Draws the bullets on the screen with the given texture
 * @param bullet the reference to the head bullet
 * @param bullet_texture the texture of the bullet
 */
void draw_bullet(Bullet *bullet, Texture2D bullet_texture);

/**
 * Draws the mushrooms on the screen
 * @param mushrooms the collection of mushrooms
 */
void draw_mushrooms(Mushroom *mushrooms);

/**
 * Draws the player on the screen
 * @param player the player to be drawn
 */
void draw_player(Player *player);

/**
 * Moves the player, restricting the y and x
 * within the screen bounds
 * @param player the player to be moved
 */
void move_player(Player *player);

/**
 * Randomly distributes mushrooms across the screen
 * @param mushrooms the collection of mushrooms
 */
void initialize_mushrooms(Mushroom *mushrooms);

/**
 * Initializes the player structure
 * @param player the reference to the player to be initialized
 */
void initialize_player(Player *player);

/**
 * Detects input and initializes a new bullet
 * @param player the player who is shooting
 * @param bullet the reference to the variable
 * holding the head bullet
 */
void shoot(Player *player, Bullet **bullet);

/**
 * Unloads the loaded textures
 * @param mushrooms the collection of mushrooms
 * @param player the player
 */
void unload_textures(Mushroom *mushrooms, Player *player);

/**
 * Updates bullets' positions and removes
 * any that are out of bounds
 * @param bullet the reference to the variable
 * holding the head bullet
 */
void update_bullets(Bullet **bullet);

#endif

