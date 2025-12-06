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
   
    // chose not to, because when making circuit, pointers are made based off of value anyway.
    // But feedback loops might now be impossible. But they weren't ever really.

    NOTE: need to store the pointers for each label in same ndex as the label, for simplicity, even though different arrays.

    Now that the labels have been dealt with, and the pointers and values for inputs have been worked out, now for outputs.


111111111111111111111111111111111111111111111111111111111111

    Need to have ALL possible gate operations in a single function,
    the gate operation is selected using enum cases based on the gate selected by the user.
    The operation is carried out using the pointers for the inputs. And the output value is assigned to a pointer,
    which is stored in the same index as the label for the output.

    After doing this gate. Perhaps update the diagram?
    Or print a new diagram with the new gate shown next to the other gates if not linked up directly.

    Finally, ask the user if they'd like to add another gate to the circuit.
    If not, then run the make test script function IN THE BACKGROUND and notify the user that it's been made.
    Then return to main menu.

111111111111111111111111111111111111111111111111111111111111


    -----------------
    Could alternatively add a new menu option for destroying the circuit, so that user could come back and add to it.

    Can't edit it though, can't delete or undo.
    -----------------

    */

    printf("Select a logic gate to add to the circuit.");

    // Code to select and display chosen logic gate:
        print_gates();  // displaying the gate options
        menu_items number_of_possible_inputs = GATE_OPTIONS;
        int gate_choice = get_user_input(number_of_possible_inputs); // retreiving and validating the input - a number corresponding to the correct gate
        struct Gate *p = &NAND; // initialising a pointer for a gate, setting it to NAND by default
        select_gate(p, gate_choice); // calls a function which points the pointer towards the correct gate



        // NOW CALL FUNCTION FOR DISPLAYING THE GATE --- use "Input 1", etc to represent that the labels have not been assigned yet
 


    // Now, code to ask the user to create labels for the gate

        int x; // establishing an incrementer for a while loop
        int first_output_index; // establishing a variable that will hold the indedx of the first output

        char input_names[p->n_inputs]; // creating 2 empty arrays for storing the input and output labels for this specific gate,
        char output_names[p->n_outputs]; // The size of the array has been set to the number of inputs and outputs for the selected gate.
        //printf("");

        // 1st, priming the new output pins and finding an available slot for their index in the label list (so that we can store the labels for them)

        x = 0; // initialising x's value
        while ( x<MAX_NUMBER_OF_IO_PINS){

            // Also, before assignning any pins. We need to check whether there are enough empty slots to actually build the logic gate.
            if (x + p->n_inputs + p->n_outputs >= MAX_NUMBER_OF_IO_PINS - 1){ // which is in the event of there not being enough unassigned slots for pins
                printf("Number of existing Pin Labels: %d/%d\nBuilding this logic gate would exceed the maximum number of pin labels.\nSorry, the logic gate cannot be built.\nExiting to main menu.",x+1,MAX_NUMBER_OF_IO_PINS);
                main_menu();
            }

            // Now to prime the output slots
            else if (array_of_io_labels[x][0] != "unassigned"){ // looking for the first unassigned pin label slot
                for (int i = 0; i< p->n_outputs; i++){ // for each of the outputs...    
                    strcpy(array_of_io_labels[x][0], "temp"); // ..if unassigned, fill in the output pin labels with a temporary marker, and to stop any new inputs from filling the slot
                }
                first_output_index = x; // recording the index of the 1st output of this gate to use later when assign labels to it and the other outputs
                x = 999; // break the condition of the while loop and exit the loop because the ouput pins are now ready
            }
            x++;
        }

        // 2nd, managing the input pins
        for (int j = 0;j< p->n_inputs;j++){
            printf("\nPlease provide a label/name for an INPUT pin of the gate:     "); // Note: if referencing the same pin twice (e.g for an output used as an input),
                                                                                    // then need to match the name character for character - or at least .upper()
            char inputlabel[MAX_LABEL_LENGTH] = {}; //limit of 10 characters
            fgets(inputlabel, sizeof(inputlabel), stdin); // got the label name for input

            input_names[j] = inputlabel; // storing the input labels in the array to use for displaying the gate with labels filled in

            // Now to assign the input pin label name to a label in the io_label array
            // Need to search through the array for the first slot where there is no pin label already filled

            x = 0; // resetting & reusing x to avoid creating an unnecessary variable

            while ( x<MAX_NUMBER_OF_IO_PINS){
                // first, need to check if the label has already an existing pin, checking through whole array of labels
                if (array_of_io_labels[x][0] == inputlabel){
                    x = 999; // no need to create a new pin if it already exists, so break the condition of the while loop
                }

                else if (array_of_io_labels[x][0] != "unassigned"){ // looking for the first unassigned pin label slot
                    strcpy(array_of_io_labels[x][0], inputlabel); // if unassigned, fill in the pin label with the user input
                    x = 999; // break the condition of the while loop and exit the loop because the input label is now made
                }
                strcpy(array_of_io_labels[x][2], "Internal"); /* Marking the input as an input to the system and therefore works internally
                                                       (not a "true" output from the system to elsewhere)*/
                x++;
            }

            // 3rd, storing labels in the the output pins
            for (int k = 0; k< p->n_outputs; k++){ // for each of the outputs...
                strcpy(array_of_io_labels[first_output_index + k][3 + j], inputlabel);
                /* In the above line, the output slots, starting from the indexed slot (& continuing up to the last (kth) output)
                (hence [first_output_index + k] ),the jth input label is placed in the jth input label slot (not the pin name/label,
                but the slot for storing the inputs used to create a pin) of the output pin
                (which starts at the 4th slot of a given output label array, hence [1 + j]).
                So, each input for a given output has its label stored in the output's label array for later use in using the gates later.
                */
                strcpy(array_of_io_labels[first_output_index + k][1], p->name); // recording the gate type in the slot for gate types in the output's label array
            }
        }

        // 4th managing the output pins fully
        for (int l = 0; l< p->n_outputs; l++){ // for each of the outputs...
            printf("\nPlease provide a label/name for an OUTPUT pin of the gate:     "); // Note: if referencing the same pin twice (e.g for an output used as an input),
                                                                                         // then need to match the name character for character - or at least .upper()
            char outputlabel[MAX_LABEL_LENGTH] = {}; //limit of 10 characters
            fgets(outputlabel, sizeof(outputlabel), stdin); // got the label name for output
           
            strcpy(array_of_io_labels[first_output_index + l][2], "External"); /* Because the outputs are new, and haven't yet been used as a input,
                                                                        their connections are external and thus a "TRUE" output from the circuit  */
            strcpy(array_of_io_labels[first_output_index + l][0], outputlabel); // naming the output gate using the user input

            output_names[l] = outputlabel; // storing the output labels in the array to use for displaying the gate with labels filled in

            // checking if an output variable has ALREADY been used as an input (in the case of feedback)
            x = 0;
            while ( x<MAX_NUMBER_OF_IO_PINS){
                // first, need to check if the label has already an existing pin, checking through whole array of labels
                if (array_of_io_labels[x][0] == outputlabel){
                    for (int m = 0; m<6; m++){ // 6 is number of parameters in each io label array for a single pin
                        strcpy(array_of_io_labels[x][m], "unassigned"); /* resetting the pin to avoid duplicates.
                                                                 The original had less information, so it was destroyed.*/
                    }
                    x = 999; // original pin destroyed, job done, so break the condition of the while loop
                }
            } // Feedback probably isn't possible with this version of the code, but that's not a main part of it,
              // there aren't currently clock cycles anyway.
        }
   
        // NOW CALL FUNCTION FOR DISPLAYING THE GATE

       

        // Will ALSO NEED A FUNCTION FOR MAKING, SAVING AND DISPLAYING THE CIRCUIT TEXT FILE after EACH GATE



        // Now, can make a separate function for determining the workings of interconnected gates and the nature of raw inputs.

        run_circuit();


    main_menu(); // return to main_menu at the end
}

