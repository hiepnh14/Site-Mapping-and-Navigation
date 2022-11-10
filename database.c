/*
 * database.h : A header file to share function prototype for database accesses
 */
#include <stdio.h>
#include <string.h>
#include "database.h"
#include "page.h"


/*
 * the definition of array variable to store items
 */
Item data[MAX_ITEM_SIZE];

/*
 * Integer variable to store the number of stored items
 */
static int i=0;

/*
 * Functions
 */


/* function for insertion of a new data item */
void insert_item(void)
{
    if (i >= MAX_ITEM_SIZE)
    {
        printf("Cannot store more than %d items\n", MAX_ITEM_SIZE);
        return;
    }
    Item new;
    printf("Enter the name of item: ");
    scanf("%s", new.name);
    printf("Enter new category of item: ");
    scanf("%s", new.category);
    printf("Enter the x-coordinates: ");
    scanf("%d", &new.x);
    while(new.x > MAX_X_COORDINATE || new.x < 0)
    {
        printf("\nValue typed is not valid, re-enter: ");
        scanf("%d", &new.x);
    }
    printf("\nEnter the y-coordinates: ");
    scanf("%d", &new.y);
    while(new.y > MAX_X_COORDINATE || new.y < 0)
    {
        printf("\nValue typed is not valid, re-enter: ");
        scanf("%d", &new.y);
    }
    data[i] = new;
    i++;
    return;
}
/* function for printing all data items */
void print_all_items(void)
{
    if(i == 0)
    {
        printf("There is no item to print.");
        return;
    }
    printf("|Item name                     |Category            |Position |\n");
    printf("|------------------------------|--------------------|---------|\n");
    //print data
    for (int j = 0; j < i; j++)
    {
        printf("|%-30s|%-20s|(%3d,%3d)|\n", data[j].name, data[j].category, data[j].x, data[j].y);
    }
    printf("|------------------------------|--------------------|---------|\n");
    return;
}

