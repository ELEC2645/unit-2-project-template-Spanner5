#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"


void menu_item_1(void) {
    printf("\n>> Menu 1: Logic Gate Information\n");

    /*
    First, a sub-menu for options to select the gates:  (select which gate to display information for (enter a number))
    2nd, for the user input number, validate it, etc - use existing functions to do that
    3rd, display info for the coresponding gate (use structs and pointers to select and print the gate info) - want a picture for each gate and info
    4th, asks if want to display another gate. If not, returns to menu.
    */

    // Selecting which gate the user wants info for

    printf("\nSelect which gate to display information for (enter a number)\n"); // getting user input
    print_gate_options();  // displaying the gate options
    important_constants number_of_possible_inputs = GATE_OPTIONS;
    int display_choice = get_user_input(number_of_possible_inputs); // retreiving and validating the input

    struct Gate *p = &NAND; // initialising a pointer for a gate, setting it to NAND by default
    select_gate(p, display_choice); // calls a function which points the pointer towards the correct gate

    // Firstly, let's display the ASCII logic gate diagram for the chosen gate
    // But to do that we need to determine the input labels for the gate:

    char inputs[p->n_inputs]; 
    char outputs[p->n_outputs];

    for (int y = 0; y < p->n_inputs; y++){
        inputs[y] = *p->input_names[y];
    }
    for (int z = 0; z < p->n_inputs; z++){
        outputs[z] = *p->output_names[z];
    }
    
    display_gate(p, inputs, outputs,0);

    // Now to display the rest of the gate information
    printf("\nName of Gate: %s",p->name);
    printf("\nNumber of NANDs used to make the gate: %d",p->n_nands);
    printf("\nNumber of inputs: %d",p->n_inputs);
    printf("\nNumber of outputs: %d",p->n_outputs);
    printf("\nInputs: %s",p->input_names);
    printf("\nOutputs: %s",p->output_names);
    printf("\nBoolean_representation: %s\n",p->Boolean_representation);
   
    printf("Would you like to display information for another gate?\n(Enter 1 for yes, 0 for no):    ");
    important_constants two_options = BINARY_CHOICE;
    int yes_no = get_user_input(two_options);
    if (yes_no == 1){
        menu_item_1();
    } else {
        printf("\nReturning to Main Menu\n");
        main_menu();
    }
}

