/*
 * page.h : A header file to share function prototypes for page viewing
 */
#ifndef PAGE_H
#define PAGE_H

/* this file depends on item.h */
#include "item.h"



/*
 * Macro definitions related to page viewing
 */


/*
 * Function prototypes related to page viewing
 */
void print_page(Item *result[], int size);
/* function prototype to show query result pages */
void print_page_search(Item *result[], int size);
// function prototype to show navigation page
void print_navigation(Item result, int x_position, int y_position);

#endif