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
            printf("Invalid input! Returning to Main Menu\n");
            main_menu();
    }
}

void menu_item_2(void) {
    printf("\n>> Menu 2: Make Logic Circuit\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 2 */

    /*
    Ideas:

    Requires user input to select gate. With option to instead view gates if they don't know.
    Need to validate that input.
    Then, for that gate, need to decide inputs for the gate - e.g. pins.
    But if I print a picture of gate and say the pin labels to make it easy.
    Need to specify number of bits of input to get bits of rest of circuit - or go gate by gate
    If possible, display the current built circuit to make design easier - rather than gate by gate
    After a gate, choose to add more gates. Return to menu. Run test script. Test individual output.
    */


    /*
    Idea: make one function that can do all the possible gate functions,
    but the action it does depends on which gate is selected.

    Also: for every gate, store the labels in one big array and each label corresponds to a value in another big array
    (would be good to make an array of pointers - as done by char*) where each pointer is given a value.
    Then can assaign pointers to be equal to each other and perform operations on the pointers until an output is reached.
   
    OR: have an array of values and assign each pointer to a value.
    But if a pointer's value equals another pointer's name then it's assigned the same value and changes as the previous pointers do. Right?
    The question is how to check the pointer names.

    Probably easier to creat an array of character type labels which matches up exactly with an array of pointers of the same names or position.
    Where each pointe has a value which refers to a 1, 0 or another pointer's value
    (or combination of pointers' values as given by logic gate computations).


    ACTUALLY, the values are determined by test scripts.
    But the status of which labels are dictated by the test script and which are dictated by other pointers needs to be clear.
    If a label is NOT EWUAL TO a previous label, then its value should be made equal to,  say, -1
    to ensure that they are singled out for making the test scripts: because they are inputs.
    Also, if a label is at the end of the chain (no pointers use its value) then it should be marked as a output variable.
    */
   





    /*
   
    First, ask for which gate they'd like to add to circuit.
    Then print list of gates using print gates function.
    Then do select gates function.
    The pointer p now points to the gate they'd like to build.
    Use the data in the structs to do a for loop making/assigning labels for each of the NAMED inputs and outputs for the gate.
    Ask the user fo each label name (limit 10 characters)
    Store each label name in the global array of label names.
    Check through the array of names to see if the label names for any inputs or outputs are equal to those.
    If they are, make the value of the array (a pointer) equal to the value of the pointer of the thing its the same label as.
    If not, make the value equal to -1. This should separate inputs from internal pins.
    As for the output(s), need to update a metadata for each value array for the number of times that pointer has been referenced
    (just increment a value in a loop). The value which has not been referenced is therefore an output.

    NOTE: SHOULD keep duplicate pin labels for the sake of indexing the pointers.

    NOTE: need to store the pointers for each label in same ndex as the label, for simplicity, even though different arrays.

    Now that the labels have been dealt with, and the pointers and values for inputs have been worked out, now for outputs.

    Need to have ALL possible gate operations in a single function,
    the gte operation is selected using enum cases based on the gate selected by the user.
    The operation is carried out using the pointers for the inputs. And the output value is assigned to a pointer,
    which is stored in the same index as the label for the output.

    After doing this gate. Perhaps update the diagram?
    Or print a new diagram with the new gate shown next to the other gates if not linked up directly.

    Finally, ask the user if they'd like to add another gate to the circuit.
    If not, then run the make test script function IN THE BACKGROUND and notify the user that it's been made.
    Then return to MAIN (not main menu, to  reset the gate.) The only time main menu is returned to is when there's an error in the input.
    And the gate is not destroyed intermittently.


    -----------------
    Could alternatively add a new menu option for destroying the circuit, so that user could come back and add to it.

    Can't edit it though, can't delete or undo.
    -----------------

    */





    main(); // return to main at the end to reset all the gate labels and values
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
    printf("\n>> Menu 5: Generate Truth Table of Circuit\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 5 */
   
    /*
    First, check if a circuit exists, if not - return to menu
    Basically, just need to run the circuit for each possible input and record output in a table., (Print an array). Use iterative for loop from i of msb, j of less msb, ... z of lowest msb
    e.g. for i(...){ for j(...){ for z(... )}}

    */
}

void menu_item_6(void) {
    printf("\n>> Menu 6: Clear Circuit\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 6 */
   
    /*
    This function clears the array of labels and the array of values by setting all the values in the labels to "unassigned" and all the values in the values array to 0
    */

    for (int i; i<MAX_NUMBER_OF_IO_LABELS; i++){
    array_of_io_labels[i][10] = "unassigned"; /* setting all the values in the array of input & output labels to unassigned,
                                                 to ensure that the values are all reset before starting the next circuit */
    array_of_io_values[i] = 0; // setting all the values in the array of input & output values to 0. To reset all the values for the next circuit.
    }
}