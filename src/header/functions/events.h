#ifndef BIODICT_EVENTS_H
#define BIODICT_EVENTS_H

#include "structures.h"

/**
 * Action performed when the user clicks on the exit button
 * @param game_textures the structure containing the game's textures
 */
void on_exit_click(GAME_TEXTURES game_textures);

/**
 * Action performed when the user clicks on the load button
 * @param game the reference to the game structure
 */
void on_load_click(GAME *game);

/**
 * Defines user-menu interaction
 * @param game the reference to the game structure
 */
void on_menu_click(GAME *game);

/**
 * Action performed when the user clicks on the pause button
 * @param game the reference to the game structure
 */
void on_pause_click(GAME *game);

/**
 * Action performed when the user clicks on the ranking button
 * @param game the reference to the game structure
 */
void on_ranking_click(GAME *game);

/**
 * Action performed when the user clicks on the start button
 * @param game the reference to the game structure
 */
void on_start_click(GAME *game);

#endif
