#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

void menu_item_1(void) {
    printf("\n>> Menu 1: Logic Gate Information\n");

    /* This function does:

    1st, prints a sub-menu for options to select the gates and asks the user to enter a number to pick one.
    2nd, gets the user input number & validates it.
    3rd, displays info for the coresponding gate (using structs and pointers to select and print the gate info).
         Also an image of the chosen gate is displayed onscreen.
    4th, asks the user if they want to display another gate's information. If not, returns to menu.
    */

    // Selecting which gate the user wants info for

    print_gate_options();  // Firstly, the gate options are displayed

    printf("\nSelect which gate's information to display\n(Enter a number):     "); // The user is then asked which gate they want to see
    int display_choice = get_user_input(GATE_OPTIONS); // Retreiving and validating the input using the get_usser_input function

    struct Gate *p = &NAND; // initialising a pointer for a gate, setting it to NAND by default
    select_gate(p, display_choice); // calls a function which points the pointer towards the chosen gate - which is determined using the user input

    // Firstly, the ASCII logic gate diagram is displayed for the chosen gate
    // But to do that we need to determine the input labels for the gate:

    char inputs[p->n_inputs];   // The lengths of the arrays of inputs and outputs are determined by the struct the pointer is pointing to.
    char outputs[p->n_outputs]; // This way, excess memory is not used up.

    for (int y = 0; y < p->n_inputs; y++){
        inputs[y] = *p->input_names[y]; // Rach label in the inputs array is assigned by using the dereferenced pointer to a struct with an array of input names.
    }
    for (int z = 0; z < p->n_inputs; z++){
        outputs[z] = *p->output_names[z]; // The same is done for the outputs array.
    }
    
    display_gate(p, inputs, outputs,0); /* The gate is then displayed.
                                           The pointer to the gate, the inputs and outputs arrays are all passed to the function,
                                           as well as a control value set to zero.
                                           This value means the gate is not written to the text file of the circuit. */

    // Now to display the rest of the gate information using pointers to the selected struct
    printf("\nName of Gate: %s",p->name);
    printf("\nNumber of NANDs used to make the gate: %d",p->n_nands);
    printf("\nNumber of inputs: %d",p->n_inputs);
    printf("\nNumber of outputs: %d",p->n_outputs);
    printf("\nInputs: %s",p->input_names);
    printf("\nOutputs: %s",p->output_names);
    printf("\nBoolean_representation: %s\n",p->Boolean_representation);
   

    // Finally, the user is asked if they'd like to see informstion for another gate.
    printf("Would you like to display information for another gate?\n(Enter 1 for yes, 0 for no):    ");
    important_constants two_options = BINARY_CHOICE;
    int yes_no = get_user_input(two_options);
    if (yes_no == 1){ 
        menu_item_1(); // If they say yes, then the function is repeated and the user can pick another gate to display infor for.
    } else {          
        printf("\nReturning to Main Menu\n"); // Otherwise, return to the main menu.
        main_menu(); 
    }
}

