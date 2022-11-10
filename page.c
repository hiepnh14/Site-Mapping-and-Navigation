/*
 * page.h : A header file to share function prototypes for page viewing
 */
#ifndef PAGE_H
#define PAGE_H

/* this file depends on item.h */
#include "item.h"
#include <stdio.h>


/*
 * Macro definitions related to page viewing
 */
#define RESULT_PAGE "result.html"


/*
 * Function prototypes related to page viewing
 */
void print_page(Item *result[], int size)
{
	FILE *f;
	int i,j,k;

	if( (f = fopen(RESULT_PAGE, "w")) == NULL) {
		printf("cannot open file %s.", RESULT_PAGE);
		return;
	}

	/* printing HTML header */
	fprintf(f, "<html>\n");
	fprintf(f, "<head>\n");
	fprintf(f, "<title>result page</title>\n");
	fprintf(f, "<style type=\"text/css\">\n");
	fprintf(f, "table { background-image: url(\"nagoya.gif\"); }\n");
	fprintf(f, "td { padding: 0px; border: 1px; width: 16px; height: 14px; font-size: 10px; text-align: center; color: #ff00ff; } \n");
	fprintf(f, "</style>\n");
	fprintf(f, "</head>\n");
	fprintf(f, "<body>\n");

	/* printing HTML table */
	

	fprintf(f, "</body>\n");
	fprintf(f, "</html>\n");

	fclose(f);

	printf("Nagoya University's map is written to the file %s.\n", RESULT_PAGE);
	return;
}



/* function prototype to show query result pages */
void print_page_search(Item *result[], int size)
{
	FILE *f;
	int i,j,k;

	if( (f = fopen(RESULT_PAGE, "w")) == NULL) {
		printf("cannot open file %s.", RESULT_PAGE);
		return;
	}

	/* printing HTML header */
	fprintf(f, "<html>\n");
	fprintf(f, "<head>\n");
	fprintf(f, "<title>result page</title>\n");
	fprintf(f, "<style type=\"text/css\">\n");
	fprintf(f, "table { background-image: url(\"nagoya.gif\"); }\n");
	fprintf(f, "td { padding: 0px; border: 1px; width: 16px; height: 14px; font-size: 10px; text-align: center; color: #ff00ff; } \n");
	fprintf(f, "</style>\n");
	fprintf(f, "</head>\n");
	fprintf(f, "<body>\n");

	/* printing HTML table */
	fprintf(f, "<table>\n");
	for(int y = 0; y < MAX_Y_COORDINATE; y++){

		/* printing table row */
		fprintf(f, "<tr>\n");
		for(int x = 0; x < MAX_X_COORDINATE; x++){

			/* printing table column */
			fprintf(f,"<td>");

			/* printing item label corresponding to X=j, Y=i */
                for (int count = 0; count < size; count++)
                {
                    if (x == result[count]->x && y == result[count]->y)
                    {   
                        //printf("Okay, %d, %d\n", x,y);
                        fprintf(f, "%d", count+1 );
                    }
                }
			fprintf(f,"</td>\n");
		}
		fprintf(f, "</tr>\n");
	}
	fprintf(f, "</table>\n");

	/* printing HTML list */
	fprintf(f, "<ul>\n");
	/* printing list items */
    for( int count = 0; count < size; count++ )
    {
        fprintf(f, "<li>%d : %s</li>\n", count + 1, result[count]->name ); /* item count */
    }
	fprintf(f, "</ul>\n");
	fprintf(f, "</body>\n");
	fprintf(f, "</html>\n");
	fclose(f);
	printf("\nSearch result is written to the file %s.\n", RESULT_PAGE);
	return;
}

void print_navigation(Item result, int x_position, int y_position)
{
	FILE *f;
	int i,j,k;

	if( (f = fopen(RESULT_PAGE, "w")) == NULL) {
		printf("cannot open file %s.", RESULT_PAGE);
		return;
	}

	/* printing HTML header */
	fprintf(f, "<html>\n");
	fprintf(f, "<head>\n");
	fprintf(f, "<title>result page</title>\n");
	fprintf(f, "<style type=\"text/css\">\n");
	fprintf(f, "table { background-image: url(\"nagoya.gif\"); }\n");
	fprintf(f, "td { padding: 0px; border: 1px; width: 16px; height: 14px; font-size: 10px; text-align: center; color: #ff00ff; } \n");
	fprintf(f, "</style>\n");
	fprintf(f, "</head>\n");
	fprintf(f, "<body>\n");

	/* printing HTML table */
	fprintf(f, "<table>\n");
	for(int y = 0; y < MAX_Y_COORDINATE; y++){
		/* printing table row */
		fprintf(f, "<tr>\n");
		for(int x = 0; x < MAX_X_COORDINATE; x++){

			/* printing table column */
			fprintf(f,"<td>");
				// Mark target point
                if (x == result.x && y == result.y)   
                        fprintf(f, "X");
				if (x == x_position && y == y_position) // Mark initial point
					fprintf(f, "O"); 
				if (((result.x <= x && x < x_position) || (x_position < x && x <= result.x)) && y == y_position) // horizontal lines
					fprintf(f,"-");
				if (((result.y < y && y <= y_position) || (y_position <= y && y < result.y)) && x == result.x)	// vertical lines
					fprintf(f, "|");
			fprintf(f,"</td>\n");
		}
		fprintf(f, "</tr>\n");
	}
	fprintf(f, "</table>\n");

	/* printing HTML list */
	fprintf(f, "<ul>\n");

	/* printing item and initial position */
    fprintf(f, "<li>Your position is (%d, %d)</li>\n", x_position, y_position); 
    fprintf(f, "<li>Your target is: %s</li>\n", result.name ); /* item count */
    int x = x_position, y = y_position;
	if (x < result.x)
    {
        fprintf(f, "<li>It's about %dm to the East</li>\n", (result.x - x)*40);
    }
    if (x > result.x)
    {
        fprintf(f,"<li>It's about %dm to the West</li>\n", (x - result.x)*40);
    }
    if (y < result.y)
    {
        fprintf(f,"<li>It's about %dm to the South</li>", (result.y - y)*40);
    }
    if (y > result.y)
    {
        fprintf(f,"<li>It's about %dm to the North</li>", (y - result.y)*40);
    }

	fprintf(f, "</ul>\n");


	fprintf(f, "</body>\n");
	fprintf(f, "</html>\n");

	fclose(f);

	printf("\nSearch result is written to the file %s.\n", RESULT_PAGE);
	return;
}



#endif