void print_gate_options(void){
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

void display_gate(struct Gate *p, char* input_labels, char* output_labels, int create_file){
//void display_gate(struct Gate *p){

    char a; // initialising some arrays to store the lines of the logic gate diagrams in
    char b;
    char c;
    char d;
    char e;

    /*
    The logic gates have different diagrams and thus need to be displayed differently
    (for the purposes of handling/displaying the input and output pins.)
    */

    // Creating the first line of diagram
    if (p->name == "Mux"){
        a = "\n%s %s", input_labels[2], p->diagram[0];  
    }
    else if(p->name == "Demux"){
        a = "\n%s %s",input_labels[1], p->diagram[0];
    }
    else{
        a = " "; // the first line is redundant for non-muxes
    }
    printf("%s",a);

    // Creating the second line of diagram
    b = "\n/t %s",p->diagram[1];
    printf("%s",b);

    // Creating the third line of diagram
    if (p->name == "Demux"){
        c = "\n\t %s%s", p->diagram[2], output_labels[0];
    }
    else if (p->name == "NOT" || p->name == "Buffer"){
        c = "\n\t %s",p->diagram[2];
    }
    else{
        c = "\n%s %s", input_labels[0], p->diagram[2];
    }
    printf("%s",c);

    // Creating the fourth line of diagram
    if (p->name == "Demux"){
        d = "\n%s %s", input_labels[0], p->diagram[3];
    }
    else if (p->name == "NOT" || p->name == "Buffer"){
        d = "\n%s %s %s", input_labels[0], p->diagram[3], output_labels[0];
    }
    else{
        d = "\n\t %s%s",p->diagram[3], output_labels[0];
    }
    printf("%s",d);

    // Creating the fifth line of diagram
    if (p->name == "Demux"){
        e = " \n%s %s", p->diagram[4], output_labels[1];
    }
    else if (p->name == "NOT" || p->name == "Buffer"){
        e = "\n\t %s",p->diagram[4];
    }
    else{
        e = "\n%s %s", input_labels[1], p->diagram[4];
    }
    printf("%s",e);

    /*
    Now, if the gate is the once customized by the user (rather than a reference image)
    then the gate's image should be saved to a text file as a record of the circuit.
    */
    if (create_file){
        char gate_data[7] = {"\n\n\n",a,b,c,d,e,"\n\n\n"}; // collate all the lines of the diagram together
        write_to_circuit_file(gate_data); // write the diagram to the text file
    }

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

    create_circuit_file(); // creating the text file for the gate

    printf("Select a logic gate to add to the circuit.");

    // Code to select and display chosen logic gate:
        print_gate_options();  // displaying the gate options
        important_constants number_of_possible_inputs = GATE_OPTIONS;
        int gate_choice = get_user_input(number_of_possible_inputs); // retreiving and validating the input - a number corresponding to the correct gate
        struct Gate *p = &NAND; // initialising a pointer for a gate, setting it to NAND by default
        select_gate(p, gate_choice); // calls a function which points the pointer towards the correct gate

        // NOW TO DISPLAY THE GATE
        char inputs = *p->input_names;
        char outputs = *p->output_names;
        display_gate(p, &inputs, &outputs,0);
        
    // Now, code to ask the user to create labels for the gate

        int x; // establishing an incrementer for a while loop
        int first_output_index; // establishing a variable that will hold the index of the first output

        char names_of_inputs[p->n_inputs]; // creating 2 empty arrays for storing the input and output labels for this specific gate,
        char names_of_outputs[p->n_outputs]; // The size of the array has been set to the number of inputs and outputs for the selected gate.
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
            printf("\nPlease provide a label/name for INPUT pin %s of the gate. (Each label is limited to %d characters):     ", p->input_names[j], MAX_LABEL_LENGTH); // Note: if referencing the same pin twice (e.g for an output used as an input),
                                                                                    // then need to match the name character for character - or at least .upper()
            char inputlabel[MAX_LABEL_LENGTH] = {}; //limit of 15 characters
            fgets(inputlabel, sizeof(inputlabel), stdin); // got the label name for input

            names_of_inputs[j] = inputlabel; // storing the input labels in the array to use for displaying the gate with labels filled in

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
                                                              (if this was an output, it's not a "true" output from the system to elsewhere)*/
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
            printf("\nPlease provide a label/name for INPUT pin %s of the gate. (Each label is limited to %d characters):     ", p->output_names[l], MAX_LABEL_LENGTH);
            // Note: if referencing the same pin twice (e.g for an output used as an input),
            // then need to match the name character for character - or at least .upper()

            char outputlabel[MAX_LABEL_LENGTH] = {}; //limit of 15 characters
            fgets(outputlabel, sizeof(outputlabel), stdin); // got the label name for output
           
            strcpy(array_of_io_labels[first_output_index + l][2], "External"); /* Because the outputs are new, and haven't yet been used as a input,
                                                                        their connections are external and thus a "TRUE" output from the circuit  */
            strcpy(array_of_io_labels[first_output_index + l][0], outputlabel); // naming the output gate using the user input

            names_of_outputs[l] = outputlabel; // storing the output labels in the array to use for displaying the gate with labels filled in

            // checking if an output variable has ALREADY been used as an input (in the case of feedback)
            x = 0;
            while ( x<MAX_NUMBER_OF_IO_PINS){
                // first, need to check if the label has already an existing pin, checking through whole array of labels
                if (array_of_io_labels[x][0] == outputlabel){
                    for (int m = 0; m<6; m++){ // 6 is number of parameters in each io label array for a single pin
                        strcpy(array_of_io_labels[x][m], "destroyed"); /* resetting the pin to avoid duplicates.
                                                                 The original had less information, so it was destroyed.*/
                    }
                    x = 999; // original pin destroyed, job done, so break the condition of the while loop
                }
            } // Feedback probably isn't possible with this version of the code, but that's not a main part of it,
              // there aren't currently clock cycles anyway.
        }
        
        /*char inputs[p->n_inputs]; 
        char outputs[p->n_outputs];

        for (int y = 0; y < p->n_inputs; y++){
            inputs[y] = names_of_inputs[y];
        }
        for (int z = 0; z < p->n_inputs; z++){
            outputs[z] = names_of_outputs[z];
        }*/
        
        // Now, let's display the ASCII logic gate diagram for the chosen gate and save it to the text file
        int create_file = 1;
        display_gate(p, names_of_inputs, names_of_outputs, create_file);   

        does_circuit_exist = 1; /* This updates the status and allows for functions to run the circuit
                                - provided no other factors are  unsatisfied */

        // Before finally exiting to the main menu, ask the user if they'd like to add another gate to the circuit
        
        printf("Would you like to add a new gate to the circuit or return to main menu? Enter 1 for yes, 0 for no:   ");
        int choice = get_user_input(BINARY_CHOICE);

        switch (choice) {
            case 1:
                menu_item_2(); // if they want to add another gate, then recall the function
            case 2:
                main_menu();
            default:
                printf("Invalid input! Returning to main menu.\n(You can always add to the circuit after it runs).\n");
                main_menu();
        }
}

void menu_item_3(void) {
    printf("\n>> Menu 3: Circuit Testing\n");

    // Before running this menu's functionality, we need to check if there's actually a circuit for this test script
    if (does_circuit_exist = 0){
        printf("\nThere is no circuit detected. Please make a circuit before making and running a test script.\nReturning to Main Menu.\n");
        main_menu();
    }

    /*
    // Now, ask the user if they'd like to make or run the test script or generate a truth table for the circuit
    printf("\nPlease select a function:\n\n");
    print_circuit_testing_menu();
    printf("\nEnter a number:   ");
    int option = get_user_input(CIRCUIT_TESTING_MENU_ITEMS);
    */







    /*
    Allows user to enter to decide how many variables, variable names, outputs, then the variables will increment as normal, but the user will enter the output value for each output on a row
    */

    // First, create an array of input labels based on user input

    printf("\nFirstly, how many INPUTS are there to the circuit (not including internal pins between logic gates)?\nEnter a single number:    ");
    int Ninput;
    scanf("%d",&Ninput); // Scanf should suffice, because we just want a single integer

    printf("\nPlease enter the label names for each INPUT one at a time when prompted.\nEach label is limited to %d characters.\nNOTE: Please make sure that the input pin labels entered here match the input pin labels of the circuit - or the program WILL BREAK\n.",MAX_LABEL_LENGTH);
    char array_of_input_labels[Ninput][MAX_LABEL_LENGTH]; /* the size of the array is determined by how many inputs the user makes,
                                                             which makes it more memory efficient and easier to insert the user inputs*/
    
    for (int i = 0; i < Ninput; i++){
        printf("\nEnter the label name for INPUT number %d:   ",i+1);
        fgets(array_of_input_labels, MAX_LABEL_LENGTH, stdin); // stores the input label name in the array of input labels
    }

    // Second, create an array of outputs based on user input

    printf("\nFirstly, how many OUTPUTS are there from the circuit (not including internal pins between logic gates)?\nEnter a single number:    ");
    int Noutput;
    scanf("%d",&Noutput); // Scanf should suffice, because we just want a single integer

    printf("\nPlease enter the label names for each OUTPUT one at a time when prompted.\nEach label is limited to %d characters.\nNOTE: Please make sure that the input pin labels entered here match the input pin labels of the circuit - or the program WILL BREAK\n.",MAX_LABEL_LENGTH);
    char array_of_output_labels[Noutput][MAX_LABEL_LENGTH]; /* the size of the array is determined by how many inputs the user makes,
                                                            which makes it more memory efficient and easier to insert the user inputs*/
    
    for (int j = 0; j < Noutput; j++){
        printf("\nEnter the label name for OUTPUT number %d:  ",j+1);
        fgets(array_of_output_labels, MAX_LABEL_LENGTH, stdin); // stores the input label name in the array of input labels
    }

    /*
    The next step is to ask the user the output values for each combination of input values
    this will be done with a for loop so the prompt has to be given outside it:
    */

    printf("\nFor each of the following combinations of inputs, please enter the value of the outputs as they appear.\nJust enter a 1 or 0.");

    // Now, we need to create all the possible input combinations
    
    int number_of_input_combinations = pow(2, Ninput); // 2 to the power of the Number of inputs

    /*
    Will use number_of_input_combinations, to create an array of all the possible input combinations. 
    And for each input combination, will ask the user what the output values should be - and make an array of expected outputs.
    When it comes to running the circuit, the outputs will be created.
    So when the test script is run
    - the outputs corresponding to the labels for the outputs will be read off into an array of actual outputs and compared.
    For the Generate Truth Table function, the only difference is that
    the actual outputs are printed next to the other inputs like - but not actually - a test script.
    */

    int array_of_input_combos[number_of_input_combinations][Ninput]; // This array will contain each combination of inputs as a row, and each inputs value as a column
    int array_of_expected_outputs[number_of_input_combinations][Noutput]; // Also, the array of expected outputs has as many rows as there are input combinations
    int array_of_actual_outputs[number_of_input_combinations][Noutput]; // Additionally, the array of actual outputs will have the same dimensions as the array of expected outputs

    /*
    need to begin with row 1, everything is zero. Then increment the last value in the row.
    Then, if that last value is one on prev row, increment the value before it and set it to 1
    - continues till all values are 1.
    */

    // Now, incrementing the values of the inputs for each row.
    for (int k = 1; k < number_of_input_combinations; k++){ // For each row of inputs

        /*
        k = the VALUE of the input combination,
        e.g. the 8th input combo of 3 bits is 111 - which is k = 7 and 111 is 7 in binary.
        So, just subtract the value of each bit from k to get the value of each bit in the value.
        */

        int combo_value = k;
        // need to relate each bit to a multiplier based on Ninput - the position ,then subtract from k
        
        for (int l = 0; l < Ninput; l++){ // For each input in a row

            int value_of_bit = pow(2, Ninput - l); // e.g. for 4 bits, the 0th bit (the HSB) has value 8. Which is 2^(4-1).

            if (combo_value - value_of_bit >= 0 ){  // In this case, the bit is less than or equal to the combination value (e.g. combination 7, or 00000111)
                array_of_input_combos[k][l] = 1;    // So, the bit can be used to represent part of this value.
                combo_value = k - value_of_bit;     // The remaining value of the combination is then compared to the other bit values until it's been represented
            }
            else if (combo_value - value_of_bit < 0 ){ // Eventually, once the combination value will have been represented by bits. Any following bits are 0.
                array_of_input_combos[k][l] = 0;
            }
        }

        // Now that the input bits for this combination have been established, we need to establish the outputs.
        // We want the user to enter the output values for each input combination as it comes.

        // The first part of the test script will be all the pin labels at the top
        printf("\nWhen:\n%s\n%s\n",array_of_input_labels,array_of_input_combos);

        for (int m = 0; m < Noutput; m++){
            printf("\nWhat is the value of %s:  ",array_of_output_labels[m]);
            array_of_expected_outputs[k][m] = get_user_input(BINARY_CHOICE);
        }
    }   
    printf("\n\nFinal Test Script:\n%s %s\n",array_of_input_labels,array_of_output_labels);
    for (int n = 0; n < number_of_input_combinations; n++){
        printf("\n%s %s\n\n",array_of_input_combos[n], array_of_expected_outputs[n]);
    }
    
    // NEED TO SEND THESE SOMEWHERE: return array_of_input_labels, array_of_output_labels, array_of_input_combos, array_of_expected_outputs;

    // Now, we'll use the test script to evaluate the circuit

    // For each set of inputs, need to run the circuit, find the output values and store in new array
    for (int o = 0; o < number_of_input_combinations; o++){

        /*
        First, we need to assign the values relating to the input pins (in the smaller array: input values array) to
        the values relating to to the input pins in the larger: array of io values.
        We'll need to use the array of io labels and the array of input labels to find the correct slots.
        */
        for (int p = 0; p < MAX_NUMBER_OF_IO_PINS; p++){ // looping through the larger array of all pin labels
            for (int q = 0; q < Ninput; q++){ // looping through the smaller array of input pin values
                if (array_of_input_labels[q] == array_of_io_labels[p][0]){ // If the input label in the SMALLER array matches the pin label in the LARGER array...
                    array_of_io_values[p] = array_of_input_combos[q][0];   // ...then the value of that pin from the SMALLER array gets copied to the value of that pin in the LARGER array 
                }          
            }
        }

        // Now that the inputs to the circuit have been entered (for THIS combination of inputs), the circuit will be run to generate the outputs 
        run_circuit();

        /*
        In order to get the actual outputs for each set of inputs, the reverse process is applied.
        The larger array of io labels is looped through and compared with the labels of the output pins from a smaller array.
        If they match, then the value of corresponding to the output pin is copied from a LARGE array of pin values to the SMALLER array of output pin values.
        The array can then be printed with the rest of the test script and also compared with the array of predicted outputs to show where they differed.
        */
        for (int p = 0; p < MAX_NUMBER_OF_IO_PINS; p++){ // looping through the larger array of all pin labels
            for (int q = 0; q < Noutput; q++){ // looping through the smaller array of output pin values
                if (array_of_output_labels[q] == array_of_io_labels[p][0]){ // If the output label in the SMALL array matches the pin label in the LARGER array...
                    array_of_actual_outputs[q][0] = array_of_io_values[p];   // ...then the value of that output pin from the LARGE array gets copied to the value of that pin in the SMALLER array 
                }          
            }
        }
    }
    
    char results[number_of_input_combinations +1]; // Initialising an array to store the results inside of
   
    // Now to print the results of the test & storing them in the results array
    results[0] = "\n\nFinal Test Script:\n%s Expected Ouptuts:%s\tActual Outputs:%s\n",array_of_input_labels,array_of_output_labels,array_of_output_labels; // storing the variables names in the results array
    printf(results[0]); // Printing the variable names at the top of the results table

    int number_of_discrepancies = 0;

    for (int n = 0; n < number_of_input_combinations; n++){
        results[n+1] = "\n%s %s\t\t\t%s\t\t",array_of_input_combos[n], array_of_expected_outputs[n],array_of_actual_outputs[n]; // storing a line of results in the array
        printf(results[n+1]); // printing the results from the array

        // Additionally, we can compare the number of discrepancies between expected and actual outputs
        for (int v = 0; v < Noutput; v++){
            if (array_of_expected_outputs[n][v] != array_of_actual_outputs[n][v]){ // if epected output is not equal to actual output
                number_of_discrepancies++;
                printf("\nThe ACTUAL output in row %d down & column %d across is not equal to the expected output.\n",n+1,v+1); // using +1 because of the indexing starting at zero
            }
        }
    }
    
    // Now to ask the user if they'd like to save these results to a text file
    printf("\nWould you like to save the test results?\nEnter 1 for yes, 0 for no:  ");
    int save_results = get_user_input(BINARY_CHOICE);
    if (save_results){
        create_test_script_file();
        write_to_test_script_file(results);
    }
}

static void print_circuit_testing_menu(void)
{
    printf("\n---------- Circuit Testing Menu ----------\n");
    printf("\n"
           "\t\t\t\t\t\t\n"
           "\t1. Make Test Script\t\t\n"
           "\t2. Run Test Script\t\t\n"
           "\t3. Generate Truth Table of Circuit\t\t\n"
           "\t4. Exit to Main Menu\t\t\n"
           "\t\t\t\t\t\t\n");
    printf("---------------------------------------------\n");
}

void run_circuit(void){
    /*
    Loop through the pin_label array until hit unassigned for the value.
    For each pin label, use its corresponding index in the value array and set it equal to the operation
    (decided by the gate label) of the values in the labels (addresses) of the input pins.
    */

    int i = 0;
    int j;
    int input_1;
    int input_2;
    int input_3;
    while(i<MAX_NUMBER_OF_IO_PINS && array_of_io_labels[i][0] != "unassigned"){ // looking through all pins that have been used
        
        /*
        --------------------
         Still need to find a way to input the inputs using a test script format.
        --------------------
        */

        /* 
        Will create an array of input values corresponding to the array of input labels - for the test script/truth table.
        Will loop through the array of input labels and see if they match any of the pin labels from the array_of_io_labels.
        If they do, then the value given to the input value for that input is copied to the array of io values for use in running the circuit.

        For reading the output values, the reverse process is applied. The array of outputs will be used to loop through the array of io labels,
        and where the two match, the value from the array of io values will be copied to a new output values array.
        From which they can be printed in a truth table, compared with values in a test script or whatever.
        
        But the output values can be read in a different function. 

        */
        
        if (array_of_io_labels[i][0] != "destroyed" && array_of_io_labels[i][3] == "unassigned"){
            /* only do the following if a pin has not been destroyed and is not a pure input.
            ("Pure input" means a pin is not created as an output of any gate, so the 1st input pin for the pin's labels must be unassigned) */

            // i = the position of the pin we're currently focusing on - also it is by desgin the position of the pin value for this pin in the array_of_io_values

            j = 0;
            while (j<MAX_NUMBER_OF_IO_PINS && array_of_io_labels[j][0] != "unassigned"){ // again, looking through all pins that have been used

                if (array_of_io_labels[j][0] == array_of_io_labels[i][3]){ // if the current pin label in the array is equal to the 1st input label of the pin we're currently focusing on
                    input_1 = array_of_io_values[j];                   // then the corresponding pin value of the pin label is taken as an input value for the pin we're currently focusing on.
                }
                if (array_of_io_labels[j][0] == array_of_io_labels[i][4]){ // if the current pin label in the array is equal to the 2nd input label of the pin we're currently focusing on
                    input_2 = array_of_io_values[j];                   // then the corresponding pin value of the pin label is taken as an input value for the pin we're currently focusing on.
                }
                if (array_of_io_labels[j][0] == array_of_io_labels[i][5]){ // if the current pin label in the array is equal to the 3rd input label of the pin we're currently focusing on
                    input_3 = array_of_io_values[j];                   // then the corresponding pin value of the pin label is taken as an input value for the pin we're currently focusing on.
                }
            }
            
            // Now that we've found the inputs for the pin, we need to pass them through the correct logic gate to generate the pin value
            // To decide the gate, we use the gate label to choose.

            char gate_label = array_of_io_labels[j][1];
            if (gate_label == "NAND"){
                array_of_io_values[i] = ~(input_1 & input_2);
            }
            else if (gate_label == "NOT"){
                array_of_io_values[i] = ~input_1;
            }
            else if (gate_label == "AND"){
                array_of_io_values[i] = input_1 & input_2;
            }
            else if (gate_label == "OR"){
                array_of_io_values[i] = input_1 | input_2;
            }
            else if (gate_label == "XOR"){
                array_of_io_values[i] = input_1 ^ input_2;
            }
            else if (gate_label == "Buffer"){
                array_of_io_values[i] = input_1;
            }
            else if (gate_label == "Mux"){

                if (input_3 == 0){
                    array_of_io_values[i] = input_1;
                }
                else if (input_3 == 1){
                    array_of_io_values[i] = input_2;
                }
            }
            else if (gate_label == "Demux"){
                
                /*
                Need to check WHICH output of the demux this is. So, let's see if there is a previous mux output with the SAME inputs.
                If there isn't a previous mux with the same inputs, then this output is Y0.
                If there is, then the previous output is Y0. So this output is Y1.
                We'll need to look at the labels either side of this input's labels.
                */
                int match = 0;
                for (int a = 1; a < NUMBER_OF_PIN_LABELS ; a++ ){
                    if(array_of_io_labels[i][a] == array_of_io_labels[i+1][a]){ // checking if this pin's labels match the labels of the next pin
                        match++; // in which case, this output is the 1st demux output Y0
                    }
                    if(array_of_io_labels[i][a] == array_of_io_labels[i-1][a]){ // checking if this pin's labels match the labels of the previous pin
                        match--; // in which case, this output is the 2nd demux output Y1
                    }
                    else{
                        printf("The mux outputs need to be determined better"); // this means I've coded something wrong
                        exit(1);
                    }
                }

                switch (match){
                    case +5:                                // Y = Y0:
                        if (input_2 == 0){                      // select == 0:
                            array_of_io_values[i] = input_1;        // Y0 = A
                        }
                        else if (input_2 == 1){                 // select == 1:
                            array_of_io_values[i] = 0;              // Y0 = 0
                        }
                    case -5:                                // Y = Y1:
                        if (input_2 == 0){                      // select == 0:
                            array_of_io_values[i] = input_1;        // Y1 = 0
                        }
                        else if (input_2 == 1){                 // select == 1: 
                            array_of_io_values[i] = 0;              // Y1 = A
                        }
                }
            }
        }
        i++; /* Increment i after each pin value has been decided. 
                After going through all the pins, the output should have been generated. */
    }
}

void Generate_Truth_Table(void) {
    printf("\n>> Circuit Testing Menu 3: Generate Truth Table\n");

    /*
    First, check if a circuit exists, if not - return to menu.
    Will run 
    Basically, just need to run the circuit for each possible input and record output in a table., (Print an array). Use iterative for loop from i of msb, j of less msb, ... z of lowest msb
    e.g. for i(...){ for j(...){ for z(... )}}

    */
}

void menu_item_4(void) {
    printf("\n>> Menu 4: Clearing previous circuit...\n");

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

int create_circuit_file() {
   
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

int write_to_circuit_file(char custom_gate) {
   
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

int create_test_script_file() {
   
    // File pointer
    FILE* fptr;

    // Creating file using fopen()
    // with access mode "w"
    fptr = fopen("Test Script.txt", "w");

    // checking if the file is created
    if (fptr == NULL)
        printf("The file is not opened.");
    else
        printf("The file is created Successfully.");
    return 0;
}

int write_to_test_script_file(char text) {
   
    // File pointer
    FILE* fptr;

    // Creating file using fopen()
    // with access mode "w"
    fptr = fopen("Test Script.txt", "w");

    // Checking if the file is created
    if (fptr == NULL)
        printf("The file is not opened.");
    else{
        //printf("The file is now opened.\n"); - not going to use this line
        fputs(text, fptr);
        fputs("\n", fptr);

        // Closing the file using fclose()
        fclose(fptr);
        printf("Circuit has been updated\n");
        // printf("The file is now closed."); - not going to use this line
    }
    return 0;
}