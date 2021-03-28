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

int colons_in_file(FILE * file){
    int size = 200; 
    char pol [size];
    int line = 1;
    char * token;
    int counter = 0;
    regex_t regex;
    const int n_matches = 1;
    regmatch_t m[n_matches];
    while(fgets(pol, size, file) != NULL){
        int value = regcomp(&regex, "^([0-2]?[0-9]):([0-5]?[0-9]):[a-zA-Z|: -]*:[0-2]$", REG_EXTENDED|REG_NEWLINE);
    	int lk = regexec(&regex, pol, n_matches, m, 0);
        if(lk == 0)
            ++line;
        else if( lk == REG_NOMATCH){
            fprintf(stderr, "Bad format in file\n Usage: <hours>:<minutes>:<code>:<mode>");
            return -1;
        }
        else{
            fprintf(stderr, "An error occured");
            return -1;
        }
    }
    regfree(&regex);
    --line;
    rewind(file);
    return line;
}
bool file_in_good_format(FILE * file, task * array_of_programs){
    int line = 1;
    int size = 200;
    int counter = 0;
    char pol [size]; 
    char * token, *cp;
    int columns = colons_in_file(file);
    if(columns == -1)
        return false;
    array_of_programs = (task*)malloc(columns * sizeof(task));
    if(array_of_programs == NULL){
        perror("Allocation memory:");
        return false;
    }
    
    while(fgets(pol, size, file) != NULL){ 
        printf("%c", pol[3]);
        token = strtok(pol, ":"); 
        do{
            switch(counter){
                case 0:
                    array_of_programs[line-1].hours = strtol(token, &cp, 10);
                break;
                case 1:
                    array_of_programs[line-1].minutes = strtol(token, &cp, 10);
                break;
                case 2:
                    strcpy(array_of_programs[line-1].program, token);
                break;
                case 3:
                    array_of_programs[line-1].state = strtol(token, &cp, 10);
                break;
                default:
                    fprintf(stderr, "Incorrect format in file - line %d\nUsage: <hours>:<minutes>:<command>:<mode>\n", line);
                    free(array_of_programs);
                    return false;
                break;
            }
            token = strtok(NULL, ":");
            ++counter;
        }while( token != NULL ); 
        
        ++line;
        if(counter != 4){
            free(array_of_programs);
            return false;
        }
        counter = 0;
    }    
    return true;
}