/* function for loading items from a file */
void load_items()
{
    char filename[MAX_FILE_PATH_LENGTH+1];
    printf("Enter path and filename: ");
    scanf("%s", &filename);
    char ch;
    char p;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Cannot open the file");
        return;
    }
    while(!feof(fp))
    {   
        //while loop to read the data's name
        while(fscanf(fp, "%c", &ch) == 1)
        {   
            
            if (ch == ',') break;
            strncat(data[i].name, &ch, 1);
        }
        //while loop to read the data's category
        while(fscanf(fp, "%c", &ch) == 1)
        {
        
            if (ch == ',') break;
            strncat(data[i].category, &ch, 1);
        }
        //read x, y coordinates and skip ',' and '\n'
        fscanf(fp, "%d", &data[i].x);
        fscanf(fp, "%c", &p);
        fscanf(fp, "%d", &data[i].y);
        fscanf(fp, "%c\n", &p);
        //print if data is null.
        if(data[i].name == NULL || feof(fp) )
        {
            fclose(fp);
            printf("\nAll data has been read completely.");
            return;
        }
        i++;
        //print if the storage is full.
        if(i > MAX_ITEM_SIZE)
        {
            printf("\nCannot write more data.");
            fclose(fp);
            return;
        }
    }
    fclose(fp);
    return;
}
/* function for saving items into a file */
void save(void)
{
    char filename[MAX_FILE_PATH_LENGTH+1];
    printf("Enter path and filename to save: ");
    scanf("%s", filename);
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Cannot open or create the file.");
        fclose(fp);
        return;
    }
    for(int j = 0; j < i; j++)
    {
        fprintf(fp, "%s,%s,%d,%d\n",data[j].name,data[j].category,data[j].x, data[j].y);
    }
    fclose(fp);
    return;
}
/* function for finding items based on name */
void find_name(void)
{
    char name[MAX_NAME_LENGTH+1];
    Item *result[10];
    printf("Enter name to be searched: ");
    scanf("%[^\n]%*c", name);
    int size = 0;
    //printf("%s\n", name);
    for (int j = 0; j < i; j++)
    {   
        if (strcmp(name, data[j].name) == 0)
        {
            result[size] = &data[j];
            size++;
            //printf("Ok %s\n", data[j].name);
        }
    }
    if (size == 0)
    {
        printf("No result found.");
        return;
    }
    print_page_search(result, size);
    return;    

}
/* function for finding items based on category */
void find_category(void)
{
    char category[MAX_CATEGORY_LENGTH+1];
    Item *result[MAX_ITEM_SIZE];
    printf("Enter category to be searched: ");
    scanf("%[^\n]%*c", category);
    int size = 0;
    for (int j = 0; j < i; j++)
    {
        if (strcmp(category, data[j].category) == 0)
        {
            result[size] = &data[j];
            size++;
            //printf("Ok\n");
        }
    }
    if (size == 0)
    {
        printf("No result found.");
        return;
    }
    print_page_search(result, size);
    return;    

}
/* function for finding items based on range */
void find_range(void)
{
    int x, y, size = 0;
    float range;
    printf("Enter your x-coordinate: ");
    scanf("%d", &x);
    printf("Enter your y-coordinate: ");
    scanf("%d", &y);
    printf("Your position is now (%d, %d)", x, y);
    printf("\nEnter distance threshold in meter: ");
    scanf("%f", &range);
    Item *result[MAX_ITEM_SIZE];
    range = range/40;
    for (int j = 0; j < i; j++)
    {
        if (((x-data[j].x)*(x-data[j].x) + (y-data[j].y)*(y-data[j].y)) <= range*range)
        {
            result[size] = &data[j];
            //printf("Ok\n");
            size++;
        }
    }
    if (size == 0)
    {
        printf("No result found.");
        return;
    }
    print_page_search(result, size);
    return;    
}
/* function for nearest neighbor items */
void find_neighbor(void)
{
    int x, y, flag = 0;
    float a;
    Item *result[1];
    printf("Enter your x-coordinate: ");
    scanf("%d", &x);
    printf("Enter your y-coordinate: ");
    scanf("%d", &y);
    printf("Your position is now (%d, %d)", x, y);
    a = (x-data[0].x)*(x-data[0].x) + (y-data[0].y)*(y-data[0].y);
    for (int j = 1; j < i; j++)
    {
        if (((x-data[j].x)*(x-data[j].x) + (y-data[j].y)*(y-data[j].y)) <= a)
        {
            a = (x-data[j].x)*(x-data[j].x) + (y-data[j].y)*(y-data[j].y);
            flag = j;
        }       
    }
    result[0] = &data[flag];
    print_page_search(result, 1);
    return;
}
// Function for find and navigate user to a place by search by name or category (the nearest one)
void original_search(void)
{
    int x, y, flag = 0, flag1;
    float a;
    char name[MAX_NAME_LENGTH+1]; // Name of the place or category
    Item *result[MAX_ITEM_SIZE];
    Item final;
    printf("Enter where you want to go (place's name or category):");
    scanf("%[^\n]%*c", name);
    int size = 0;
    for (int j = 0; j < i; j++)
    {
        if (strcmp(name, data[j].category) == 0)
        {
            result[size] = &data[j];
            size++;
            flag = 1;
        }
    }
    for (int j = 0; j < i; j++)
    {   
        if (size != 0) break;
        if (strcmp(name, data[j].name) == 0)
        {
            result[size] = &data[j];
            size++;
            flag = 2;
        }
    }
    if (size == 0) 
    {
        printf("Name or category is not correct.");
        return;
    }
    printf("Enter your x-coordinate: ");
    scanf("%d", &x);
    printf("Enter your y-coordinate: ");
    scanf("%d", &y);
    //Find the nearest category or name if more than 1
    for (int j = 0; j < size; j++)
    {
        if (((x-result[j]->x)*(x-result[j]->x) + (y-result[j]->y)*(y-result[j]->y)) <= a)
        {
            a = (x-result[j]->x)*(x-result[j]->x)+ (y-result[j]->y)*(y-result[j]->y);
            flag1 = j;
        }
    }
    if (flag == 1)    printf("The nearest %s is ", name);  
    printf("%s at (%d,%d)\n", result[flag1]->name, result[flag1]->x, result[flag1]->y);
    if (x < result[flag1]->x)
    {
        printf("It's about %dm to the East\n", (result[flag1]->x - x)*40);
    }
    if (x > result[flag1]->x)
    {
        printf("It's about %dm to the West\n", (x - result[flag1]->x)*40);
    }
    if (y < result[flag1]->y)
    {
        printf("It's about %dm to the South", (result[flag1]->y - y)*40);
    }
    if (y > result[flag1]->y)
    {
        printf("It's about %dm to the North", (y - result[flag1]->y)*40);
    }
    print_navigation(*result[flag1], x, y);
    return;
}
