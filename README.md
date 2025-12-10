[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21756496)
# ELEC2645 Unit 2 Project: circuit_maker

This is supposed to be a basic command line application which can be used to:

1.View a selection of logic gates. (Currently 8, but can be scaled as necessary if this was to be a real thing).

2.Make a circuit out of the logic gates. And save the circuit as text file.

3.Make a text script of the circuit, run the circuit to compare expected and actual outputs.

4.Clear the circuit so that new ones can be made.

### Gates available:

1.AND
2.NAND
3.NOT
4.Buffer (BUF for short)
5.OR
6.XOR
7.Mux
8.Demux (DMUX for short)

### Project Successes:

I managed to work out how it would work and coded it well.
The logic seems clear to me and laid out in a more-or-less understandable way.
I am very happy with what I've managed to achieve considering the scope and technicality of my project.

### Project Failings:

Unfortunately, this project took FAR LONGER than I ever anticipated.
It's scope exceeded the complexity required by the brief and its technicality exceeded the timeframe.
Yes, the project is as of yet *unfinished...*

Needless to say, I am not happy about this, *especially* after all the work I put in to figure out how it'd all work.
It's fair to say that I could have spent more time working on it,
but I definitely spent *at least DOUBLE* the expected 15 hours on the project.

I'd intended to upload snippets of the projects once I'd got something working.
However, because I'd designed the project to jump from function to function, and developed parts of the code out of order as I tried to figure out how things would be done, the code was never complilable as there were always errors present from having open-ended functions, etc.

When it got to the week of submission, things got a bit panicky. But eventually I got rid of all the error "squiggles" and was hoping I'd finally finished the coding.

But when I ran it I got a series of similar errors permeating the ENTIRE PROJECT:

        funcs.c:114:11: warning: assignment to ‘char’ from ‘char *’ makes integer from pointer without a cast [-Wint-conversion]
        114 |         a = "\n", input_labels[2]," ", *p->diagram[0];
            |           ^

        funcs.c:156:44: warning: comparison between pointer and integer
        156 |     else if (*p->name == "NOT" || *p->name == "Buffer"){
            |          

The above errors are to do with the use of pointers. But I could NOT find an asnwer on what I could do to fix it.
And because the errors permeated most of the code, I couldn't simply redo the code.


        funcs.c:66:9: warning: implicit declaration of function ‘main_menu’ [-Wimplicit-function-declaration]
        66 |         main_menu();
            |         ^~~~~~~~~

And I had no idea what was causing this. It was such a generic error that I couldn't pinpoint what had caused it.


In short, I was over-ambitious and ran out of time. 
Sorry for not completing the project. 

Still, I believe that the all code that I've written and the logic behind it are sound and can be appreciated.
Despite the convoluted pointer errors that have arisen from somewhere.

Thank you and have a good time.

### 4 Submit Solution

Use the same method as previous labs to commit and push your code to your GitHub repository for the autograder to check. 

In your final journal post, please include a link to your GitHub repository containing your code *and* a zip file of your code as an attachment.