void run_circuit(void){

    /*
    Loop through the pin_label array until hit unassigned for the value.
    For each pin label, use its corresponding index in the value array and set it equal to the operation
    (decided by the gate label) of the values in the labels (addresses) of the input pins.
    */

    int i = 0;
    while(i<MAX_NUMBER_OF_IO_PINS & array_of_io_labels[i][0] != "unassigned"){
        int index_of_pin_value = i;

    }

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
    printf("\n>> Clearing previous circuit...\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 6 */
   
    /*
    This function clears the array of labels and the array of values by setting all the values in the labels to "unassigned" and all the values in the values array to 0
    */
    int n = 6; // n is the number of parameters in the sub arrays in the array of labels. Can be adjusted to scale for more inputs.
    for (int i; i<MAX_NUMBER_OF_IO_PINS; i++){           // An overarching for loop that goes through the whole label array
        for (int j; j<n; j++){                             // Now looping through the array in position i of the labels array      
            strcpy(array_of_io_labels[i][j],"unassigned");  // Setting each value in that array to "unassigned". To reset the values to a known default.
        }

        //strcpy(array_of_io_labels[i][j],"unassigned");  --- This is the correst way to overwrite a string

        //array_of_io_labels[i][j] = "unassigned";  --- This doesn't work because you can't just reassign the string

        /* setting all the values in the array of input & output labels to unassigned,
        to ensure that the values are all reset before starting the next circuit */

        array_of_io_values[i] = 0; // setting all the values in the array of input & output values to 0. To reset all the values for the next circuit.
    }
    /*
    Syntax: array_of_io_labels[i] = [pin_label, gate_type, internal_or_external_output?, input_1, input_2, input_3] // should I add is output or is input to the label?
    */
   
    /*
    Note: can determine if a pin is an external input if it has no inputs into the pin,
    and can determine an output if the internal_or_external_output? value is still 1
    (if zero or less, it's an internal output or an input).

    Because an output is created with an internal_or_external_output? value of 1,
    and every time an existing pin is used as an input, the value is taken down by -1.
    So, this means that anything that is not purely an external output, will be less than 1.

    OR, in the case of characters, just reset the value to a different string (like internal).

    For feedback loops, this might damage the code recognising outputs...
    */

    }



int create_file() {
   
    // File pointer
    FILE* fptr;

    // Creating file using fopen()
    // with access mode "w"
    fptr = fopen("Circuit.txt", "w");

    // checking if the file is created
    if (fptr == NULL)
        printf("The file is not opened.");
    else
        printf("The file is created Successfully.");
    return 0;
}

int write_to_file(custom_gate) {
   
    // File pointer
    FILE* fptr;

    // Creating file using fopen()
    // with access mode "w"
    fptr = fopen("Circuit.txt", "w");

    // Checking if the file is created
    if (fptr == NULL)
        printf("The file is not opened.");
    else{
        //printf("The file is now opened.\n"); - not going to use this line
        fputs(custom_gate, fptr);
        fputs("\n", fptr);

        // Closing the file using fclose()
        fclose(fptr);
        printf("Circuit has been updated\n");
        // printf("The file is now closed."); - not going to use this line
    }
    return 0;
}