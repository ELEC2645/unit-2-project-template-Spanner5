#ifndef FUNCS_H
#define FUNCS_H

typedef enum { BINARY_CHOICE = 2, MENU_ITEMS = 7, GATE_OPTIONS = 8, MAX_NUMBER_OF_IO_LABELS = 100 } menu_items ;   // - defining an enum globally for use in input validation

char* array_of_io_labels[MAX_NUMBER_OF_IO_LABELS]; // making a character array where each term is an empty space for a label (of the variables used in the gates).
// --- [10];  limit of 10 characters per label name

/* in the main program, each slot of the array of io labels gets rewritten to:
array_of_io_labels[i] = [pin_label,input_1,input_2,input_3,gate_type] // should I add is output or is input to the label? */


int* array_of_io_values[MAX_NUMBER_OF_IO_LABELS];
/*
making an array of integer values which will change depending on the computations done to with pointers
- the value in an array should match that of the labels - except in the cases where a label is marked equal to another

Although the array contains pointers and values.
The array values of inputs should b -1 and the array values of labels whicha re not input or outputs should be pointers,
we need some way of determining outputs as well.
Maybe attach a metadata for each value in THIS ARRAY which increments every time a pointer is used.
(Attach it when returning the value, actually return an array [value, times used].)
Then when the output variable(s) will have been used zero times.
*/

struct Gate{
    char name[10];
    int diagram; // just a placeholder for calling the function for diagram
    int n_nands;
    int n_inputs;
    int n_outputs;
    char input_names[5];
    char output_names[5];
    char Boolean_representation[20]; // 20 characters long to allow for longer formulae or descriptions


     /* for inputs, could have an array of int variables, which get assigned a value,
        but every time a user makes a gate, a new struct is made which is a clone of one of these
        but with its int variables for inputs assigned a value - or letter OR array (up to a character limit).
        The input is then stored in a global array. OR passed as a parameter between functions
        OR written to a txt file and loaded from every time.

        Whenever a user enters a label for an input or output,
        the code looks through the list of all labels and assigns the new variable as equal to THAT VARIABLE ITSELF as a pointer
        so that a change in the variable affects the output of the pointer. So that nested gates can work.
        It changes the initial input but that doesn't matter. OR it just adds all the computations together manually
        once all inputs are given - to create an output.
     */
};

struct Gate NAND = {
    .name = "NAND",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 4,
    .n_inputs = 2,
    .n_outputs = 1,
    .input_names = "A","B",
    .output_names = "Y",
    .Boolean_representation = "Y = A⊕B"};

struct Gate NOT = {
    .name = "NOT",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 1,
    .n_inputs = 1,
    .n_outputs = 1,
    .input_names = "A",
    .output_names = "Y",
    .Boolean_representation = "Y = A'"};

struct Gate AND = {
    .name = "AND",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 2,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "Y = A.B"};

struct Gate OR = {
    .name = "OR",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 3,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "Y = A+B"};

struct Gate XOR = {
    .name = "XOR",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 4,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "Y = A⊕B"};

struct Gate Buffer = {
    .name = "Buffer",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 0,
    .n_inputs = 1,
    .n_outputs = 1,
    .Boolean_representation = "Y = A"};

struct Gate Mux = {
    .name = "Mux",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 4,
    .n_inputs = 3,
    .n_outputs = 2,
    .Boolean_representation = "Y = A or Y = B"};

struct Gate Demux = {
    .name = "Demux",
    .diagram = 0,//Need to load the diagram or print it using ASCII",
    .n_nands = 5,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "Y0 = A or Y1 = A"};

void menu_item_1(void);
void menu_item_2(void);
void menu_item_3(void);
void menu_item_4(void);
void menu_item_5(void);
void menu_item_6(void);


// MY INTERNAL FUNCTIONS for within the 6 menu options

void print_gates(void);
void select_gate(struct Gate *p, int display_choice);

#endif

/*

Example enum use:

typedef enum { A =1, MENU_ITEMS = 6,  } menu_items ;   // - defining an enum globally for use in input validation

static void main_menu(void)
{
    print_main_menu();

    menu_items cur_items = MENU_ITEMS;
    cur_items = A;
    int input = get_user_input(cur_items);
    select_menu_item(input);
}

static int get_user_input(menu_items local_name)
{

    local_name = A;


    rest of function
}
   
*/