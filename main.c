// ELEC2645 Unit 2 Project Template
// Command Line Application Menu Handling Code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

/* Prototypes mirroring the C++ version */

static void main_menu(void);            /* runs in the main loop ---  infinite loop to run the program: print menu and get input */

static void print_main_menu(void);      /* output the main menu description ---  prints the options  */

static int get_user_input(important_constants local_name_of_enum_value);  /* get a valid integer menu choice ----   Validates user input for the menu too */

static void select_menu_item(int input);/* run code based on user's choice ---  just selects the option and runs the function */
 
static void go_back_to_main(void);      /* wait for 'b'/'B' to continue ---- returns to main menu if user wants to */

static int is_integer(const char *s);  /* validate integer string --- don't touch input validation */

int main(void)
{
    does_circuit_exist = 0; // This global variable is set to 0 before starting the program because no circuit has been made yet

    menu_item_4(); // Running this function before the main program to set all the labels and values for the created pins of the gates to zero

    int create_file(); /* Create a text file to store the circuit design in,
                       this will update as the circuit is created */

    /* this loop will run forever until we call exit(0) in select_menu_item() */
    for(;;) {
        main_menu();
    }
    /* not reached */
    return 0;
}

static void main_menu(void)
{
    print_main_menu(); // Firstly print the menu options...
    printf("\nPlease select a function.\n(Enter a number):  "); // ...then ask the user to select an option

    int input = get_user_input(MENU_ITEMS); /* Retreiving and validating user input via the get_user_input function,
                                               and an enum is used to determine the range of acceptable user input values. */

    select_menu_item(input); // Now we use the user's input to determine which function is called.
}

static int get_user_input(important_constants local_name_of_enum_value)
{
    // NOTE: local_name_of_enum_value is the maximum number of numbers in the list of possible inputs for menu selection

    /*
    This function is mostly unedited from the original provided version except that
    the maximum number of numbers is determined when calling the function.
    Also, and extra if statement has been added to allow for binary inputs of 1 & zero to be validated.
    */

    char buf[128];
    int valid_input = 0;
    int value = 0;

    do {
        if (!fgets(buf, sizeof(buf), stdin)) {  /* If the input is outside the buffer range,
                                                   is the wrong input type or no input is provided */
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';

        if (!is_integer(buf)) {             // If the input isn't an integer. The user is told to enter one and the loop repeats.
            printf("Enter an integer!\n");
            valid_input = 0;
        } else {
            value = (int)strtol(buf, NULL, 10);

            if (local_name_of_enum_value == 2 && value >=0 && value <= 1){ // for a choice between binary 1 and 0.
                valid_input = 1;
            }
            else if (value >= 1 && value <= local_name_of_enum_value) { // for a choice between numbered menu options from 1 to the maximum number of numbers
                valid_input = 1;
            } else {
                printf("Invalid menu item!\n");     // If the entered number is outside the range of acceptable inputs.
                valid_input = 0;
            }
        }
    } while (!valid_input); // The loop repeats until a valid input is entered.

    return value; // Once valid, the input is returned and can be used for selecting options using an if or a switch.
}

static void print_main_menu(void)   // Self-explanatory
{
    printf("\n----------- Main menu -----------\n");
    printf("\n"
           "\t\t\t\t\t\t\n"
           "\t1. Logic Gate Information\t\t\n"
           "\t2. Make Logic Circuit\t\t\n"
           "\t3. Circuit Testing\t\t\n"
           "\t4. Clear Circuit\t\t\t\t\n"
           "\t5. Exit\t\t\t\t\n"
           "\t\t\t\t\t\t\n");
    printf("------------------------------------\n");
}

static void select_menu_item(int input) // Using a switch to run the selected menu function
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
            printf("Bye!\n");
            exit(0);
        default:
            printf("Invalid Input. Exiting anyway. Bye!\n");
            exit(1);
    }
}

static void go_back_to_main(void) // Self-explanatory
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