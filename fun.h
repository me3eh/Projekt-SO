#ifndef _fun_h

#define _fun_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

typedef struct task{
    long hours;
    long minutes;
    char program[40];
    long state;
}task;

int colons_in_file(FILE * file);

int amount_of_arguments(int arg, char*word);

bool equal_namings(char* naming_input, char* naming_output);

FILE* checking_file_valid(char * naming, bool for_writing);

bool file_in_good_format(FILE * file, task * array_of_programs);



#endif