void print_gate_options(void){  // Self-explanatory
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

    /* This function:

    Creates multiple character arrays which vary depending on the chosen gate.

    These arrays are first inisitalised.
    Then assigned different characters depending on the type of gate the pointer is pointing at.
    
    Each array represents a single line of my ASCII representation of a gate.

    If the create_file value is 1, then the arrays are collated into a new array of arrays called gate data.
    Then gate data is written to the circuit's text file so that the user can look back on their gate design in future.

    The gates in the circuit text file do not visuallt link up together.
    But, the whole program is designed so that if the user enters the same pin label for 2 gates,
    then it gets used for 2 gates - allowing the value to be transferred between gates and thus make a functioning logic circuit.
    */

    char a; // initialising some arrays to store the lines of the logic gate diagrams in
    char b;
    char c;
    char d;
    char e;

    /* The logic gates have different diagrams and thus need to be displayed differently
    (for the purposes of handling/displaying the input and output pins.) */  

    // Creating the first line of diagram
    if (*p->name == "Mux"){
        a = "\n", input_labels[2]," ", *p->diagram[0];  
    }
    else if(*p->name == "Demux"){
        a = "\n",input_labels[1]," ", *p->diagram[0];
    }
    else{
        a = " "; // the first line is redundant for non-muxes
    }
    printf("%s",a);

    // Creating the second line of diagram
    b = "\n/t ",*p->diagram[1];
    printf("%s",b);

    // Creating the third line of diagram
    if (*p->name == "Demux"){
        c = "\n\t ", *p->diagram[2]," ", output_labels[0];
    }
    else if (*p->name == "NOT" || *p->name == "Buffer"){
        c = "\n\t ",p->diagram[2];
    }
    else{
        c = "\n", input_labels[0]," ", *p->diagram[2];
    }
    printf("%s",c);

    // Creating the fourth line of diagram
    if (*p->name == "Demux"){
        d = "\n", input_labels[0]," ", *p->diagram[3];
    }
    else if (*p->name == "NOT" || *p->name == "Buffer"){
        d = "\n", input_labels[0]," ", *p->diagram[3]," ", output_labels[0];
    }
    else{
        d = "\n\t ",*p->diagram[3]," ", output_labels[0];
    }
    printf("%s",d);

    // Creating the fifth line of diagram
    if (*p->name == "Demux"){
        e = " \n", *p->diagram[4]," ", output_labels[1];
    }
    else if (*p->name == "NOT" || *p->name == "Buffer"){
        e = "\n\t ",*p->diagram[4];
    }
    else{
        e = "\n", input_labels[1]," ", *p->diagram[4];
    }
    printf("%s",e);

    
    // Now, if the gate is the one customized by the user (rather than a reference image)
    // then the gate's image should be saved to a text file as a record of the circuit.
    
    if (create_file){ // If create_file is 1, then the gate is "saved" to the text file
        char gate_data[7] = {"\n\n\n",a,b,c,d,e,"\n\n\n"}; // Collating all the lines of the diagram together
        write_to_circuit_file(gate_data); // write the diagram to the text file
    }
}

