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
    while(fgets(pol, size, file) != NULL){
        token = strtok(pol, ":");
        ++counter;
        while(token !=NULL){
            token = strtok(NULL, ":");
            ++counter;
            if(counter > 5){
                fprintf(stderr, "Too many arguments in file - line %d\nUsage: <hours>:<minutes>:<command>:<mode>\n", line);
                return -1;
            }
        }
        if(counter < 4){
                fprintf(stderr, "Too few arguments in file - line %d\nUsage: <hours>:<minutes>:<command>:<mode>\n", line);
                return -1;
        }
        counter = 0;
        ++line;
    }
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
        int i;
        for(i=0;i < 2; ++i)
            printf("Hours:%ld, minutes:%ld, word:%s, state:%ld",array_of_programs[i].hours, array_of_programs[i].minutes, array_of_programs[i].program,array_of_programs[i].state);
    
    return true;
}
