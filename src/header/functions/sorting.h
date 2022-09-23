#ifndef BIODICT_SORTING_H
#define BIODICT_SORTING_H

#include "structures.h"

/**
 * Checks if an insertion is viable at the last position, and, if positive, executes it
 * @param records the reference to the records
 * @param player the current player
 * @param inserted boolean value for whether the current player has already been inserted or not
 */
void check_last_position(RECORD records[], PLAYER player, int inserted);

/**
 * Saves the current player to the leaderboard, if suitable
 * @param game the reference to the structure holding the player and the records
 */
void save_to_leaderboard(GAME *game);

/**
 * Saves the given player to the specified records position
 * @param records the collection of records
 * @param player the player
 * @param position the position
 */
void save_to_leaderboard_position(RECORD records[], PLAYER player, int position);

/**
 * Sorts the given collection in ascending order
 * @param records the collection of records
 */
void sort_records(RECORD records[]);

/**
 * Switches the values for records in the given positions
 * @param records the collection of records
 * @param i the first index
 * @param j the second index
 */
void switch_positions(RECORD records[], int i, int j);

#endif
