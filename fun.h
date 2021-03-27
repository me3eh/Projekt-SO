#ifndef _fun_h

#define _fun_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

int amount_of_arguments(int arg, char*word);

bool equal_namings(char* naming_input, char* naming_output);

FILE* checking_file_valid(char * naming, bool for_writing);

#endif