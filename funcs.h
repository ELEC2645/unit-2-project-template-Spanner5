#ifndef FUNCS_H
#define FUNCS_H

typedef enum { BINARY_CHOICE = 2, MENU_ITEMS = 6, GATE_OPTIONS = 8 } menu_items ;   // - defining an enum globally for use in input validation

// need to mkae a character array where each term is an empty space for a label for the variables used in the gates




struct Gate{
    char name[10];
    int diagram; // just a placeholder for calling the function for diagram
    int n_nands;
    int n_inputs;
    int n_outputs;
    char inputs[20];                    // unsure how to make the array of inputs. May need to determine that for every gate separately
    char outputs[20];
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
    //int A = 0,

    .inputs = 0,0,

    .Boolean_representation = "A⊕B"};

struct Gate NOT = {
    .name = "NOT",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 1,
    .n_inputs = 1,
    .n_outputs = 1,
    .Boolean_representation = "A'"};

struct Gate AND = {
    .name = "AND",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 2,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "A.B"};

struct Gate OR = {
    .name = "OR",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 3,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "y = A+B"};

struct Gate XOR = {
    .name = "XOR",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 4,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "y = A⊕B"};

struct Gate Buffer = {
    .name = "Buffer",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 0,
    .n_inputs = 1,
    .n_outputs = 1,
    .Boolean_representation = "y = A"};

struct Gate Mux = {
    .name = "Mux",
    .diagram = 0,//"Need to load the diagram or print it using ASCII",
    .n_nands = 4,
    .n_inputs = 3,
    .n_outputs = 2,
    .Boolean_representation = "y = A or y = B"};

struct Gate Demux = {
    .name = "Demux",
    .diagram = 0,//Need to load the diagram or print it using ASCII",
    .n_nands = 5,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "y0 = A or y1 = A"};

void menu_item_1(void);
void menu_item_2(void);
void menu_item_3(void);
void menu_item_4(void);
void menu_item_5(void);
//void menu_item_6(void);


// MY INTERNAL FUNCTIONS for within the 5 menu options

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