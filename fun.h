#ifndef _fun_h

#define _fun_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#include <time.h>

typedef struct task{
    long hours;
    long minutes;
    char program[40];
    long state;
    long time_to_exec;
    long time_to_sleep_before_exec;
}task;

int colons_in_file(FILE * file);

int amount_of_arguments(int arg, char*word);

bool equal_namings(char* naming_input, char* naming_output);

FILE* checking_file_valid(char * naming, bool for_writing);

task * file_in_good_format(FILE * file);

int comparator(const void *p, const void *q) ;

int daj_ilosc();

void set_time_to_exec(task * array, int length);

void set_time_to_sleep(task * array, int legnth);

#endif