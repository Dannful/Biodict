#ifndef BIODICT_HEADER_C
#define BIODICT_HEADER_C

#include "raylib.h"
#include "structures.h"

/**
 * Allocates memory for a new
 * bullet
 * @param bullet the reference to the variable
 * holding the head bullet
 * @return
 */
BULLET *allocate_bullet(BULLET **bullet);

/**
 * Animates the player's sprite according
 * to movement and shooting
 * @param player the player to be moved
 * @param player_texture the texture for the player
 */
void animate_player(PLAYER *player, Texture2D player_texture);

/**
 * Calculates the angle between
 * cathetus X and Y
 * @param cathetusX the adjacent cathetus
 * @param cathetusY the opposite cathetus
 * @return the angle between the two cathetus
 */
float calculate_angle(float cathetusX, float cathetusY);

/**
 * Draws the bullets on the screen with the given texture
 * @param bullet the reference to the head bullet
 * @param bullet_texture the texture of the bullet
 */
void draw_bullet(BULLET *bullet, Texture2D bullet_texture);

/**
 * Draws the player's crosshair
 * @param crosshair_texture the crosshair texture
 * to be drawn
 */
void draw_crosshair(Texture2D crosshair_texture);

/**
 * Draws the mushrooms on the screen
 * @param mushrooms the collection of mushrooms
 * @param mushroom_texture the texture for the mushrooms
 */
void draw_mushrooms(MUSHROOM *mushrooms, Texture2D mushroom_texture);

/**
 * Draws the player on the screen
 * @param player the player to be drawn
 * @param player_texture the texture for the player
 */
void draw_player(PLAYER *player, Texture2D player_texture);

/**
 * Draws the given texture
 * rotated in the given angle
 * @param texture the texture to be drawn
 * @param position the position at which the texture
 * will be drawn
 * @param angle the angle in which the texture will
 * be rotated
 */
void draw_texture_angle(Texture2D texture, Vector2 position, float angle);

/**
 * Randomly distributes mushrooms across the screen
 * @param mushrooms the collection of mushrooms
 * @param mushroom_texture the texture for the mushrooms
 */
void initialize_mushrooms(MUSHROOM *mushrooms, Texture2D mushroom_texture);

/**
 * Initializes the player structure
 * @param player the reference to the player to be initialized
 * @param player_texture the texture for the player
 */
void initialize_player(PLAYER *player, Texture2D player_texture);

/**
 * Initializes the textures that
 * will be used in the game
 * @param game_textures the reference to the structure
 * holding all the textures
 */
void initialize_textures(GAME_TEXTURES *game_textures);

/**
 * Detects input and initializes a new bullet
 * @param player the player who is shooting
 * @param bullet the reference to the variable
 * holding the head bullet
 * @param bullet_texture the texture for the bullet
 * @param last_bullet_time the frame count when the
 * last bullet was shot
 * @param frames_counter the total amount of frames
 * elapsed
 */
void shoot(PLAYER *player, BULLET **bullet, Texture2D bullet_texture, unsigned int *last_bullet_time, unsigned int frames_counter);

/**
 * Unloads the loaded textures from the VRAM
 * @param game_textures the textures loaded
 * unloaded
 */
void unload_textures(GAME_TEXTURES game_textures);

/**
 * Updates bullets' positions and removes
 * any that are out of bounds
 * @param bullet the reference to the variable
 * holding the head bullet
 */
void update_bullets(BULLET **bullet);

#endif

