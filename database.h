/*
 * database.h : A header file to share function prototype for database accesses
 */
#ifndef DATABASE_H
#define DATABASE_H

/* this header file depends on item.h */
#include "item.h"

/*
 * Macro defitions related to database
 */

/* Macro definition for the maximum size of database */
#define MAX_ITEM_SIZE 100 

/* Macro definition for the maximum length of file path (loading/saving) */
#define MAX_FILE_PATH_LENGTH 30


/*
 * Function prototypes related to database
 */

/* function prototype for insertion of a new data item */
void insert_item(void);
/* function prototype for printing all data items */
void print_all_items(void);
/* function prototype for loading items from a file */
void load_items(void);
/* function prototype for saving items into a file */
void save(void);
/* function prototype for finding items based on name */
void find_name(void);
/* function prototype for finding items based on category */
void find_category(void);
/* function prototype for finding items based on range */
void find_range(void);
/* function prototype for nearest neighbor items */
void find_neighbor(void);
// function prototype for original search
void original_search(void);
#endif