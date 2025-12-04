// ELEC2645 Unit 2 Project Template
// Command Line Application Menu Handling Code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

/* Prototypes mirroring the C++ version */

static void main_menu(void);            /* runs in the main loop */               //        ---  infinite loop to run the program: print menu and get input  don't touch

static void print_main_menu(void);      /* output the main menu description */    //            ---  prints the options         DONE

static int  get_user_input(menu_items local_name_of_enum_value);  // Don't know if I need to put local_name_of_enum_value here     /* get a valid integer menu choice */   // ----   Validates user input for the menu too  - don't need to touch

static void select_menu_item(int input);/* run code based on user's choice */    //             ---  just selects the option and runs the function            DONE
 
static void go_back_to_main(void);      /* wait for 'b'/'B' to continue */        //           ----  no need to touch, returns to main menu if user wants to

static int  is_integer(const char *s);  /* validate integer string */             //              --- don't touch input validation


int main(void)
{
    menu_item_6(); // Running this function first to set all the labels and values for the created pins of the gates to zero

    /* this will run forever until we call exit(0) in select_menu_item() */
    for(;;) {
        main_menu();
    }
    /* not reached */
    return 0;
}

static void main_menu(void)
{
    print_main_menu();

    menu_items cur_items = MENU_ITEMS;
    // cur_items = A; - use this to rewrite the value of cur_items to another enum value
    int input = get_user_input(cur_items);
    select_menu_item(input);
}

static int get_user_input(menu_items local_name_of_enum_value)
{
    // local_name_of_enum_value is the number of numbers we want in our list of possible inputs for menu selection

    //enum { MENU_ITEMS = n };   /* E.g. 1..4 = items, 5 = Exit */   --- I've taken this line out, so that I can reuse this function for other input validation,
                                                                    //   where I can provide a different length enum to match the situation
    char buf[128];
    int valid_input = 0;
    int value = 0;

    do {
        printf("\nSelect item: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';

        if (!is_integer(buf)) {
            printf("Enter an integer!\n");
            valid_input = 0;
        } else {
            value = (int)strtol(buf, NULL, 10);
            if (value >= 1 && value <= local_name_of_enum_value) {
                valid_input = 1;
            } else {
                printf("Invalid menu item!\n");
                valid_input = 0;
            }
        }
    } while (!valid_input);

    return value;
}

static void select_menu_item(int input)
{
    switch (input) {
        case 1:
            menu_item_1();
            go_back_to_main();
            break;
        case 2:
            menu_item_2();
            go_back_to_main();
            break;
        case 3:
            menu_item_3();
            go_back_to_main();
            break;
        case 4:
            menu_item_4();
            go_back_to_main();
            break;
        case 5:
            menu_item_5();
            go_back_to_main();
            break;
        case 6:
            menu_item_6();
            go_back_to_main();
            break;
        case 7:
            printf("Bye!\n");
            exit(0);
        default:
            printf("Invalid Input. Exiting anyway. Bye!\n");
            exit(1);
    }
}

static void print_main_menu(void)
{
    printf("\n----------- Main menu -----------\n");
    printf("\n"
           "\t\t\t\t\t\t\n"
           "\t1. Logic Gate Information\t\t\n"
           "\t2. Make Logic Circuit\t\t\n"
           "\t3. Make Test Script\t\t\n"
           "\t4. Run Test Script\t\t\n"
           "\t5. Generate Truth Table of Circuit\t\t\n"
           "\t6. Clear Cirucit\t\t\t\t\n"
           "\t7. Exit\t\t\t\t\n"
           "\t\t\t\t\t\t\n");
    printf("---------------------------------------------\n");
}

static void go_back_to_main(void)
{
    char buf[64];
    do {
        printf("\nEnter 'b' or 'B' to go back to main menu: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            puts("\nInput error. Exiting.");
            exit(1);
        }
        buf[strcspn(buf, "\r\n")] = '\0'; /* strip newline */
    } while (!(buf[0] == 'b' || buf[0] == 'B') || buf[1] != '\0');
}

/* Return 1 if s is an optional [+/-] followed by one-or-more digits, else 0. */
static int is_integer(const char *s)
{
    if (!s || !*s) return 0;

    /* optional sign */
    if (*s == '+' || *s == '-') s++;

    /* must have at least one digit */
    if (!isdigit((unsigned char)*s)) return 0;

    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}