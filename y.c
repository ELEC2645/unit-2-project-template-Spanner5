#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

struct G{
    int n_inputs;
    char input_names[3][6];
};

struct G g = {
    .n_inputs = 3,
    .input_names = "A","B","C",
};

int main(void){
    struct G *p = &g;
    char inputs[p->n_inputs];
    for (int y = 0; y < p->n_inputs; y++){
        //inputs[y] = p->input_names[y];
        printf("%s",*p->input_names[y]);
    }
}

/* I think the pointers have caused the errors In the code,
   but I've tried for hours andhours to fix the errors and now I cant' fix them.
   now I've run  out of time... (I made this project too ambitious and now I can't even submit it properly...)


                                            :(

*/