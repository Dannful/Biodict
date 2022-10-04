#ifndef BIODICT_GRAPHICS_H
#define BIODICT_GRAPHICS_H

#include "structures.h"

/**
 * Deletes the last character from the user input
 * @param game the reference to the structure holding the user's name
 * @param name_edit the reference to the structure containing editing data
 */
void delete_last_name_character(GAME *game, NAME_EDIT *name_edit);

/**
 * Disables username editing mode
 * @param game the reference to the structure containing the user's name
 * @param name_edit the reference to the structure holding editing data
 * @param on_enter action performed upon saving input
 */
void disable_editing(GAME *game, NAME_EDIT *name_edit, void (*on_enter)(GAME *));

/**
 * Draws the information on the lower side of the screen
 * @param game the game structure
 */
void draw_bottom_info(GAME game);

/**
 * Draws the crosshair
 * @param crosshair_texture the texture for the crosshair
 */
void draw_crosshair(Texture2D crosshair_texture);

/**
 * Abstract function for drawing an interface for retrieving username
 * @param game the reference to the structure holding the user's name
 * @param name_edit the reference to the structure containing editing data
 * @param on_enter action performed upon saving input
 */
void draw_input_requirement(GAME *game, NAME_EDIT *name_edit, void (*on_enter)(GAME *));

/**
 * Draws the load menu, if it is selected
 * @param game the reference to the structure containing the selected tab and the user's name
 * @param name_edit the reference to the structure containing editing data
 */
void draw_load_menu(GAME *game, NAME_EDIT *name_edit);

/**
 * Draws the entire upper menu
 * @param game the reference to the game structure
 * @param name_edit the reference to the structure holding the editing data
 */
void draw_menu(GAME *game, NAME_EDIT *name_edit);

/**
 * Draws the millipede
 * @param millipede the reference to the millipede
 * @param millipede_texture the texture for the millipede
 */
void draw_millipede(MILLIPEDE *millipede, Texture2D millipede_texture);

/**
 * Draws the mushrooms
 * @param mushrooms the collection of mushrooms
 * @param mushroom_texture the texture for the mushrooms
 */
void draw_mushrooms(MUSHROOM mushrooms[], Texture2D mushroom_texture);

/**
 * Draws the player
 * @param player the player structure
 * @param player_texture the texture for the player
 */
void draw_player(PLAYER player, Texture2D player_texture);

/**
 * Draws the ranking menu
 * @param game the structure containing the selected tab and the records collection
 */
void draw_ranking(GAME game);

/**
 * Draws the paused menu
 * @param game the reference to the structure containing the selected tab and the user's name
 * @param name_edit the reference to the structure containing the editing data
 */
void draw_save_menu(GAME *game, NAME_EDIT *name_edit);

/**
 * Draws the menu to save to the leaderboard
 * @param game the reference to the structure containing the selected tab and the user's name
 * @param name_edit the reference to the structure containing the editing data
 */
void draw_save_ranking(GAME *game, NAME_EDIT *name_edit);

/**
 * Draws the millipede's segments
 * @param game the reference to the structure containing the millipede's texture and segments data
 */
void draw_segments(GAME *game);

/**
 * Draws the spiders
 * @param spiders the collection of spiders
 * @param spider_texture the texture for the spiders
 */
void draw_spiders(SPIDER spiders[], Texture2D spider_texture);

/**
 * Enables username editing
 * @param name_edit the reference to the structure containing editing data
 * @param text_box the editing text box
 */
void enable_editing(NAME_EDIT *name_edit, Rectangle text_box);

/**
 * Handles all drawing
 * @param game the reference to the game structure
 * @param name_edit the reference to the structure holding editing data
 */
void game_drawing(GAME *game, NAME_EDIT *name_edit);

/**
 * @param game_textures the structure holding the game's textures
 * @return the gap between the left corner of the screen and the upper menu
 */
int menu_gap(GAME_TEXTURES game_textures);

/**
 * @param game_textures the structure that holds the game's textures
 * @return the minimum height accessible for game content
 */
int min_screen_height(GAME_TEXTURES game_textures);

/**
 * Handles username typing
 * @param game the reference to the structure containing the user's name
 * @param name_edit the reference to the structure containing username editing data
 * @param on_enter action performed upon saving input
 */
void type_name(GAME *game, NAME_EDIT *name_edit, void (*on_enter)(GAME *));

/**
 * Unloads the game's textures
 * @param game_textures the structure holding the game's textures
 */
void unload_textures(GAME_TEXTURES game_textures);

#endif
