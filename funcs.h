#ifndef FUNCS_H
#define FUNCS_H


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









struct Gate{
    char name[10];
    char diagram[1]; // just a placeholder for calling the function for diagram
    int n_nands;
    int n_inputs;
    int n_outputs;
    char inputs[20];                    // unsure how to make the array of inputs. May need to determine that for every gate separately
    char outputs[20];
    char Boolean_representation[];

    
};

struct Gate NAND = {
    .name = "NAND",
    .diagram = "Need to load the diagram or print it using ASCII",
    .n_nands = 4,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "A⊕B"};

struct Gate NOT = {
    .name = "NOT",
    .diagram = "Need to load the diagram or print it using ASCII",
    .n_nands = 1,
    .n_inputs = 1,
    .n_outputs = 1,
    .Boolean_representation = "A'"};

struct Gate AND = {
    .name = "AND",
    .diagram = "Need to load the diagram or print it using ASCII",
    .n_nands = 2,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "A.B"};

struct Gate OR = {
    .name = "OR",
    .diagram = "Need to load the diagram or print it using ASCII",
    .n_nands = 3,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "y = A+B"};

struct Gate XOR = {
    .name = "XOR",
    .diagram = "Need to load the diagram or print it using ASCII",
    .n_nands = 4,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "y = A⊕B"};

struct Gate Buffer = {
    .name = "Buffer",
    .diagram = "Need to load the diagram or print it using ASCII",
    .n_nands = 0,
    .n_inputs = 1,
    .n_outputs = 1,
    .Boolean_representation = "y = A"};

struct Gate Mux = {
    .name = "Mux",
    .diagram = "Need to load the diagram or print it using ASCII",
    .n_nands = 4,
    .n_inputs = 3,
    .n_outputs = 2,
    .Boolean_representation = "y = A or y = B"};

struct Gate Demux = {
    .name = "Demux",
    .diagram = "Need to load the diagram or print it using ASCII",
    .n_nands = 5,
    .n_inputs = 2,
    .n_outputs = 1,
    .Boolean_representation = "y0 = A or y1 = A"};

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