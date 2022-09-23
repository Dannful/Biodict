#ifndef BIODICT_IO_H
#define BIODICT_IO_H

#include <stdio.h>

#include "structures.h"

/**
 * Loads the records data from the file
 * @param records the reference to the records collection
 */
void load_records(RECORD records[]);

/**
 * Prints the lines from the records to the given file
 * @param file the file to which the records will be saved
 * @param records the reference to the records collection
 */
void print_to_file(FILE *file, RECORD records[]);

/**
 * Reads saved game data
 * @param game the reference to the game structure
 */
void read_game(GAME *game);

/**
 * Reads the records saved in the given file and stores it in the given collection
 * @param file the file from which the records will be read
 * @param records the reference to the records collection
 */
void read_record_lines(FILE *file, RECORD records[]);

/**
 * Saves game data
 * @param game the reference to the game structure for leaderboard updating
 */
void save_game(GAME *game);

/**
 * Saves the given records to the external file
 * @param records the reference to the records collection
 */
void save_to_leaderboard_file(RECORD records[]);

#endif
