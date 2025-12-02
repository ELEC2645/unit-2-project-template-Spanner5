#include <stdio.h>
#include "funcs.h"

void menu_item_1(void) {
    printf("\n>> Menu 1: Logic Gate Information\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 1 */

    /* 
    First, a sub-menu for options to select the gates:  (select which gate to display information for (enter a number))
    2nd, for the user input number, validate it, etc - use existing functions to do that
    3rd, display info for the coresponding gate (use structs and pointers to select and print the gate info) - want a picture for each gate and info
    4th, asks if want to display another gate. If not, returns to menu.
    */


    // Selecting which gate the user wants info for

    printf("\nSelect which gate to display information for (enter a number)\n"); // getting user input
    print_gates();  // displaying the gate options
    menu_items number_of_possible_inputs = GATE_OPTIONS;
    int display_choice = get_user_input(number_of_possible_inputs); // retreiving and validating the input

    struct Gate *p = &NAND; // initialising a pointer for a gate, setting it to NAND by default
    select_gate(p, display_choice); // calls a function which points the pointer towards the correct gate 



    // CODE HERE TO DISPLAY THE DIAGRAM STORED IN THE STRUCT





    printf("Name of Gate: %c",p->name);
    printf("Number of NANDs used to make the gate: %d",p->n_nands);
    printf("Number of inputs: %d",p->n_inputs);
    printf("Number of outputs: %d",p->n_outputs);
    printf("Boolean_representation: %c",p->Boolean_representation);
    
    printf("Would you like to display information for another gate?\n(Enter 1 for yes, 0 for no)    ");
    menu_items two_options = BINARY_CHOICE;
    int yes_no = get_user_input(two_options);
    if (yes_no == 1){
        menu_item_1();
    } else {
        printf("Returning to Main Menu");
        main_menu();
    }
}

void print_gates(void){ 
    printf("\n"
           "\t\t\t\t\t\t\n"
           "\t1. NAND\t\t\n"
           "\t2. NOT\t\t\n"
           "\t3. AND\t\t\n"
           "\t4. OR\t\t\n"
           "\t5. XOR\t\t\n"
           "\t6. Buffer\t\t\t\t\n"
           "\t7. Mux\t\t\n"
           "\t8. Demux\t\t\n"
           "\t\t\t\t\t\t\n");
}

void select_gate(struct Gate *p, int display_choice) // // A function which points the pointer towards the correct gate - depending on the entered number, enabling gate selection
{
    switch (display_choice) {
        case 1:
            p = &NAND;
            break;
        case 2:
            p = &NOT;
            break;
        case 3:
            p = &AND;
            break;
        case 4:
            p = &OR;
            break;
        case 5:
            p = &XOR;
            break;
        case 6:
            p = &Buffer;
            break;
        case 7:
            p = &Mux;
            break;
        case 8:
            p = &Demux;
            break;
        default:
            printf("Invalid input! Returning to Menu 1\n");
            menu_item_1();
    }
}

void menu_item_2(void) {
    printf("\n>> Menu 2: Make Logic Circuit\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 2 */

    /*
    Ideas:

    Requires user input to select gate.
    Need to validate that input.
    Then, for that gate, need to decide inputs for the gate - e.g. pins. But if I print a picture of gate and say the pin labels to make it easy. Need to specify number of bits of input to get bits of rest of circuit - or go gate by gate
    If possible, display the current built circuit to make design easier - rather than gate by gate
    After a gate, choose to add more gates. Return to menu. Run test script. Test individual output.
    */
}

void menu_item_3(void) {
    printf("\n>> Menu 3: Make Test Script\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 3 */

    /* 
    Allows user to enter to decide how many variables, variable names, outputs, then the variables will increment as normal, but the user will enter the output value for each output on a row 
    */

}

void menu_item_4(void) {
    printf("\n>> Menu 4: Run Test Script\n");
    printf("\nSome code here does something useful\n");

    /*
    Need to load a test script as a text file.
    Then convert to array? Or run the make test script or generate truth table of the circuit and see if it matches. If not, for that row print the actual value, error and the value it should be
    */

    /* you can call a function from here that handles menu 4 */
}

void menu_item_5(void) {
    printf("\n>> Menu 4: Generate Truth Table of Circuit\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 4 */
    
    /*
    First, check if a circuit exists, if not - return to menu
    Basically, just need to run the circuit for each possible input and record output in a table., (Print an array). Use iterative for loop from i of msb, j of less msb, ... z of lowest msb
    e.g. for i(...){ for j(...){ for z(... )}}

    */
}