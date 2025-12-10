#ifndef FUNCS_H
#define FUNCS_H


typedef enum { BINARY_CHOICE = 2, MENU_ITEMS = 5, GATE_OPTIONS = 8, MAX_NUMBER_OF_IO_PINS = 100, NUMBER_OF_PIN_LABELS = 5, MAX_LABEL_LENGTH = 15, CIRCUIT_TESTING_MENU_ITEMS = 4 } important_constants ;   // - defining an enum globally for use in input validation

char* array_of_io_labels[MAX_NUMBER_OF_IO_PINS][NUMBER_OF_PIN_LABELS][MAX_LABEL_LENGTH]; // making a character array where each term is an empty space for a label (of the variables used in the gates).
//  limit of 15 characters per label name

/* in the main program, each slot of the array of io labels gets rewritten to:
Syntax: array_of_io_labels[i] = [pin_label, gate_type, input_1, input_2, input_3]
*/

int* array_of_io_values[MAX_NUMBER_OF_IO_PINS];
/*
making an array of integer values which will change depending on the computations done to with pointers
- the value in an array should match that of the labels - except in the cases where a label is marked equal to another
*/

int does_circuit_exist; // defining this variable to be updated and used to check whether a circuit exists and thus whether some functions can run

struct Gate{
    char name[10];
    char diagram[5][50];
    int n_nands;
    int n_inputs;
    int n_outputs;
    char input_names[3][6];
    char output_names[2][2];
    char Boolean_representation[20]; // 20 characters long to allow for longer formulae or descriptions
};

struct Gate AND = {
    .name = "AND",
    .diagram = 
"\n",
 "  	   _______",
 "--------|       \\",
 "        | AND    ))---------",
 "--------|_______//\n",
    .n_nands = 2,
    .n_inputs = 2,
    .n_outputs = 1,
    .input_names = "A","B",
    .output_names = "Y",
    .Boolean_representation = "Y = A.B"};

struct Gate NAND = {
    .name = "NAND",
    .diagram = 
"\n",
"   	  _______",
"--------|       \\",
"        | NAND   ))-(O)-----",
"--------|_______//\n",
    .n_nands = 4,
    .n_inputs = 2,
    .n_outputs = 1,
    .input_names = "A","B",
    .output_names = "Y",
    .Boolean_representation = "Y = A⊕B"};

struct Gate NOT = {
    .name = "NOT",
    .diagram = 
"\n",
"   	  ___",
"        |   \\",
"--------|NOT >>>-(O)--------",
"        |___//\n",
    .n_nands = 1,
    .n_inputs = 1,
    .n_outputs = 1,
    .input_names = "A",
    .output_names = "Y",
    .Boolean_representation = "Y = A'"};

struct Gate Buffer = {
    .name = "Buffer",
    .diagram =
"\n",
"	       ___",
"         |   \\",
" --------|BUF >>>------------",
"         |___//\n",
    .n_nands = 0,
    .n_inputs = 1,
    .n_outputs = 1,
    .input_names = "A",
    .output_names = "Y",
    .Boolean_representation = "Y = A"};

struct Gate OR = {
    .name = "OR",
    .diagram = 
"\n",
" 	        ______",
" --------\\      \\   ",
"           )  OR  >>---------",
" --------//______//\n",
    .n_nands = 3,
    .n_inputs = 2,
    .n_outputs = 1,
    .input_names = "A","B",
    .output_names = "Y",
    .Boolean_representation = "Y = A+B"};

struct Gate XOR = {
    .name = "XOR",
    .diagram = 
"\n",
" 	        ______",
" -----)--\\      \\",
"       }   ) XOR  >>---------",
" -----)--//______//\n",
    .n_nands = 4,
    .n_inputs = 2,
    .n_outputs = 1,
    .input_names = "A","B",
    .output_names = "Y",
    .Boolean_representation = "Y = A⊕B"};

struct Gate Mux = {
    .name = "Mux",
    .diagram =
" ---¬",
"	       _L__",
" --------|    \\",
"         | MUX  ]------------",
" --------|____//\n",

    .n_nands = 4,
    .n_inputs = 3,
    .n_outputs = 1,
    .input_names = "A","B","Select",
    .output_names = "Y",
    .Boolean_representation = "Y = A or Y = B"}; // A if sel == 0, b if 1

struct Gate Demux = {
    .name = "Demux",
    .diagram =
" ----¬",
"	        _L__",
"         //    |-------------",
" -------[ DMUX |",
"         \\____|-------------\n",
    .n_nands = 5,
    .n_inputs = 2,
    .n_outputs = 2,
    .input_names = "A","Select",
    .output_names = "Y1","Y2",
    .Boolean_representation = "Y0 = A or Y1 = A"}; // Y0 if sel == 0, Y1 if 1

void menu_item_1(void);
void menu_item_2(void);
void menu_item_3(void);
void menu_item_4(void);

// MY INTERNAL FUNCTIONS for within the main menu options

void print_gate_options(void);
void display_gate(struct Gate *p,char* input_labels,char* output_labels,int create_file);
void select_gate(struct Gate *p, int display_choice);
static void print_circuit_testing_menu(void);
int create_circuit_file();
int write_to_circuit_file(char custom_gate);
int create_test_script_file();
int write_to_test_script_file(char text);
void run_circuit(void);

#endif