void select_gate(struct Gate *p, int display_choice){

    /* This function does:
   
    Using a switch, it points the struct pointer towards the chosen gate
    (which is determined on the number entered by the user).
    Thus, gate selection is enabled.
    */

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

    /* This function:


    In short: it makes the circuit and saves it as a text file based on user inputs

    
    Asks the user which gate they'd like to add to the circuit, and to enter a nmber corresponding to this gate.
    The user input is recieved and validated, then used to point the pointer towards the correct struct for the gate.
    The gate is then displayed with its default pin labels - extracted from the struct using pointers.
    
    The names_of_inputs and names_of_outputs arrays are initialised along with some other variables before loops begin.

    To start the first loop, the code iterates through the array of io labels searching for the first pin position which has
    a sub-array slot 0 (the slot for the pin's name) which is still set to "unassigned".

    Then the code checks if there are enough slots left in the array of io labels to add the pin labels for the current gate,
    by checking if the current pin position + the number of inputs and outputs exceeds the maximum number of pins (100).

    If there's not enough room, the function tells that to the user and exits to the main menu.

    Alternatively, if there are no unassigned slots,
    that means the maximum number of slots is reached and the function exits to the menu again.

    If there is enough room, the function proceeds normally:

    The function sets the names of the next few empty slots to "temp" to indicate which slots are for the outputs pins,
    and the index of the first of these output pins is recorded.

    The reason for this is to reserve the output pins for processing:
    by "priming" the output slots, the information that is shared for each of the outputs
    (the labels of the input pins to the gate and the type of gate that the outputs come from)
    can be written to the output pins BEFORE having named the output pins themselves.

    Thus, the input pins to the gate can be focused on first - which makes more sense from the user's perspective: inputs first, then outputs.


    Next, the input pins:

    For each of the input pins (using a for loop), the user is asked to enter a label name to replace the default pin-label for a single input.
    The user input is limited to 15 characters and stored in the names_of_inputs array.

    Then, using a while loop, the array of io labels is iterated through.
    If the user-entered-name of the input label is matches an existing pin in the array, the input pin already exists.
    So, the code skips the next step.
    Otherwise, when the code reaches the next unassigned slot, the name of the pin is placed in a new slot - representing a new pin.

    Then the primed output slots are iterated through, during this the gate type is written to slot 1 (the 2nd slot due to indexing starting at 0) of the output pin
    and the names of the input pins are written in turn to the input information slots for each output. 


    Next, the output pins proper:

    For each primed output slot...
    The user is asked to provide an output pin label. It's also limited to 15 characters. It's stored in the names_of_outputs array
    and written to the array of io labels at the primed slot.

    The array of io labels is the iterated through to see if the new output pin matches any other pins.
    If it does, the old pin's sub-array is rewritten as "destroyed" to remove any duplicates.
    (Which would cause error because the new one would never be used.)
    Besides, the old one would have just been an input and therefore contained just a pin name. So: no information is lost.

    But old pin is not reset to unassigned. Otherwise, the available space checking process and the
    priming process for further outputs for future gates would see the slot as being empty.
    Which means that slot could get overwritten and potentially the occupied slots after it
    - breaking the circuit and the program.


    Finally, the does_circuit_exist global variable is updated to 1, the gate is displayed and saved to the text file (because create_file = 1)
    and the user is asked if they want to add another gate to the circuit. If they do, the function is repeated, if not - return to main menu.

    But because all the pin information is stored in a global array,
    no parameters need be passed between the functions for the gates
    and progress is not lost unless the circuit is reset.
    */

    printf("Select a logic gate to add to the circuit.");

    // Code to select and display chosen logic gate:
        print_gate_options();  // displaying the gate options
        int gate_choice = get_user_input(GATE_OPTIONS); // retreiving and validating the input - a number corresponding to the correct gate
        struct Gate *p = &NAND; // initialising a pointer for a gate, setting it to NAND by default
        select_gate(p, gate_choice); // calls a function which points the pointer towards the correct gate

        // NOW TO DISPLAY THE GATE
        char inputs = *p->input_names;
        char outputs = *p->output_names;
        display_gate(p, &inputs, &outputs,0); // create_file = 0 to not save the gate to the text file
        
    // Now, code to ask the user to create labels for the gate

        int x; // establishing an incrementer for a while loop
        int first_output_index; // establishing a variable that will hold the index of the first output

        char names_of_inputs[p->n_inputs]; // creating 2 empty arrays for storing the input and output labels for this specific gate,
        char names_of_outputs[p->n_outputs]; // The size of the array has been set to the number of inputs and outputs for the selected gate.

        /*
        1st: Prime the new output pins by finding and reserving available slots for them in the array of io labels.
        (So that we can store other labels
        - like the label names of the inputs responsible for creating those outputs -
        in the sub-array of the output pins BEFORE deciding the names of the output pins themselves).
        */

        x = 0; // initialising x's value
        while ( x<MAX_NUMBER_OF_IO_PINS){

            // Now to prime the output slots
            if (array_of_io_labels[x][0] != "unassigned"){ // looking for the first unassigned pin label slot

                // Also, before assignning any pins. We need to check whether there are enough empty slots to actually build the logic gate.
                if (x + p->n_inputs + p->n_outputs >= MAX_NUMBER_OF_IO_PINS - 1){ // The event of there not being enough unassigned slots for pins
                printf("Number of existing Pin Labels: %d/%d\nBuilding this logic gate would exceed the maximum number of pin labels.\nSorry, the logic gate cannot be built.\nExiting to main menu.",x+1,MAX_NUMBER_OF_IO_PINS);
                main_menu();
                }

                for (int i = 0; i< p->n_outputs; i++){ // for each of the outputs...    
                    strcpy(array_of_io_labels[x][0], "temp"); // ..if a slot is unassigned, fill in the output pin labels with a temporary marker, and to stop any new inputs from filling the slot
                }
                first_output_index = x; // recording the index of the 1st output of this gate to use later when assign labels to both it and the other outputs
                x = 999; // break the condition of the while loop and exit the loop because the ouput pins are now ready
            }
            
            if (x == MAX_NUMBER_OF_IO_PINS - 1){ // the event of there being no more room for any more pins
                printf("Number of existing Pin Labels: %d/%d\nMaximum number of pin labels reached.\nSorry, the logic gate cannot be built.\nExiting to main menu.",x+1,MAX_NUMBER_OF_IO_PINS);
                main_menu();
            }
            x++;
        }

        // 2nd, managing the input pins
        for (int j = 0;j< p->n_inputs;j++){
            printf("\nPlease provide a label/name for INPUT pin %s of the gate. (Each label is limited to %d characters):   ", p->input_names[j], MAX_LABEL_LENGTH);

            char inputlabel[MAX_LABEL_LENGTH]; //limit of 15 characters
            fgets(inputlabel, sizeof(inputlabel), stdin); // got the label name for input

            names_of_inputs[j] = inputlabel; // storing the input labels in an array - to eventually use them for displaying the gate with the labels filled in

            // Now to assign the input pin label to a label in the io_label array
            // To do this, we have to search through the array for the first slot where there is no pin label already filled in

            x = 0; // resetting & reusing x to avoid creating an unnecessary variable

            while ( x<MAX_NUMBER_OF_IO_PINS){
                // first, need to check if the label already has an existing pin, checking through whole array of labels
                if (array_of_io_labels[x][0] == inputlabel){
                    x = 999; // no need to create a new pin if it already exists, so break the condition of the while loop
                }

                else if (array_of_io_labels[x][0] != "unassigned"){ // looking for the first unassigned pin label slot
                    strcpy(array_of_io_labels[x][0], inputlabel); // if unassigned, fill in the pin label with the user input
                    x = 999; // break the condition of the while loop and exit the loop because the input label is now made
                }
                x++;
            }

            // 3rd, storing labels in the the output pins
            for (int k = 0; k< p->n_outputs; k++){ // for each of the outputs...
                strcpy(array_of_io_labels[first_output_index + k][2 + j], inputlabel);
                /* In the above line, the output slots, starting from the indexed slot (& continuing up to the last (kth) output - hence [first_output_index + k]),
                the jth INPUT LABEL is placed in the jth INPUT LABEL SLOT of the output pin
                (which starts at the 3rd slot of a given output label's sub-array, hence [2 + j]).
                So, each input for a given output has its label stored in the output label's sub-array for later use when running the circuit later.
                */
                strcpy(array_of_io_labels[first_output_index + k][1], p->name); // recording the gate type in the slot for gate types in the output label's sub-array
            }
        }

        // 4th managing the output pins fully
        for (int l = 0; l< p->n_outputs; l++){ // for each of the outputs...
            printf("\nPlease provide a label/name for INPUT pin %s of the gate. (Each label is limited to %d characters):     ", p->output_names[l], MAX_LABEL_LENGTH);
            /* Note: if the user referencing the same pin twice (e.g for an output used as an input),
               they need to match the name character for character */

            char outputlabel[MAX_LABEL_LENGTH]; //limit of 15 characters
            fgets(outputlabel, sizeof(outputlabel), stdin); // got the label name for output
           
            strcpy(array_of_io_labels[first_output_index + l][0], outputlabel); // naming the output gate using the user input

            names_of_outputs[l] = outputlabel; // storing the output labels in an array for use when displaying the gate

            // checking if an output variable has ALREADY been used as an input (in the case of feedback)
            x = 0;
            while ( x<MAX_NUMBER_OF_IO_PINS){
                // first, need to check if the label has already an existing pin, checking through whole array of labels
                if (array_of_io_labels[x][0] == outputlabel){
                    for (int m = 0; m<NUMBER_OF_PIN_LABELS; m++){ // 5 is number of parameters in each sub-array for a single pin
                        strcpy(array_of_io_labels[x][m], "destroyed"); /* Removing the pin to avoid duplicates.
                                                                          And not resetting to unassigned in case the available space gets miscalculated.
                                                                          The original had less information, so it was destroyed.*/
                    }
                    x = 999; // original pin destroyed, job done, so break the condition of the while loop
                }
            } // Feedback isn't possible with this version of the code, but that's not a main part of it,        
        }     // there aren't currently clock cycles anyway.

        // Now, let's display the ASCII logic gate diagram for the chosen gate and save it to the text file. (So, create_file is set to 1).
        display_gate(p, names_of_inputs, names_of_outputs, 1);   

        does_circuit_exist = 1; /* This updates the status and allows for functions to run the circuit */

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

    /* This function:
    

    In short: it makes a test script, runs the circuit and compares it to the output the user expected.


    First of all, the function checks if a circuit exists. If not, return to main menu.

    Then, the user is asked how many inputs there are to the circuit.
    Following this, an array of input labels is created with the length equal to the number of inputs
    - to conserve memory usage - and a limit of 15 characters per label.
    The user is then asked to enter as many label names for inputs as they specified earlier.
    These names are stored in the aray.

    The same is done for the outputs: number of outputs --> output label array of said size --> enter output label names --> store in array 
    
    In order to make a test script the function needs to have all possible outputs:

    The number of input combinations = 2^(number of inputs)
    Some arrays are initialised to store the all the input combinations and the expected & actual outputs.

    Then all the input combinations are calculated:

    Each combination has a binary value. The combinations begin at zero and increment
    until they reach a value equal to the number of input combinations. 

    So, the decimal value of a given bit, for a given input combination, is equal to 2^(Number of inputs - 1 - the position of the bit in the array).
    Whether a bit is one or zero is determined by whether the input combination value (k) minus the bit_value, minus values of preceding positive bits is either
    a) greater than/equal to or b) less than zero. (See the code annotation of that stage for more clarity). 

    This is easily done with a for loop and some if statements.
    So, iterating through the input combinations, all the combinations are represented in binary
    and are all stored in the array_of_input_combos array.

    Next, the input and output labels are printed in a row on the same line - to form the top of the test script.
    Then the binary representation of each input combination is printed from the array one by one.
    After every combination, the user is asked to enter the output values for each output, for that input combination.
    These outputs are stored in the array_of_expected_outputs because these are the outputs the USER expects.

    To obtain the actual output values, the circuit has to be run...

    The array of input combinations is iterated through, and for each input combination,
    the labels in the array of input labels are compared to the labels of the pin names in the array of io labels.
    If an input label matches the label of a pin name in the array of io labels, then the value relating to that input label
    (stored in the array of input combos) is copied to a place in the array_of_io_values that corresponds to the matching label in
    the array of io labels.
    
    This effectively just puts the input values for a given combination into the array_of_io_values
    using the labels to get the values in the right places:

                       array of input names == array of io labels
    input combo array ---------------------------------------------> array of io values 

    With the inputs inputted, the circuit is run (using the run circuit function). 
    This will have generated the output values in the array_of_io_values.

    So, now the reverse process is applied to extract the output values from the array of io values, and pass the value of the outputs
    to the array of actual outputs.

    When an output name label is equal to a pin label name in the array of io labels, the value in the array of io values (with the same position (index)
    as the matching label in the array of io labels) is copied to the value in the array of actual outputs which has same index/position as
    the matching output names label.

                              array of output names == array of io labels
    array of actual outputs <--------------------------------------------- array of io values 

    Again, it's probably made eaiser to understand by looking at the code.

    After ALL THAT, it's a simple matter of printing and storing each line of the test script into a final array called "results"
    (where each row of the array is an input combination, expected outputs and actual outputs), with the input and output labels at the top 
    of the test script, then comparing each value of the expected output array to the actual output array
    - which is easily done because they have the same dimensions.

    Finally the results array is written to a text file called "Test Script.txt".

    */

    // Before running this menu's functionality, we need to check if there's actually a circuit for this test script
    if (does_circuit_exist = 0){
        printf("\nThere is no circuit detected. Please make a circuit before making and running a test script.\nReturning to Main Menu.\n");
        main_menu();
    }

    // First, create an array of input labels based on user input

    printf("\nFirstly, how many INPUTS are there to the circuit (not including internal pins between logic gates)?\nEnter a single number:    ");
    int Ninput = get_user_input(MAX_NUMBER_OF_IO_PINS-1); /* The maximum number of inputs is 99
    (because, theoretically, the circuit could be comprised of many gates that all combine and end in a gate with a single output). */

    printf("\nPlease enter the label names for each INPUT one at a time when prompted.\nEach label is limited to %d characters.\nNOTE: Please make sure that the input pin labels entered here match the input pin labels of the circuit - or the program WILL BREAK\n.",MAX_LABEL_LENGTH);
    char array_of_input_labels[Ninput][MAX_LABEL_LENGTH]; /* the size of the array is determined by how many inputs the user makes,
                                                             which makes it more memory efficient and easier to insert the user inputs*/
    
    for (int i = 0; i < Ninput; i++){
        printf("\nEnter the label name for INPUT number %d:   ",i+1);
        fgets(array_of_input_labels, MAX_LABEL_LENGTH, stdin); // stores the input label name in the array of input labels
    }

    // Secondly, create an array of outputs based on user input

    printf("\nSecondly, how many OUTPUTS are there from the circuit (not including internal pins between logic gates)?\nEnter a single number:    ");
    int Noutput = get_user_input(MAX_NUMBER_OF_IO_PINS/2); // The maximum number of output pins is half the number of pins because none of the gates has more outputs than inputs

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

    // These arrays will contain all possible inputs and their corresponding expected & atual outputs

    int array_of_input_combos[number_of_input_combinations][Ninput]; // This array will contain each combination of inputs as a row, and each input's value as a column
    int array_of_expected_outputs[number_of_input_combinations][Noutput]; // Also, the array of expected outputs has as many rows as there are input combinations
    int array_of_actual_outputs[number_of_input_combinations][Noutput]; // Additionally, the array of actual outputs will have the same dimensions as the array of expected outputs

    // Now, determining the values of the inputs for each row.
    for (int k = 1; k < number_of_input_combinations; k++){ // For each row of inputs

        /*
        k = the VALUE of the input combination,
        e.g. the 8th input combo of 3 bits is 111 - which is k = 7 and 111 is 7 in binary.
        So, just subtract the value of each bit from k to get the value of each bit in the value.
        */

        int combo_value = k;
        /*
        The value of each bit based on its position, and is equal to 2^(Number of inputs - 1 - the position of the bit in the array),
        whether a bit is one or zero is whether k - bit_value - the value of preceding positive bits is >= or < zero.
        E.g. if k = combo_value = 11 (or 1011 in binary), determining the 3rd bit would go like this:

        bit_value = 2^(4 input bits - 1 - position 2 (from the LEFT, index starts at 0)) = 2

        Then: k - 2 - 8 (the value of bit 0, which is positive) = 1. 

        1 > 0, so the 3rd bit (position 2) = 1.

        */
        
        for (int l = 0; l < Ninput; l++){ // For each input in a row

            int value_of_bit = pow(2, Ninput -1 - l); // e.g. for 4 bits, the 0th bit (the HSB) has value 8. Which is 2^(4-1-0).

            if (combo_value - value_of_bit >= 0 ){  // In this case, the bit is less than or equal to the combination value (e.g. combination 7, or 00000111)
                array_of_input_combos[k][l] = 1;    // So, the bit can be used to represent part of this value.
                combo_value = k - value_of_bit;     // The remaining value of the combination is then compared to the other bit values until it's been represented.
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

    // Now, we'll use the test script to evaluate the circuit

    // For each set of inputs, run the circuit, find the output values and store them in the array of actual outputs
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
    printf("\n%s\n",number_of_discrepancies); // display number of discrepancies
    
    // Now to ask the user if they'd like to save these results to a text file
    printf("\nWould you like to save the test results?\nEnter 1 for yes, 0 for no:  ");
    int save_results = get_user_input(BINARY_CHOICE);
    if (save_results){
        create_test_script_file();
        write_to_test_script_file(results);
    }
}

static void print_circuit_testing_menu(void) // Implement once menu 3 is fully functional without functions - then split it up
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

    /* This function:
    
    In short: uses the input pin values inputted from the test script
              and uses the sub-array for each pin to decide the gate operation that should be done in order to produce
              the correct output value to set as the value of the pin.


    The function iterates through the array of io labels using index i, stopping when an unassigned pin name label is reached
    (which is end of the pins the user has assigned).

    If a given pin in the array of io labels has no input pins labels, it must be a "pure" input to the circuit
    (i.e. it is not an output of any gate) and can therefore be ignored: any pure inputs to the circuit will have had their values 
    inputted by the test script so we don't have to worry about them.

    If a pin is marked as "destroyed" or its input pin labels are "unassigned",
    then the following does not happen and the program continues to iterate until
    it either finds an assigned pin or the end of the array is reached.

    The current position in the array of io labels is the pin currently being focused on/selected: pin i.

    Within the current while loop, the array of io labels is iterated through again using index j.
    If the jth pin name label is equal to any of the input pin labels of pin i,
    then the jth pin value corresponding to the jth pin name label
    (due to the fact that array of io labels and array of io values share the same index)
    is copied to the correct "input" variable below.

    This gives us the inputs for the operation to calculate the value of pin i.

    The operation itself is determined by the gate name label in the sub-arry of the array of io values for pin i.
    Using an if-else ladder, the operation matching the gate name label is selected and carried out on the relevant 
    "input" variables below. 

    For the Demux, it's a bit more complicated because it has 2 outputs rather than one.

    We have to first decide which of the 2 outputs this output is, Y0 or Y1.
    This is done based on chacking the previous pin (pin i-1).
    If pin i-1 has the EXACT same input labels and gate type, it must be from the same mux, so treat that output as being Y0.
    So, the current output is Y1.
    If pin i-1 has different details, then the current pin must be the first of the mux outputs. 
    So, the current output is Y0.

    Then of course there's the usual opreations for the demux. But with 4 possible outputs depending on whether
    the current pin is Y0 or Y1 and what the value of the select bit is.

    Then increment i to move to the next pin.
    Repeat until no more assgined pins of the end of the array is reached.
    */

    int i = 0;
    int j;
    int input_1;
    int input_2;
    int input_3;
    while(i<MAX_NUMBER_OF_IO_PINS && array_of_io_labels[i][0] != "unassigned"){ // looking through all pins that have been used

        if (array_of_io_labels[i][0] != "destroyed" && array_of_io_labels[i][2] != "unassigned"){
            /* only do the following if a pin has not been destroyed and is not a pure input.
            ("Pure input" means a pin is not created as an output of any gate, so the 1st input pin for the pin's labels must be unassigned) */

            // i = the position of the pin we're currently focusing on - also it is by desgin the position of the pin value for this pin in the array_of_io_values

            j = 0;
            while (j<MAX_NUMBER_OF_IO_PINS && array_of_io_labels[j][0] != "unassigned"){ // again, looking through all pins that have been used

                if (array_of_io_labels[j][0] == array_of_io_labels[i][2]){ // if the current pin label in the array is equal to the 1st input label of the pin we're currently focusing on
                    input_1 = array_of_io_values[j];                   // then the corresponding pin value of the pin label is taken as an input value for the pin we're currently focusing on.
                }
                if (array_of_io_labels[j][0] == array_of_io_labels[i][3]){ // if the current pin label in the array is equal to the 2nd input label of the pin we're currently focusing on
                    input_2 = array_of_io_values[j];                   // then the corresponding pin value of the pin label is taken as an input value for the pin we're currently focusing on.
                }
                if (array_of_io_labels[j][0] == array_of_io_labels[i][4]){ // if the current pin label in the array is equal to the 3rd input label of the pin we're currently focusing on
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

void menu_item_4(void) {
    printf("\n>> Menu 4: Clearing previous circuit...\n");

    /* This function does:
    
    Firstly, a new text file is initialised called "Circuit.txt"
    The does_circuit_exist variable is set to zero to prevent the Circuit Testing function(s) being called without a complete circuit.
    The above two both serve to "reset" from the previous circuit and prevent any old "Circuit.txt" files being written to
    - while simultaneously prparing the new one to be written to.

    Next, this function iterates counter through the MAX_NUMBER_OF_IO_PINS.
    For each value within the MAX_NUMBER_OF_IO_PINS, the function clears the array of io labels and the array of io values.
    It does this by setting all the labels to "unassigned" and all the values in the values array to 0.

    This serves to set all the stored data for pin information of the circuit to a known default. 
    Which is useful for preparing for the first circuit made and resetting for any further ones made during the same session.
    */

    does_circuit_exist = 0;
    create_circuit_file(); //Initialising an empty text file for storing the circuit in.

    int n = NUMBER_OF_PIN_LABELS; /* n is the number of parameters in the sub-array for given pin, which is within the larger array of labels.
                                     (Also, the sub-array and NUMBER_OF_PIN_LABELS can be adjusted, and the code will automatically scale for more inputs.) */
    
    for (int i; i<MAX_NUMBER_OF_IO_PINS; i++){  // An overarching for loop that goes through the whole label array
        for (int j; j<n; j++){    // A sub loop that goes through the sub-array for the pin in position i of the labels array      
            strcpy(array_of_io_labels[i][j],"unassigned");  /* Setting each the value in the sub-array to unassigned,
                                                               to ensure that the values are all reset to a known default before starting the next circuit */
        }

        array_of_io_values[i] = 0; // setting all the values in the array of input & output values to 0. To reset all the values for the next circuit.

        /*
        Structure of array of io labels: array_of_io_labels[i] = [pin_label, gate_type, input_1, input_2, input_3]
        
        Structure of array of io values: array_of_io_values = [1,0,1,0,0,1,...etc]
        */


        //NOTE TO SELF:
        //strcpy(array_of_io_labels[i][j],"unassigned");  --- This is the correst way to overwrite a string

        //array_of_io_labels[i][j] = "unassigned";  --- This doesn't work because you can't just reassign the string
    }
}

int create_circuit_file() { // Self-explanatory
   
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

int write_to_circuit_file(char custom_gate) { // Self-explanatory
   
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

int create_test_script_file() { // Self-explanatory
   
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

int write_to_test_script_file(char text) { // Self-explanatory
   
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