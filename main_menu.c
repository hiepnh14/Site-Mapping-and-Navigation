/*
 * main_menu.c : A Source file of main function
 */
#include <stdio.h>
#include "item.h"
#include "database.h"


/* main function */
int main(void)
{
    printf("This is a skelton of the spatial database.\n");
    char code;
    for(;;) {
        printf("Enter operation code (Press 'h' for help): ");
        scanf(" %c", &code);
        while (getchar() != '\n')  /* skips to end of line */
            ;
        switch(code) {
            case 'i': insert_item();
                      break;
            case 'l': 
                
                load_items();
                      break;
            case 's': save();
                      break;
            case 'f': find_name();
                      break;
            case 'c': find_category();
                      break;
            case 'r': find_range();
                      break;
            case 'p': print_all_items();
                      break;
            case 'n': find_neighbor();
                      break;
            case 'q': return 0;
            case 'o': original_search();
                      break;
            case 'h': printf("'i' to insert from keyboard\n");
                        printf("'p' to print all data items\n");
                        printf("'l' to load data from a file\n");
                        printf("'s' to save program output into a file\n");
                        printf("'f' to find item based on its name\n");
                        printf("'c' to have categorical search\n");
                        printf("'r' to do range search\n");
                        printf("'n' to search for nearest neighbor\n");
                        printf("'o' to navigate to certain place's name or the closest category:");
                      break;
            default:  printf("Illegal code\n");
        }
        printf("\n");
    }
    return 0;
}
