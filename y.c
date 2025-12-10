#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

struct Gate{
    int n_inputs;
    char input_names[3][6];
};

struct Gate g = {
    .n_inputs = 3,
    .input_names = "A","B","C",
};

int main(void){
    struct Gate *p = &g;
    char inputs[p->n_inputs];
    for (int y = 0; y < p->n_inputs; y++){
        //inputs[y] = p->input_names[y];
        printf("%s",*p->input_names[y]);
    }
}