#include "fun.h"

int amount_of_arguments(int arg, char* word){
    if(arg != 3){
        fprintf(stderr, "Usage: %s <taskfile> <outfile> \n", word);
        return EINVAL;
    }
    return 0;
}

bool equal_namings(char* naming_input, char* naming_output){
    return (naming_input == naming_output);
}

FILE* checking_file_valid(char * naming, bool for_writing){
    FILE * file = for_writing ? fopen(naming, "w") : fopen(naming, "r");
    if(file == NULL)
        perror("File error");
    return file;
}
