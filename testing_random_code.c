

        for (int l = 0; l < Ninput; l++){ // For each input in a row
            array_of_input_combos[k][l] = array_of_input_combos[k-1][l]; // Set each row to the previous row, ready for incremening
        }
        // Firstly, we need to check the LSB
        if (array_of_input_combos[k][Ninput-1] == 0){ // if the LSB is zero
            array_of_input_combos[k][Ninput-1] = 1; // Then increment the LSB - which will not overflow to the next bit
        }
        else if (array_of_input_combos[k][Ninput-1] == 1 && Ninput >= 2){ /* if the LSB is one and there are at least 2 inputs 
            (need to check for this, because if just a buffer has been placed, there will only be 1 input
            and thus we've already exhausted the combinations) */

            // In this case we'll have set the LSB to zero and increment the next-lowest value bit - and so on...

            // So, to check each value in the row and increment accordingly, we need to use a new for loop for this

            for (int l = 2; l < Ninput; l++){ // starting from the next-lowest-bit as a reference point 


                // DOESN'T WORK - NEED TO ADJUST --- IT'D JUST SET THE HSB TO 1 EVERY TIME - need to adjust it to do the process once
                // maybe check if the current bit is one, and that this isn't the HSB, then increment the previous bit.
                // but the problem is that it keeps incrementing all the bits - just need to do it once per cycle.
            

                if (array_of_input_combos[k][Ninput-l+1] == 1){ // If the bit lower than the current bit is one:
                    array_of_input_combos[k][Ninput-l] = 1;     //    then set the current bit to 1...
                    array_of_input_combos[k][Ninput-l+1] = 0;   //    ...and set the bit lower than the current bit to zero.
                }
            }
            
        }
// C Implementation for lineto()
#include <graphics.h>

// driver code
int main()
{
    // gm is Graphics mode which is
    // a computer display mode that
    // generates image using pixels.
    // DETECT is a macro defined in
    // "graphics.h" header file
    int gd = DETECT, gm;

    // initgraph initializes the
    // graphics system by loading a
    // graphics driver from disk
    initgraph(&gd, &gm, "");

    // change initial position of point
    // with moveto function
    moveto(100, 100);

    // lineto function
    lineto(250, 100);

    getch();

    // closegraph function closes the
    // graphics mode and deallocates
    // all memory allocated by
    // graphics system .
    closegraph();

    return 0;
}

*/

int main()
{
        char x = "A";
        x = "eeeee";
        return 0;
}